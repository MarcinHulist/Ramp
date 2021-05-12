#include "Pattern.h"
#include <cmath>

namespace
{
    static const std::vector<uint16_t> invalidRow;
}

namespace Ramp
{

RGB565Colour Lerp(const RGB565Colour& colour1, const RGB565Colour& colour2, float t) noexcept
{
    struct RGBColour
    {
        using SingleChannelColour = int8_t;
        SingleChannelColour r;
        SingleChannelColour g;
        SingleChannelColour b;

        RGBColour(RGB565Colour colour) noexcept
            : r(static_cast<SingleChannelColour>(colour >> 11))
            , g(static_cast<SingleChannelColour>((colour >> 5) & 0x3f))
            , b(static_cast<SingleChannelColour>(colour & 0x1f))
        {}

        RGBColour(SingleChannelColour r, SingleChannelColour g, SingleChannelColour b) noexcept
            : r(r)
            , g(g)
            , b(b)
        {}


        RGBColour operator-(const RGBColour& other) const noexcept
        {
            return RGBColour(r - other.r, g - other.g, b - other.b);
        }

        RGBColour operator+(const RGBColour& other) const noexcept
        {
            return RGBColour(r + other.r, g + other.g, b + other.b);
        }

        RGBColour operator*(float value) const noexcept
        {
            return RGBColour(static_cast<int8_t>(std::round(r * value)), static_cast<int8_t>(std::round(g * value)), static_cast<int8_t>(std::round(b * value)));
        };

    };

    const RGBColour first{ colour1 };
    const RGBColour second{ colour2 };

    const auto lerp = first + (second - first) * t;

    return static_cast<RGB565Colour>((lerp.r << 11) + (lerp.g << 5) + lerp.b);
}

Pattern::Pattern(const Dimension& patternDimensions, CornerColours colours)
{
    GeneratePattern(patternDimensions, std::move(colours));
}

const std::vector<uint16_t>& Pattern::GetPixlesRow(size_t row) const 
{
    if (row >= m_pixels.size())
    {
        return invalidRow;
    }
    else
    {
        return m_pixels[row];
    }
}

void Pattern::GeneratePattern(const Dimension& patternDimensions, CornerColours colours)
{
    if (patternDimensions.height == 0)
    {
        return;
    }

    m_pixels.resize(patternDimensions.height);
    
    if (patternDimensions.width == 0) 
    {
        return;
    }

    if (patternDimensions.height == 1 && (colours.topLeft != colours.bottomLeft || colours.topRight != colours.bottomRight))
    {
        colours.topLeft = colours.bottomLeft = Ramp::Lerp(colours.topLeft, colours.bottomLeft, 0.5f);
        colours.topRight = colours.bottomRight = Ramp::Lerp(colours.topRight, colours.bottomRight, 0.5f);
    }

    for (auto row = 0u; row < m_pixels.size(); ++row)
    {
        auto& pixelRow = m_pixels[row];
        pixelRow.reserve(patternDimensions.width);
        const float t = patternDimensions.height > 1 ? row / static_cast<float>(patternDimensions.height - 1) : 1.0f;
        const auto leftColour = Ramp::Lerp(colours.topLeft, colours.bottomLeft, t);
        const auto rightColour = Ramp::Lerp(colours.topRight, colours.bottomRight, t);
        
        if (patternDimensions.width == 1)
        {
            pixelRow.emplace_back(Ramp::Lerp(leftColour, rightColour, 0.5f));
        }
        else
        {
            for (auto column = 0u; column < patternDimensions.width; ++column)
            {
                pixelRow.emplace_back(Ramp::Lerp(leftColour, rightColour, column / static_cast<float>(patternDimensions.width - 1)));
            }
        }
    }
}

size_t Pattern::GetNumberOfRows() const noexcept 
{
    return m_pixels.size();
}

}