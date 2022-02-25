#pragma once

#include <stdint.h>

namespace Katline {

namespace IO {

[[maybe_unused]] static inline void OutB(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

[[maybe_unused]] static inline uint8_t InB(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

[[maybe_unused]] static inline void Wait(void)
{
    /* TODO: This is probably fragile. */
    asm volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}

}

}
