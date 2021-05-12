#include "catch2/catch.hpp"
#include "Constants.h"
#include "Pattern.h"

using namespace Ramp;

TEST_CASE("Lerp Colour", "[RGB565Colour]")
{
    SECTION("Half mixed colours")
    {
        const auto& [colour1, colour2, halfMixedColour] = GENERATE(blackWhiteWithMiddleColour, redBlackWithMiddleColour, greenBlackWithMiddleColour, blueBlackWithMiddleColour);
        
        const auto lerp = Lerp(colour1, colour2, 0.5f);
        REQUIRE(lerp == halfMixedColour);
    }

    SECTION("First colour")
    {
        const auto colour1 = GENERATE(blackColour, whiteColour, redColour, greenColour, blueColour);
        const auto colour2 = GENERATE(blackColour, whiteColour, redColour, greenColour, blueColour);

        const auto lerp = Lerp(colour1, colour2, 0.0f);
        REQUIRE(lerp == colour1);
    }

    SECTION("Second colour")
    {
        const auto colour1 = GENERATE(blackColour, whiteColour, redColour, greenColour, blueColour);
        const auto colour2 = GENERATE(blackColour, whiteColour, redColour, greenColour, blueColour);

        const auto lerp = Lerp(colour1, colour2, 1.0f);
        REQUIRE(lerp == colour2);
    }
}
