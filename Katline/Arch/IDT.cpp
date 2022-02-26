#include "Debug.h"
#include <Katline/Arch/IDT.h>

#include <Katline/Arch/Interrupts.h>

namespace Katline {

IDT::IDTR idtr;
IDT::Entry entries[256];

void IDT::SetOffset(Entry& entry, u64 offset)
{
    entry.offset0 = (u16)(offset & 0x000000000000ffff);
    entry.offset1 = (u16)((offset & 0x00000000ffff0000) >> 16);
    entry.offset2 = (u32)((offset & 0xffffffff00000000) >> 32);
}

u64 IDT::GetOffset(Entry& entry)
{
    u64 offset = 0;
    offset |= (u64)entry.offset0;
    offset |= (u64)entry.offset1 << 16;
    offset |= (u64)entry.offset2 << 32;
    return offset;
}

void IDT::Init()
{
    idtr.limit = 0x0FFF;
    idtr.base = (u64)&entries;

    asm("lidt %0"
        :
        : "m"(idtr));

    Debug::WriteFormatted("[IDT]: Loaded.\n");
}

}
