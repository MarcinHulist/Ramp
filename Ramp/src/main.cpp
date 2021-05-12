#include "InputParser.h"
#include "Display.h"
#include "Pattern.h"
#include "PatternDrawer.h"
#include "Types.h"

int main(int argc, const char* argv[])
{
    Ramp::InputParser inputParser;
    if (inputParser.Parse(argc, argv))
    {
        Display display(inputParser.GetDisplayName());
        
        const auto cornerColours = inputParser.GetCornerColours();
        const auto dimensions = display.size();

        Ramp::Pattern pattern(dimensions, cornerColours);

        if (!Ramp::PatternDrawer::DrawPattern(display, pattern))
        {
            printf("Failed to draw pattern on the display.\n");
            return 1;
        }

        display.present();
    }
    else
    {
        inputParser.PrintHelpMessage();
    }
    
    return 0;
}
