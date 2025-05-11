#include "display.h"
#include <string.h>
#include <stdio.h>

void draw_circle(uint8_t buffer[], int x0, int y0, int radius, bool set) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius + radius) {
                int px = x0 + x;
                int py = y0 + y;
                if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                    ssd1306_set_pixel(buffer, px, py, set);
                }
            }
        }
    }
}

void draw_background(uint8_t buffer[], Peg pegs[]) {
    for (int y = 0; y < SIMULATION_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            ssd1306_set_pixel(buffer, x, y, false);
        }
    }
    
    for (int i = 0; i < NUM_PEG_ROWS * (NUM_PEG_ROWS + 1) / 2; i++) {
        draw_circle(buffer, (int)pegs[i].x, (int)pegs[i].y, PEG_RADIUS, true);
    }
    
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        ssd1306_set_pixel(buffer, x, SIMULATION_HEIGHT, true);
    }
}

void draw_bin_counters(uint8_t buffer[], int bins[], int total_balls, bool show_bin_percentage) {
    float bin_width = (float)SCREEN_WIDTH / NUM_BINS;

    for (int i = 0; i < NUM_BINS; i++) {
        char text[6];
        if (show_bin_percentage && total_balls > 0) {
            int pct = (bins[i] * 100) / total_balls;
            snprintf(text, sizeof(text), "%d%%", pct);
        } else {
            snprintf(text, sizeof(text), "%d", bins[i]);
        }

        int x_pos = i * bin_width + bin_width/2 - 4;
        int y_pos = SCREEN_HEIGHT - 2;

        for (int x = x_pos-4; x < x_pos+12; x++) {
            for (int y = y_pos-6; y <= y_pos+2; y++) {
                if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
                    ssd1306_set_pixel(buffer, x, y, false);
                }
            }
        }

        ssd1306_draw_string(buffer, x_pos, y_pos, text);
    }
}

void draw_frame(uint8_t buffer[], Ball balls[], Peg pegs[], int bins[], int total_balls, bool show_bin_percentage, bool *need_full_redraw) {
    if (*need_full_redraw) {
        memset(buffer, 0, ssd1306_buffer_length);
        draw_background(buffer, pegs);
        *need_full_redraw = false;
    } else {
        for (int i = 0; i < MAX_BALLS; i++) {
            if (balls[i].active && balls[i].prev_x != -1) {
                draw_circle(buffer, balls[i].prev_x, balls[i].prev_y, BALL_RADIUS+1, false);
                
                for (int j = 0; j < NUM_PEG_ROWS * (NUM_PEG_ROWS + 1) / 2; j++) {
                    float dx = balls[i].prev_x - pegs[j].x;
                    float dy = balls[i].prev_y - pegs[j].y;
                    if (dx*dx + dy*dy < (BALL_RADIUS+2 + PEG_RADIUS)*(BALL_RADIUS+2 + PEG_RADIUS)) {
                        draw_circle(buffer, (int)pegs[j].x, (int)pegs[j].y, PEG_RADIUS, true);
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < MAX_BALLS; i++) {
        if (balls[i].active) {
            draw_circle(buffer, (int)balls[i].x, (int)balls[i].y, BALL_RADIUS, true);
        }
    }
    
    int max_bin = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        if (bins[i] > max_bin) max_bin = bins[i];
    }
    
    float bin_width = (float)SCREEN_WIDTH / NUM_BINS;
    for (int i = 0; i < NUM_BINS; i++) {
        int bar_height = max_bin > 0 ? (HISTOGRAM_HEIGHT * bins[i]) / max_bin : 0;
        
        for (int y = SIMULATION_HEIGHT+1; y < SCREEN_HEIGHT; y++) {
            bool set = (y >= SCREEN_HEIGHT - bar_height);
            for (int x = i*bin_width+1; x < (i+1)*bin_width; x++) {
                ssd1306_set_pixel(buffer, x, y, set);
            }
        }
    }
    
    draw_bin_counters(buffer, bins, total_balls, show_bin_percentage);
    
    char counter_str[16];
    snprintf(counter_str, sizeof(counter_str), "BO:%d", total_balls);
    for (int x = 0; x < 24; x++) {
        for (int y = 0; y < 8; y++) {
            ssd1306_set_pixel(buffer, x, y, false);
        }
    }
    ssd1306_draw_string(buffer, 2, 0, counter_str);
    
    struct render_area area = {0, SCREEN_WIDTH-1, 0, (SCREEN_HEIGHT/8)-1};
    calculate_render_area_buffer_length(&area);
    render_on_display(buffer, &area);
}