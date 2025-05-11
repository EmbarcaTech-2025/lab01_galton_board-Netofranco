#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"

void init_pegs(Peg pegs[]);
void add_ball(Ball balls[], int *total_balls);
void update_balls(Ball balls[], Peg pegs[], int bins[], int bias, bool *need_full_redraw);

#endif // SIMULATION_H