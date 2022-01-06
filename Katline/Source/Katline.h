#pragma once

#include <Controllers/FramebufferController.h>
#include <Controllers/SerialController.h>

namespace Katline {

extern Controller::FramebufferController k_framebuffer_controller;
extern Controller::SerialController k_serial_controller;

void KatlineMain(Controller::Framebuffer* framebuffer);

}
