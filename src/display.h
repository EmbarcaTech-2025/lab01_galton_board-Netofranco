#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"
#include "include/ssd1306.h"

void draw_circle(uint8_t buffer[], int x0, int y0, int radius, bool set);
void draw_background(uint8_t buffer[], Peg pegs[]);
void draw_bin_counters(uint8_t buffer[], int bins[], int total_balls, bool show_bin_percentage);
void draw_frame(uint8_t buffer[], Ball balls[], Peg pegs[], int bins[], int total_balls, bool show_bin_percentage, bool *need_full_redraw);

#endif // DISPLAY_H