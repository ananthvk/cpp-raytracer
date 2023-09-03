// MIT License
//
// Copyright (c) 2023 Ananthanarayanan Venkitakrishnan (https://github.com/ananthvk)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once
#include <iomanip>
#include <iostream>
#include <stdio.h>

// A class which represents an ASCII progressbar
class ProgressBar
{
  private:
    int value;
    int max_value;
    int width;
    bool display_percent;

  public:
    /// @brief Constructor for progressbar
    /// @param max_value
    /// @param width
    /// @param display_percent
    ProgressBar(int max_value, int width, bool display_percent = true)
        : value(0), max_value(max_value), width(width), display_percent(display_percent)
    {
    }

    /// @brief Updates the value of progressbar by given amount
    /// @param dt the amount by which the progressbar value has to be increased
    void tick(int dt = 1) { value += dt; }

    /// @brief Display the progressbar on the passed stream
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

    /// @brief Hide the cursor to prevent flickering when updating progressbar
    void hide_cursor(std::ostream &os) { os << "\033[?25l"; }

    /// @brief Show the cursor
    void show_cursor(std::ostream &os) { os << "\033[?25h"; }
};