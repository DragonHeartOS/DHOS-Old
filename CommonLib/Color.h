#pragma once

#include <cstdint>

#include <CommonLib/Common.h>

namespace Color {

struct RGBColor {
    u8 r, g, b;
};

RGBColor const WHITE = { 0xff, 0xff, 0xff };
RGBColor const BLACK = { 0x00, 0x00, 0x00 };

}
