#include <cstddef>
#include <cstdint>

#include <Katline.h>

namespace Katline {

KGraphics::FramebufferController k_framebuffer_controller = NULL;

void KatlineMain(KGraphics::Framebuffer *framebuffer)
{
    k_framebuffer_controller = KGraphics::FramebufferController(framebuffer);

    k_framebuffer_controller.PutStringSafe("Hello framebuffer text rendering!", 33);
}

}
