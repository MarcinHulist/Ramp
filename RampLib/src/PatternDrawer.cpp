#include "PatternDrawer.h"

#include "Display.h"
#include "Pattern.h"

namespace Ramp
{

bool PatternDrawer::DrawPattern(Display& display, const Pattern& pattern) 
{
    const auto displayDimensions = display.size();

    if (displayDimensions.height < pattern.GetNumberOfRows())
    {
        return false;
    }

    const auto x = 0;

    for (uint16_t row = 0u; row < pattern.GetNumberOfRows(); ++row)
    {
        const auto& pixels = pattern.GetPixlesRow(row);
        
        if (pixels.size() > displayDimensions.width)
        {
            return false;
        }
    
        const auto y = static_cast<int16_t>(row);
        display.draw({ x, y}, pixels.data(), static_cast<uint16_t>(pixels.size()));
    }

    return true;
}

}