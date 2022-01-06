#pragma once

#include <cstdint>

namespace Color {

struct RGBColor {
    uint8_t r, g, b;
};

const RGBColor WHITE = { 0xff, 0xff, 0xff };
const RGBColor BLACK = { 0x00, 0x00, 0x00 };

}
