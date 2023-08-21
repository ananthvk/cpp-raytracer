#pragma once
#include <iomanip>
#include <iostream>
#include <stdio.h>

void print_progressbar(std::ostream &os, int value, int max_value, int width,
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
    printf("( %0.2f%% )", percent * 100);
    os << std::flush;
}