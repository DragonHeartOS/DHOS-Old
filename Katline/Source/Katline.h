#pragma once

#include <Controllers/FramebufferController.h>

namespace Katline {

extern KGraphics::FramebufferController k_framebuffer_controller;

void KatlineMain(KGraphics::Framebuffer* framebuffer);

}
