#include <CommonLib/Common.h>

#include <Katline/stivale/stivale2.h>

#include <Katline/Controllers/FramebufferController.h>
#include <Katline/Katline.h>
#include <Katline/Memory/MemoryData.h>

static u8 stack[8192];

extern "C" void kernel_start(stivale2_struct*);

static stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = 0 },
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0,
};

__attribute__((section(".stivale2hdr"), used)) static stivale2_header stivale_hdr = {
    .entry_point = (u64)&kernel_start,
    .stack = (uptr)stack + sizeof(stack),
    .flags = 0b1111,
    .tags = (uptr)&framebuffer_hdr_tag,
};

void* stivale2_get_tag(struct stivale2_struct* stivale_struct, u64 id)
{
    auto* current_tag = (stivale2_tag*)stivale_struct->tags;

    for (;;) {
        if (current_tag == NULL)
            return NULL;

        if (current_tag->identifier == id)
            return current_tag;

        current_tag = (stivale2_tag*)current_tag->next;
    }
}

extern "C" void kernel_start(stivale2_struct* stivale_struct)
{
    auto fb_tag = (stivale2_struct_tag_framebuffer*)stivale2_get_tag(stivale_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    auto mmap_tag = (stivale2_struct_tag_memmap*)stivale2_get_tag(stivale_struct, STIVALE2_STRUCT_TAG_MEMMAP_ID);

    if (fb_tag->framebuffer_bpp != 32) {
        for (;;)
            asm("hlt");
    }

    Katline::Controller::Framebuffer fb = {
        fb_tag->framebuffer_addr,
        fb_tag->framebuffer_width,
        fb_tag->framebuffer_height,
        fb_tag->framebuffer_pitch,
        fb_tag->framebuffer_bpp,
        (u8*)fb_tag->framebuffer_addr,
    };

    Katline::Memory::MemoryMap mmap = {
        .size = mmap_tag->entries,
        .data = (Katline::Memory::MemoryData*)mmap_tag->memmap,
    };

    Katline::KatlineMain(&fb, &mmap);

    for (;;)
        asm("hlt");
}
