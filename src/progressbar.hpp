#pragma once
#include <iomanip>
#include <iostream>
#include <stdio.h>

void progressbar_display(std::ostream &os, int value, int max_value, int width,
                       bool display_percent = true)
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
        printf("( %0.2f%% )", percent * 100);
    }
    os << std::flush;
}

// Hide the cursor to prevent flickering when updating progressbar
void progressbar_hide_cursor() { printf("%s", "\033[?25l"); }

// Show the cursor
void progressbar_show_cursor() { printf("%s", "\033[?25h"); }