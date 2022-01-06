#include "Font.h"
#include <CommonLib/Math.h>
#include <Controllers/FramebufferController.h>
#include <cstddef>

namespace KGraphics {

FramebufferController::FramebufferController(Framebuffer *framebuffer)
    : m_framebuffer(framebuffer)
{
    this->m_framebuffer = framebuffer;
}

void FramebufferController::PlotPixel(uint y, uint x)
{
    if (y > m_framebuffer->height - 1)
        y = m_framebuffer->height - 1;
    if (x > m_framebuffer->width - 1)
        x = m_framebuffer->width - 1;

    auto fb = m_framebuffer->data +
        x * 4 +                  // X
        y * m_framebuffer->pitch // Y
    ;

    fb[0] = color.b;
    fb[1] = color.g;
    fb[2] = color.r;
    fb[3] = 0xff;
}

void FramebufferController::Rect(uint y1, uint x1, uint y2, uint x2)
{
    if (x1 > x2) {
        uint temp_x = x1;
        x1 = x2;
        x2 = temp_x;
    }

    if (y1 > y2) {
        uint temp_y = y1;
        y1 = y2;
        y2 = temp_y;
    }

    for (uint i=y1; i < y2; i++)
        for (uint j=x1; j < x2; j++)
            PlotPixel(i, j);
}

void FramebufferController::DrawRawCharacter(char ch, uint y, uint x, bool inverted)
{
    for (uint temp_y = 0; temp_y < 8; temp_y++) {
        for (uint temp_x = 0; temp_x < 8; temp_x++) {
            auto character = Katline::Font::KernelFontStd[(uint) ch * 8 + temp_y];
            character = (character >> temp_x) & 1;
            if (character == (!inverted))
                PlotPixel(temp_y + y, x + 8 - temp_x);
        }
    }
}

void FramebufferController::DrawCharacter(char ch, bool inverted)
{
    DrawRawCharacter(ch, (uint) cursor_position.Y(), (uint) cursor_position.X(), inverted);
}

void FramebufferController::PutCharacter(char ch, bool inverted)
{
    DrawCharacter(ch, inverted);

    cursor_position.SetX(cursor_position.X() + 8);

    if (cursor_position.X() > m_framebuffer->width) {
        cursor_position.SetX(0);
        cursor_position.SetY(cursor_position.Y() + 8);
    }
}

void FramebufferController::PutStringSafe(const char * string, size_t size, bool inverted)
{
    for (size_t i = 0; i < size; i++)
        PutCharacter(string[i]);
}

}
