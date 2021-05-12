#include <iomanip>

#include "InputParser.h"
#include "catch2/catch.hpp"
#include <cstring>

using namespace Ramp;

namespace
{
    constexpr auto applicationName = "ramps.exe";
    constexpr auto whiteColourDecimal = std::tuple<const char*, uint16_t>{ "65535", 65535 };
    constexpr auto blackColourDecimal = std::tuple<const char*, uint16_t>{ "0", 0 };
    constexpr auto randomColourDecimal = std::tuple<const char*, uint16_t>{ "1200", 1200 };
    constexpr auto whiteColourHex = std::tuple<const char*, uint16_t>{ "0xFFFF", 65535 };
    constexpr auto blackColourHex = std::tuple<const char*, uint16_t>{ "0x0", 0 };
    constexpr auto randomColourHex = std::tuple<const char*, uint16_t>{ "0x4B0", 1200 };
    constexpr auto displayName = "displayName";


}

namespace Ramp
{
    bool operator==(const CornerColours& lhs, const CornerColours& rhs)
    {
        return lhs.bottomLeft == rhs.bottomLeft && lhs.bottomRight == rhs.bottomRight && lhs.topLeft == rhs.topLeft && rhs.topRight == lhs.topRight;
    }

    static std::ostream& align(std::ostream& os)
    {
        os << std::setw(12) << std::fixed << std::right;
        return os;
    }

    static std::ostream& operator<<(std::ostream& os, const CornerColours& colours)
    {
        os << "TL: " << align << colours.topLeft << ", TR: " << align << colours.topRight << ", BL: " << align << colours.bottomLeft << align << ", BR: " << colours.bottomRight << "\n";
        return os;
    }
}



TEST_CASE("Input should be parrsed", "[InputParser]")
{
    const auto [firstColourString, firstColourValue] = GENERATE(whiteColourDecimal, randomColourDecimal, blackColourDecimal, whiteColourHex, blackColourHex, randomColourHex);

    InputParser inputParser;
    SECTION("Two corrners and display name passed")
    {
        const auto [secondColourString, secondColourValue] = GENERATE(whiteColourDecimal, randomColourDecimal, blackColourDecimal, whiteColourHex, blackColourHex, randomColourHex);
        const auto outputColour = CornerColours { firstColourValue, secondColourValue, firstColourValue, secondColourValue };
        
        const char* input[] = {applicationName, displayName, firstColourString, secondColourString };
        const int numberOfElements = sizeof(input)/sizeof(const char*);

        REQUIRE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == outputColour);
        REQUIRE(std::strcmp(inputParser.GetDisplayName().c_str(), displayName) == 0);
    }

    SECTION("Three corrners and display name passed")
    {
        const auto[secondColourString, secondColourValue] = GENERATE(whiteColourDecimal, randomColourDecimal, blackColourDecimal, whiteColourHex, blackColourHex, randomColourHex);
        const auto[thirdColourString, thirdColourValue] = GENERATE(whiteColourDecimal, randomColourDecimal, blackColourDecimal, whiteColourHex, blackColourHex, randomColourHex);
        const auto outputColour = CornerColours{ firstColourValue, secondColourValue, thirdColourValue, secondColourValue };

        const char* input[] = { applicationName, displayName, firstColourString, secondColourString, thirdColourString };
        const int numberOfElements = sizeof(input)/sizeof(const char*);
        
        REQUIRE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == outputColour);
        REQUIRE(std::strcmp(inputParser.GetDisplayName().c_str(), displayName) == 0);
    }

    SECTION("Four corrners and display name passed")
    {
        const auto[secondColourString, secondColourValue] = GENERATE(whiteColourDecimal, randomColourDecimal, blackColourDecimal, whiteColourHex, blackColourHex, randomColourHex);
        const auto[thirdColourString, thirdColourValue] = GENERATE(whiteColourDecimal, randomColourDecimal, blackColourDecimal, whiteColourHex, blackColourHex, randomColourHex);
        const auto[fourthColourString, fourthColourValue] = GENERATE(whiteColourDecimal, randomColourDecimal, blackColourDecimal, whiteColourHex, blackColourHex, randomColourHex);
        const auto outputColour = CornerColours{ firstColourValue, secondColourValue, thirdColourValue, fourthColourValue };

        const char* input[] = { applicationName, displayName, firstColourString, secondColourString, thirdColourString, fourthColourString };
        const int numberOfElements = sizeof(input)/sizeof(const char*);

        REQUIRE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == outputColour);
        REQUIRE(std::strcmp(inputParser.GetDisplayName().c_str(), displayName) == 0);
    }
}

TEST_CASE("Input should not be parrsed", "[InputParser]")
{
    InputParser inputParser;

    SECTION("No arguments are passed")
    {
        const char* input[] = { nullptr };
        int numberOfElements = 0;
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Only app name is passed")
    {
        const char* input[] = { applicationName};
        const int numberOfElements = sizeof(input)/sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Only display name passed")
    {
        const char* input[] = { applicationName, displayName };
        const int numberOfElements = sizeof(input)/sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Display name passed and one colour")
    {
        const char* input[] = { applicationName, displayName, "0" };
        const int numberOfElements = sizeof(input)/sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Display name and both colors as stings are passed")
    {
        const char* input[] = { applicationName, displayName, "a", "b" };
        const int numberOfElements = sizeof(input)/sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Display name and second color as sting are passed")
    {
        const char* input[] = { applicationName, displayName, "0", "a" };
        const int numberOfElements = sizeof(input)/sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Display name and third color as sting are passed")
    {
        const char* input[] = { applicationName, displayName, "0", "0", "a" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Display name and fourth color as sting are passed")
    {
        const char* input[] = { applicationName, displayName, "0", "0", "0", "a" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Too many arguments are passed")
    {
        const char* input[] = { applicationName, displayName, std::get<0>(whiteColourDecimal), std::get<0>(blackColourDecimal), "invalidParameter"};
        const int numberOfElements = sizeof(input)/sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("One colour is negative")
    {
        const char* input[] = { applicationName, displayName, "0", "-1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Two colours are negative")
    {
        const char* input[] = { applicationName, displayName, "-10", "-1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Three colours are negative")
    {
        const char* input[] = { applicationName, displayName, "-10", "-1", "-100" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Four colours are negative")
    {
        const char* input[] = { applicationName, displayName, "-10", "-1", "-100", "-200" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("One colour is to big")
    {
        const char* input[] = { applicationName, displayName, "70000", "1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Two colours are to big")
    {
        const char* input[] = { applicationName, displayName, "80000", "70000" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Three colours are to big")
    {
        const char* input[] = { applicationName, displayName, "90000", "80000", "70000" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Four colours are to big")
    {
        const char* input[] = { applicationName, displayName, "100000", "90000", "80000", "70000" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("One colour is to big HEX")
    {
        const char* input[] = { applicationName, displayName, "0xFFFFFFF", "1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Two colours are to big")
    {
        const char* input[] = { applicationName, displayName, "0xFFFFFFF", "0xFFFFFFF" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Three colours are to big")
    {
        const char* input[] = { applicationName, displayName, "0xFFFFFFF", "0xFFFFFFF", "0xFFFFFFF" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Four colours are to big")
    {
        const char* input[] = { applicationName, displayName, "0xFFFFFFF", "0xFFFFFFF", "0xFFFFFFF", "0xFFFFFFF" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("One colour is float")
    {
        const char* input[] = { applicationName, displayName, "1.1", "1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Two colours are float")
    {
        const char* input[] = { applicationName, displayName, "1.1", "1.1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Three colours are float")
    {
        const char* input[] = { applicationName, displayName, "1.1", "1.1", "1.1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }

    SECTION("Four colours are float")
    {
        const char* input[] = { applicationName, displayName, "1.1", "1.1", "1.1", "1.1" };
        const int numberOfElements = sizeof(input) / sizeof(const char*);
        REQUIRE_FALSE(inputParser.Parse(numberOfElements, input));
        REQUIRE(inputParser.GetCornerColours() == CornerColours{});
        REQUIRE(inputParser.GetDisplayName().empty());
    }
}
