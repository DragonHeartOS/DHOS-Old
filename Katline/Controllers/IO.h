#pragma once

#include <CommonLib/Common.h>

namespace Katline {

namespace IO {

[[maybe_unused]] static inline void OutB(u16 port, u8 val)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}

[[maybe_unused]] static inline u8 InB(u16 port)
{
    u8 ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));
    return ret;
}

[[maybe_unused]] static inline void Wait(void)
{
    /* TODO: This is probably fragile. */
    asm volatile("jmp 1f\n\t"
                 "1:jmp 2f\n\t"
                 "2:");
}

}

}
