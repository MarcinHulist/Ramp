#pragma once

class Display;

namespace Ramp
{
    class Pattern;
    
    namespace PatternDrawer 
    {
        bool DrawPattern(Display& display, const Pattern& pattern);
    }
}
