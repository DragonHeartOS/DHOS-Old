#pragma once

#include <stdint.h>

namespace Katline {

namespace Memory {

enum class MemoryType : uint32_t {
    USABLE = 1,
    RESERVED,
    ACPI_RECLAIMABLE,
    ACPI_NVS,
    BAD_MEMORY,
    BOOTLOADER_RECLAIMABLE = 0x1000,
    KERNEL_AND_MODULES,
    FRAMEBUFFER
};

struct MemoryData {
    uint64_t base;
    uint64_t size;
    MemoryType type;
    uint32_t unused;
};

struct MemoryMap {
    uint64_t size;
    MemoryData* data;
};

}

}
