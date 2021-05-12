#include "catch2/catch.hpp"
#include "Constants.h"
#include "Pattern.h"

using namespace Ramp;

TEST_CASE("Generated pattern dimensions", "[pattern]")
{
    SECTION("Check for diffrent heights")
    {
        constexpr auto patternWidth = 11u;
        const auto patternHeight = static_cast<uint16_t>(GENERATE(0u, 1u, 2u, 10u));
        Pattern pattern{ {patternWidth, patternHeight}, {blackColour, blackColour, blackColour, blackColour} };

        REQUIRE(pattern.GetNumberOfRows() == patternHeight);

        for (auto row = 0u; row < patternHeight; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            REQUIRE(pixels.size() == patternWidth);
        }
    }

    SECTION("Check for diffrent widths")
    {
        const auto patternWidth = static_cast<uint16_t>(GENERATE(0u, 1u, 2u, 10u));
        constexpr auto patternHeight = 11u;
        Pattern pattern{ {patternWidth, patternHeight}, {blackColour, blackColour, blackColour, blackColour} };

        for (auto row = 0u; row < patternHeight; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            REQUIRE(pixels.size() == patternWidth);
        }
    }

    SECTION("Check for diffrent widths and heights")
    {
        const auto patternWidth = static_cast<uint16_t>(GENERATE(0u, 1u, 2u, 10u));
        const auto patternHeight = static_cast<uint16_t>(GENERATE(0u, 1u, 2u, 10u));
        Pattern pattern{ {patternWidth, patternHeight}, {blackColour, blackColour, blackColour, blackColour} };

        REQUIRE(pattern.GetNumberOfRows() == patternHeight);

        for (auto row = 0u; row < patternHeight; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            REQUIRE(pixels.size() == patternWidth);
        }
    }
}


TEST_CASE("Pattern generation single colour", "[pattern]")
{
    SECTION("Single Row")
    {
        constexpr auto patternWidth = 11u;
        constexpr auto patternHeight = 1u;
        const auto colour = GENERATE(blackColour, whiteColour, blueColour, redColour, greenColour, greyColour);
        Pattern pattern{ {patternWidth, patternHeight}, {colour, colour, colour, colour} };
        
        const auto& pixels = pattern.GetPixlesRow(0);
        REQUIRE(pixels.size() == patternWidth);
        for(const auto& pixel : pixels)
        {
            REQUIRE(pixel == colour);
        }
    }

    SECTION("Multiple rows")
    {
        constexpr auto patternWidth = 11u;
        constexpr auto patternHeight = 11u;
        const auto colour = GENERATE(blackColour, whiteColour, blueColour, redColour, greenColour, greyColour);
        Pattern pattern{ {patternWidth, patternHeight}, {colour, colour, colour, colour} };
        for (auto row = 0u; row < patternHeight; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            REQUIRE(pixels.size() == patternWidth);
            for(const auto& pixel : pixels)
            {
                REQUIRE(pixel == colour);
            }
        }
    }
}

TEST_CASE("Pattern generation multi colour interpolation", "[pattern]")
{
    SECTION("Single row different colours at the ends, the same top/bottom")
    {
        constexpr auto patternWidth = 11u;
        constexpr auto patternHeight = 1u;
        const auto& [leftColour, rightColour, middleColour] = GENERATE(blackWhiteWithMiddleColour, whiteBlackWithMiddleColour, redBlackWithMiddleColour, greenBlackWithMiddleColour, blueBlackWithMiddleColour);
        Pattern pattern{ {patternWidth, patternHeight}, {leftColour, rightColour, leftColour, rightColour} };

        const auto& pixels = pattern.GetPixlesRow(0);

        REQUIRE(pixels.front() == leftColour);
        REQUIRE(pixels.back() == rightColour);
        REQUIRE(pixels[pixels.size() / 2] == middleColour);
    }

    SECTION("Single row differen top and bottom colours")
    {
        constexpr auto patternWidth  = 11u;
        constexpr auto patternHeight =  1u;
        const auto&[topColour, bottomColour, middleColour] = GENERATE(blackWhiteWithMiddleColour, whiteBlackWithMiddleColour);
        Pattern pattern{ {patternWidth, patternHeight}, {topColour, topColour, bottomColour, bottomColour} };

        const auto& pixels = pattern.GetPixlesRow(0);

        REQUIRE(pixels.front() == middleColour);
        REQUIRE(pixels.back() == middleColour);
    }

    SECTION("Single column differen left and right colours")
    {
        constexpr auto patternWidth  =  1u;
        constexpr auto patternHeight = 11u;
        const auto&[leftColour, rightColour, middleColour] = GENERATE(blackWhiteWithMiddleColour, whiteBlackWithMiddleColour);
        Pattern pattern{ {patternWidth, patternHeight}, {leftColour, rightColour, leftColour, rightColour} };

        for (auto row = 0u; row < patternHeight; ++row) {
          const auto& pixels = pattern.GetPixlesRow(row);
          for (const auto& pixel : pixels) {
            REQUIRE(pixels.front() == middleColour);
            REQUIRE(pixels.size() == patternWidth);

          }
        }
    }

    SECTION("Single row colour to black")
    {
        const auto& [endColour, colourMask] = GENERATE(redColourWithMask, greenColourWithMask, blueColourWithMask);
        constexpr auto patternWidth  = 11u;
        constexpr auto patternHeight =  1u;
        Pattern pattern{ {patternWidth, patternHeight}, {blackColour, endColour, blackColour, endColour} };
        for (auto row = 0u; row < patternHeight; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            for (const auto& pixel : pixels)
            {
                REQUIRE((pixel &~colourMask) == 0);
            }
        }
    }

    SECTION("Multiple row")
    {
        constexpr auto patternWidth  = 11u;
        constexpr auto patternHeight = 11u;
        const auto&[leftColour, rightColour, middleColour] = GENERATE(blackWhiteWithMiddleColour, whiteBlackWithMiddleColour, redBlackWithMiddleColour, greenBlackWithMiddleColour, blueBlackWithMiddleColour);
        Pattern pattern{ {patternWidth, patternHeight}, {leftColour, rightColour, leftColour, rightColour} };
               
        for (auto row = 0u; row < patternHeight; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            for (const auto& pixel : pixels)
            {
                REQUIRE(pixels.front() == leftColour);
                REQUIRE(pixels.back() == rightColour);
                REQUIRE(pixels[pixels.size() / 2] == middleColour);
            }
        }
    }

    SECTION("Multiple row black to colour")
    {
        const auto&[endColour, colourMask] = GENERATE(redColourWithMask, greenColourWithMask, blueColourWithMask);
        constexpr auto patternWidth  = 11u;
        constexpr auto patternHeight = 11u;
        Pattern pattern{ {patternWidth, patternHeight}, {blackColour, endColour, blackColour, endColour} };
        for (auto row = 0u; row < patternHeight; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            for (const auto& pixel : pixels)
            {
                REQUIRE((pixel &~colourMask) == 0);
            }
        }
    }

    SECTION("Multiple row diffrent colours top/bottom and left/right")
    {
        const auto corners = GENERATE(allCornersDiffrentColours1, allCornersDiffrentColours2, allCornersDiffrentColours3, allCornersDiffrentColours4);
        constexpr auto patternWidth  = 8u;
        constexpr auto patternHeight = 8u;
        Pattern pattern{ {patternWidth, patternHeight}, corners };
        for (auto row = 1u; row < patternHeight -1; ++row)
        {
            const auto& pixels = pattern.GetPixlesRow(row);
            for (auto column = 1u; column < pixels.size() - 1; ++column)
            {
                CAPTURE(row, column, pixels[column], corners);
                REQUIRE((pixels[column] & redColourMask) != 0);
                REQUIRE((pixels[column] & greenColourMask) != 0);
                REQUIRE((pixels[column] & blueColourMask) != 0);
            }
        }
    }
}

TEST_CASE("Pattern without one dimmension", "[pattern]")
{
    SECTION("Zero width")
    {
        constexpr auto patternWidth = 0u;
        constexpr auto patternHeight = 11u;
        const auto colour = GENERATE(blackColour, whiteColour, blueColour, redColour, greenColour, greyColour);
        Pattern pattern{ {patternWidth, patternHeight}, {colour, colour, colour, colour} };

        const auto& pixels = pattern.GetPixlesRow(0);
        REQUIRE(pixels.size() == 0);
    }

    SECTION("Zero height")
    {
        constexpr auto patternWidth = 11u;
        constexpr auto patternHeight = 0u;
        const auto colour = GENERATE(blackColour, whiteColour, blueColour, redColour, greenColour, greyColour);
        Pattern pattern{ {patternWidth, patternHeight}, {colour, colour, colour, colour} };
        
        const auto& pixels = pattern.GetPixlesRow(0);
        REQUIRE(pixels.size() == 0);

    }
}

