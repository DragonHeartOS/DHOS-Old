#include <bits/stdint-uintn.h>
#include <cstddef>
#include <cstdint>

#include <stivale/stivale2.h>

#include <Controllers/FramebufferController.h>
#include <Katline.h>

static std::uint8_t stack[8192];

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
    .entry_point = (uint64_t)&kernel_start,
    .stack = (std::uintptr_t)stack + sizeof(stack),
    .flags = 0b1111,
    .tags = (std::uintptr_t)&framebuffer_hdr_tag,
};

void* stivale2_get_tag(struct stivale2_struct* stivale_struct, uint64_t id)
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
        (uint8_t*)fb_tag->framebuffer_addr,
    };

    Katline::KatlineMain(&fb);

    for (;;)
        asm("hlt");
}
