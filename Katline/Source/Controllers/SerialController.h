#pragma once

#include <CommonLib/Math.h>
#include <Controllers/IO.h>

#include <cstddef>
#include <cstdint>
#include <cstdarg>

namespace Katline {

namespace Controller {

const uint PORT = 0x3f8;

class SerialController {
public:
    SerialController() {};
    bool Init();
    int Received();
    char Read();
    int IsTransmitEmpty();
    void Write(char ch);
    void WriteStringSafe(const char* string, size_t size);
    void WriteString(const char* string);

private:
    bool m_enabled = false;
};

}

}
