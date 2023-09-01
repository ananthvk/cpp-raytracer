#include "progressbar.hpp"

void progressbar_display(std::ostream &os, int value, int max_value, int width,
                         bool display_percent)
{
    char fill = '=';
    char head = '>';
    char left_end = '[';
    char right_end = ']';

    os << "\r" << left_end;
    double percent = (double)value / max_value;
    os << std::string(percent * width, fill) << head
       << std::string((1 - percent) * width, ' ') << right_end;
    if (display_percent)
    {
        printf("( %0.03f%% )", percent * 100);
    }
    os << std::flush;
}
