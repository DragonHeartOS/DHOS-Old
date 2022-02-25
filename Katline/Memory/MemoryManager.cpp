#include <Katline/Memory/MemoryManager.h>

#include <Katline/Debug.h>
#include <Katline/Memory/Heap.h>
#include <Katline/Memory/MemoryData.h>

#include <cstdint>

namespace Katline {

namespace Memory {

void MemoryManager::Init(MemoryMap const* mmap)
{
    for (uint64_t i = 0; i < mmap->size; i++) {
        MemoryData* md = &mmap->data[i];

        if (i != 0 && md->type == MemoryType::USABLE)
            mrvn_memory_init((void*)md->base, md->size);
    }

    Debug::WriteFormatted("[MemoryManager] Initialized.\n");
}

void* MemoryManager::Allocate(size_t size)
{
    return mrvn_malloc(size);
}

void MemoryManager::Free(void* ptr)
{
    mrvn_free(ptr);
}

}

}
