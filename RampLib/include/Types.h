#pragma once
#include <cstdint>

namespace Ramp
{
    using RGB565Colour = uint16_t;
    
    struct CornerColours final
    {
        RGB565Colour topLeft = 0;
        RGB565Colour topRight = 0;
        RGB565Colour bottomLeft = 0;
        RGB565Colour bottomRight = 0;
    };
}
