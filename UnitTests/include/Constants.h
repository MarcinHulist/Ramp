#pragma once
#include "Types.h"

constexpr Ramp::RGB565Colour blackColour = static_cast<Ramp::RGB565Colour>(0x0000);
constexpr Ramp::RGB565Colour whiteColour = static_cast<Ramp::RGB565Colour>(0xFFFF);
constexpr Ramp::RGB565Colour blueColour  = static_cast<Ramp::RGB565Colour>(0x001F);
constexpr Ramp::RGB565Colour redColour   = static_cast<Ramp::RGB565Colour>(0xF800);
constexpr Ramp::RGB565Colour greenColour = static_cast<Ramp::RGB565Colour>(0x07E0);
constexpr Ramp::RGB565Colour greyColour  = static_cast<Ramp::RGB565Colour>(0x8410);


constexpr auto blackWhiteWithMiddleColour = std::tuple<uint16_t, uint16_t, uint16_t>{ blackColour, whiteColour, static_cast<uint16_t>(0x8410) };
constexpr auto whiteBlackWithMiddleColour = std::tuple<uint16_t, uint16_t, uint16_t>{ whiteColour, blackColour, static_cast<uint16_t>(0x7BEF) };
constexpr auto redBlackWithMiddleColour   = std::tuple<uint16_t, uint16_t, uint16_t>{ redColour,   blackColour, static_cast<uint16_t>(0x7800) };
constexpr auto greenBlackWithMiddleColour = std::tuple<uint16_t, uint16_t, uint16_t>{ greenColour, blackColour, static_cast<uint16_t>(0x03E0) };
constexpr auto blueBlackWithMiddleColour  = std::tuple<uint16_t, uint16_t, uint16_t>{ blueColour,  blackColour, static_cast<uint16_t>(0x000F) };

constexpr auto redColourMask   = static_cast<uint16_t>(0xF800);
constexpr auto greenColourMask = static_cast<uint16_t>(0x07E0);
constexpr auto blueColourMask  = static_cast<uint16_t>(0x001F);

constexpr auto redColourWithMask   = std::tuple<uint16_t, uint16_t>{ redColour,   redColourMask };
constexpr auto greenColourWithMask = std::tuple<uint16_t, uint16_t>{ greenColour, greenColourMask };
constexpr auto blueColourWithMask  = std::tuple<uint16_t, uint16_t>{ blueColour,  blueColourMask };

const Ramp::CornerColours allCornersDiffrentColours1 = { redColour, greenColour, blueColour, blackColour };
const Ramp::CornerColours allCornersDiffrentColours2 = { blackColour, redColour, greenColour, blueColour };
const Ramp::CornerColours allCornersDiffrentColours3 = { blueColour, blackColour, redColour, greenColour };
const Ramp::CornerColours allCornersDiffrentColours4 = { greenColour, blueColour, blackColour, redColour };
