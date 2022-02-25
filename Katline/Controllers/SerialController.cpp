#include <Katline/Controllers/IO.h>
#include <Katline/Debug.h>
#include <Katline/Katline.h>
#include <Katline/Controllers/SerialController.h>

namespace Katline {

namespace Controller {

bool SerialController::Init()
{
    m_enabled = false;

    IO::OutB(PORT + 1, 0x00); // Disable all interrupts
    IO::OutB(PORT + 3, 0x80); // Enable DLAB (set baud rate driver)
    IO::OutB(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    IO::OutB(PORT + 1, 0x00); //                  (hi byte)
    IO::OutB(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    IO::OutB(PORT + 2, 0xc7); // Enable FIFO, clear them, with 14-byte threshold
    IO::OutB(PORT + 4, 0x0b); // IRQs enabled, RTS/DSR set
    IO::OutB(PORT + 4, 0x1e); // Set in loopback mode, test the serial chip
    IO::OutB(PORT + 0, 0xae); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    if (IO::InB(PORT + 0) != 0xAE) {
        Debug::WriteFormatted("[SerialController] Failed to initialize serial: test failed.\n");
        return false;
    }

    m_enabled = true;

    // Serial not faulty, set it to normal mode
    IO::OutB(PORT + 4, 0x0f);

    Debug::WriteFormatted("[SerialController] Initialized.\n");

    return true;
}

int SerialController::Received()
{
    return IO::InB(PORT + 5) & 1;
}

char SerialController::Read()
{
    if (m_enabled) {
        while (Received() == 0)
            ;

        return (char) IO::InB(PORT);
    } else {
        return '\0';
    }
}

int SerialController::IsTransmitEmpty()
{
    return IO::InB(PORT + 5) & 0x20;
}

void SerialController::Write(char ch)
{
    if (m_enabled) {
        while (IsTransmitEmpty() == 0)
            ;

        IO::OutB(PORT, (uint8_t) ch);
    }
}

void SerialController::WriteStringSafe(const char* string, size_t size)
{
    if (m_enabled)
        for (size_t i = 0; i < size; i++)
            Write(string[i]);
}

void SerialController::WriteString(const char* string)
{
    if (m_enabled) {
        while (string[0] != '\0') {
            Write(string[0]);
            string++;
        }
    }
}

}

}
