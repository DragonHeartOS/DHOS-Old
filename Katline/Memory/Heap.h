#pragma once

#include <stddef.h>

namespace Katline {

namespace Memory {

void mrvn_memory_init(void* mem, size_t size);
void* mrvn_malloc(size_t size);
void mrvn_free(void* mem);

}

}
