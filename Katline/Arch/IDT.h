#pragma once

#include <CommonLib/Common.h>

namespace Katline {

class IDT {
public:
    struct Entry {
        u16 offset0;
        u16 selector;
        u8 ist;
        u8 type_attr;
        u16 offset1;
        u32 offset2;
        u32 ignore;
    };

    static void SetOffset(Entry& entry, u64 offset);
    static u64 GetOffset(Entry& entry);

    struct IDTR {
        u16 limit;
        u64 base;
    } __attribute__((packed));

    static void Init();
};

}
