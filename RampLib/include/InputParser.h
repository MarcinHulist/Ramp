#pragma once
#include <string>

#include "Types.h"

namespace Ramp
{
    class InputParser final
    {
    public:
        bool Parse(int argc, const char* argv[]);
        CornerColours GetCornerColours() const;
        const std::string& GetDisplayName() const;
        std::string& GetDisplayName();
        void PrintHelpMessage() const;
    
    private:
        CornerColours m_cornerColours;
        std::string m_displayName;
    };
}
