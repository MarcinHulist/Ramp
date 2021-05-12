#include "InputParser.h"
#include <cstdlib>
#include <string>
#include <stdexcept>

namespace
{
    constexpr uint8_t displayNameArgumentIndex = 1;
    constexpr uint8_t topLeftCornerArgumentIndex = 2;
    constexpr uint8_t topRightCornerArgumentIndex = 3;
    constexpr uint8_t bottomLeftCornerArgumentIndex = 4;
    constexpr uint8_t bottomRightCornerArgumentIndex = 5;

    int GetBase(const std::string& input) noexcept
    {
        if (input.size() > 2 && (input.rfind("0x") == 0 || input.rfind("0X") == 0) )
        {
            return 16;
        }
        else
        {
            return 10;
        }
    }


    bool ExtractColour(const std::string& input, uint16_t& output)
    {
        output = 0;
        if (input.find(".") != std::string::npos || input.find(",") != std::string::npos )
        {
            return false;
        }

        try
        {
            const auto base = GetBase(input);
            const auto convertedValue = std::stoul(input, nullptr, base);
            if (convertedValue > std::numeric_limits<uint16_t>::max())
            {
                return false;
            }
            else
            {
                output = static_cast<uint16_t>(convertedValue);
                return true;
            }
        }
        catch (const std::invalid_argument&)
        {
            return false;
        }
        catch (const std::out_of_range&)
        {
            return false;
        }
    }

    bool ExtractAllColours(int argc, const char* argv[], Ramp::CornerColours& outColorous)
    {
        const auto topLeftColour = std::string(argv[topLeftCornerArgumentIndex]);
        if (!ExtractColour(topLeftColour, outColorous.topLeft))
        {
            return false;
        }

        const auto topRightColour = std::string(argv[topRightCornerArgumentIndex]);
        if (!ExtractColour(topRightColour, outColorous.topRight))
        {
            return false;
        }

        if (argc > bottomLeftCornerArgumentIndex)
        {
            const auto bottomLeftColour = std::string(argv[bottomLeftCornerArgumentIndex]);
            if (!ExtractColour(bottomLeftColour, outColorous.bottomLeft))
            {
                return false;
            }
        }
        else
        {
            outColorous.bottomLeft = outColorous.topLeft;
        }

        if (argc > bottomRightCornerArgumentIndex)
        {
            const auto bottomRightColour = std::string(argv[bottomRightCornerArgumentIndex]);
            if (!ExtractColour(bottomRightColour, outColorous.bottomRight))
            {
                return false;
            }
        }
        else
        {
            outColorous.bottomRight = outColorous.topRight;
        }

        return true;
    }
}

namespace Ramp
{
    bool InputParser::Parse(int argc, const char* argv[])
    {
        if (argc < 4 || argc > 6 || argv == nullptr)
        {
            return false;
        }
        else
        {
            if (!ExtractAllColours(argc, argv, m_cornerColours))
            {
                m_cornerColours = {};
                m_displayName.clear();
                return false;
            }

            m_displayName = argv[displayNameArgumentIndex];

            return true;
        }
    }

    Ramp::CornerColours InputParser::GetCornerColours() const
    {
        return m_cornerColours;
    }

    const std::string& InputParser::GetDisplayName() const
    {
        return m_displayName;
    }

    std::string& InputParser::GetDisplayName()
    {
        return m_displayName;
    }

    void InputParser::PrintHelpMessage() const 
    {
        printf(
            "The program should be invoked by the following command line:\n"
            "ramp.exe display tl tr [bl] [br]\n"
            "\tdisplay: is the name of the display device.\n"
            "\ttl: is the top left colour value (decimal or hex). Value Range [0 - 65535].\n"
            "\ttr: is the top right colour value (decimal or hex). Value Range [0 - 65535].\n"
            "\tbl: is the bottom left colour value (decimal or hex). Value Range [0 - 65535]. [optional, defaults to tl] \n"
            "\tbr: is the bottom right colour value (decimal or hex). Value Range [0 - 65535]. [optional, defaults to tr]\n");
    }

}
