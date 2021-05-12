#pragma once
#include <vector>

#include "Display.h"
#include "Types.h"

namespace Ramp
{
    RGB565Colour Lerp(const RGB565Colour& colour1, const RGB565Colour& colour2, float t) noexcept;

    class Pattern final
    {
    public:
        Pattern(const Dimension& patternDimensions, CornerColours colours);
        const std::vector<RGB565Colour>& GetPixlesRow(size_t row) const;
        size_t GetNumberOfRows() const noexcept;

    private:
        void GeneratePattern(const Dimension& patternDimensions, CornerColours colours);
        std::vector<std::vector<RGB565Colour>> m_pixels;
    };
    
}
