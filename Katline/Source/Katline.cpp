#include "Controllers/SerialController.h"
#include "Debug.h"
#include <cstddef>
#include <cstdint>

#include <Katline.h>

namespace Katline {

Controller::FramebufferController k_framebuffer_controller = NULL;
Controller::SerialController k_serial_controller;

void KatlineMain(Controller::Framebuffer* framebuffer)
{
    k_framebuffer_controller = Controller::FramebufferController(framebuffer);

    k_serial_controller.Init();

    Debug::WriteFormatted("Among us?!?!?!?!? %d", 23467824768);
}

}
