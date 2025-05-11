//Adição de Bibliotecas necessárias ao código
#include "hardware.h"
#include "simulation.h"
#include "display.h"
#include "config.h"
#include "time.h"
#include <stdio.h>
#include <pico/stdlib.h>

int main() {  
    hardware_init();                                //Inicialização do Hardware
    srand(time(NULL));                              //Inicia Gerador De Numeros Aleatórios

    uint8_t display_buffer[ssd1306_buffer_length];  // Buffer do display
    Ball balls[MAX_BALLS] = {0};
    Peg pegs[NUM_PEG_ROWS * (NUM_PEG_ROWS + 1) / 2];
    int bins[NUM_BINS] = {0};
    int total_balls = 0;
    int prob = 50;
    bool show_bin_percentage = false;
    bool need_full_redraw = true;

    init_pegs(pegs);                                    //Inicia Obstaculos na tela

    uint32_t last_ball_time = 0;
    uint32_t last_update_time = 0;
    
    // Loop principal
    while (true) {
        uint32_t current_time = to_ms_since_boot(get_absolute_time());
        
        // Verifica botões
        check_prob_buttons(&prob);
        check_percentage_button(&show_bin_percentage, &need_full_redraw, bins, total_balls);
        
        // Adiciona nova bola periodicamente
        if (current_time - last_ball_time > 800) {
            add_ball(balls, &total_balls);
            last_ball_time = current_time;
        }
        
        // Atualiza física e renderização
        if (current_time - last_update_time > 10) {
            update_balls(balls, pegs, bins, prob, &need_full_redraw);
            draw_frame(display_buffer, balls, pegs, bins, total_balls, show_bin_percentage, &need_full_redraw);
            last_update_time = current_time;
        }
    }
    
    return 0;
}