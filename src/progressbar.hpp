#pragma once
#include <iomanip>
#include <iostream>
#include <stdio.h>

void progressbar_display(std::ostream &os, int value, int max_value, int width,
                         bool display_percent = true);

// Hide the cursor to prevent flickering when updating progressbar
inline void progressbar_hide_cursor() { printf("%s", "\033[?25l"); }

// Show the cursor
inline void progressbar_show_cursor() { printf("%s", "\033[?25h"); }