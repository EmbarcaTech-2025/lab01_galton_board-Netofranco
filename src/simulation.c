#include "simulation.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void init_pegs(Peg pegs[]) {
    int peg_index = 0;
    float start_y = 8.0f;
    float vertical_spacing = 6.0f;
    float horizontal_spacing = 12.0f;

    for (int row = 0; row < NUM_PEG_ROWS; row++) {
        int pegs_in_row = row + 1;
        float row_width = horizontal_spacing * (pegs_in_row - 1);
        float start_x = (SCREEN_WIDTH - row_width) / 2.0f;
        float y = start_y + row * vertical_spacing;

        for (int i = 0; i < pegs_in_row; i++) {
            pegs[peg_index].x = start_x + i * horizontal_spacing;
            pegs[peg_index].y = y;
            peg_index++;
        }
    }
}

void add_ball(Ball balls[], int *total_balls) {
    for (int i = 0; i < MAX_BALLS; i++) {
        if (!balls[i].active) {
            balls[i].x = SCREEN_WIDTH / 2 + (rand() % 9 - 4);
            balls[i].y = 3;
            balls[i].vx = (rand() % 5 - 2) * 0.12f;
            balls[i].vy = 0.15f + (rand() % 10) * 0.02f;
            balls[i].active = true;
            balls[i].bin = -1;
            balls[i].prev_x = -1;
            balls[i].prev_y = -1;
            (*total_balls)++;
            break;
        }
    }
}

void update_balls(Ball balls[], Peg pegs[], int bins[], int bias, bool *need_full_redraw) {
    for (int i = 0; i < MAX_BALLS; i++) {
        if (balls[i].active) {
            balls[i].prev_x = (int)balls[i].x;
            balls[i].prev_y = (int)balls[i].y;
            
            balls[i].x += balls[i].vx;
            balls[i].y += balls[i].vy;
            
            for (int j = 0; j < NUM_PEG_ROWS * (NUM_PEG_ROWS + 1) / 2; j++) {
                float dx = balls[i].x - pegs[j].x;
                float dy = balls[i].y - pegs[j].y;
                float distance = sqrtf(dx*dx + dy*dy);
                
                if (distance < BALL_RADIUS + PEG_RADIUS) {
                    balls[i].vx = (rand() % 100 < bias) ? 0.5f : -0.5f;
                    balls[i].vy = fabsf(balls[i].vy) * 0.5f;
                    break;
                }
            }
            
            if (balls[i].x < BALL_RADIUS) {
                balls[i].x = BALL_RADIUS;
                balls[i].vx *= -0.6f;
            } else if (balls[i].x > SCREEN_WIDTH - BALL_RADIUS) {
                balls[i].x = SCREEN_WIDTH - BALL_RADIUS;
                balls[i].vx *= -0.6f;
            }
            
            if (balls[i].y > SIMULATION_HEIGHT - BALL_RADIUS) {
                balls[i].active = false;
                int bin = (int)(balls[i].x / (SCREEN_WIDTH / NUM_BINS));
                bin = bin < 0 ? 0 : (bin >= NUM_BINS ? NUM_BINS - 1 : bin);
                bins[bin]++;
                *need_full_redraw = true;
            }
            
            balls[i].vy += 0.04f;
            if (balls[i].vy > 1.2f) balls[i].vy = 1.2f;
        }
    }
}