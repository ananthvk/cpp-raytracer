#pragma once
#include <iomanip>
#include <iostream>
#include <stdio.h>

class ProgressBar
{
  private:
    int value;
    int max_value;
    int width;
    bool display_percent;

  public:
    ProgressBar(int max_value, int width, bool display_percent = true)
        : value(0), max_value(max_value), width(width), display_percent(display_percent)
    {
    }

    void tick(int dt = 1) { value += dt; }

    void display(std::ostream &os)
    {
        char fill = '=';
        char head = '>';
        char left_end = '[';
        char right_end = ']';

        os << "\r" << left_end;
        double percent = (double)value / max_value;
        os << std::string(percent * width, fill) << head << std::string((1 - percent) * width, ' ')
           << right_end;
        if (display_percent)
        {
            printf("( %0.03f%% )", percent * 100);
        }
        os << std::flush;
    }

    // Hide the cursor to prevent flickering when updating progressbar
    void hide_cursor(std::ostream &os) { os << "\033[?25l"; }

    // Show the cursor
    void show_cursor(std::ostream &os) { os << "\033[?25h"; }
};