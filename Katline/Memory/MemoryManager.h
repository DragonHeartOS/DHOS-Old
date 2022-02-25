#pragma once

#include <Katline/Memory/MemoryData.h>

#include <CommonLib/Common.h>

namespace Katline {

namespace Memory {

class MemoryManager {
public:
    static void Init(MemoryMap const* mmap);

    static void* Allocate(size_t size);
    static void Free(void* ptr);
};

using MM = MemoryManager;

}

}
