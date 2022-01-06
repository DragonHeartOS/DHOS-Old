#include <bits/stdint-uintn.h>
#include <cstdint>
#include <cstddef>

#include <stivale/stivale2.h>

#include <Controllers/FramebufferController.h>
#include <Katline.h>

static std::uint8_t stack[8192];

extern "C" void kernel_start(stivale2_struct*);

static stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },
    .flags = 0
};

static stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t) &terminal_hdr_tag
    },
    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0,
};

__attribute__((section(".stivale2hdr"), used))
static stivale2_header stivale_hdr = {
    .entry_point = (uint64_t) &kernel_start,
    .stack = (std::uintptr_t) stack + sizeof(stack),
    .flags = 0b1111,
    .tags = (std::uintptr_t) &framebuffer_hdr_tag,
};

void *stivale2_get_tag(struct stivale2_struct *stivale_struct, uint64_t id) {
    auto *current_tag = (stivale2_tag*) stivale_struct->tags;

    for (;;) {
        if (current_tag == NULL)
            return NULL;
        
        if (current_tag->identifier == id)
            return current_tag;

        current_tag = (stivale2_tag*) current_tag->next;
    }
}

extern "C" void kernel_start(stivale2_struct *stivale_struct) {
    auto term_str_tag = (stivale2_struct_tag_terminal*) stivale2_get_tag(stivale_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
 
    if (term_str_tag == NULL)
        for (;;)
            asm ("hlt");
 
    void (*term_write)(const char *string, size_t length) = (void (*)(const char*, size_t)) term_str_tag->term_write;

    auto fb_tag = (stivale2_struct_tag_framebuffer*) stivale2_get_tag(stivale_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
 
    term_write("Hello Katline! Now booting...", 29);

    if (fb_tag->framebuffer_bpp != 32) {
        term_write("Unsuported BPP! Halting...", 26);
        for (;;)
            asm ("hlt");
    }
    
    KGraphics::Framebuffer fb = {
        fb_tag->framebuffer_addr,
        fb_tag->framebuffer_width,
        fb_tag->framebuffer_height,
        fb_tag->framebuffer_pitch,
        fb_tag->framebuffer_bpp,
        (uint8_t*) fb_tag->framebuffer_addr,
    };

    Katline::KatlineMain(&fb);
 
    for (;;)
        asm ("hlt");
}
