#include "hardware.h"
#include <stdio.h>
#include "include/ssd1306.h"            //Biblioteca comunicação com display 

void hardware_init() {
    stdio_init_all();
    i2c_init(I2C_PORT, 400000);
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SDA);
    gpio_pull_up(PIN_SCL);
    sleep_ms(250);
    ssd1306_init();

    // Configura botões
    gpio_init(BUTTON_ESQ);
    gpio_set_dir(BUTTON_ESQ, GPIO_IN);
    gpio_pull_up(BUTTON_ESQ);

    gpio_init(BUTTON_DIR);
    gpio_set_dir(BUTTON_DIR, GPIO_IN);
    gpio_pull_up(BUTTON_DIR);

    gpio_init(BUTTON_PRINT);
    gpio_set_dir(BUTTON_PRINT, GPIO_IN);
    gpio_pull_up(BUTTON_PRINT);
}

void check_prob_buttons(int *prob) {
    uint32_t now = to_ms_since_boot(get_absolute_time());
    static uint32_t last_check = 0;
    bool change_percent = false;

    if (now - last_check < 200) return;

    if (!gpio_get(BUTTON_DIR)) {
        *prob += 5;
        change_percent = true;
        if (*prob > 100) *prob = 100;
    }

    if (!gpio_get(BUTTON_ESQ)) {
        *prob -= 5;
        if (*prob < 0) *prob = 0;
        change_percent = true;
    }

    if (change_percent == true){
        printf("Porcentagem Esquerda = %d : Porcentagem Direita = %d \n", 100-*prob, *prob);
    }
    last_check = now;
}

void check_percentage_button(bool *show_bin_percentage, bool *need_full_redraw, int bins[], int total_balls) {
    static uint32_t last_check = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if (now - last_check > 200 && !gpio_get(BUTTON_PRINT)) {
        *show_bin_percentage = !(*show_bin_percentage);
        *need_full_redraw = true;

        printf("\n--- Distribuição de Bolas ---\n");
        for (int i = 0; i < NUM_BINS; i++) {
            printf("Bin %d: %d bolas\n", i, bins[i]);
        }
        printf("Total: %d bolas\n", total_balls);
        last_check = now;
    }
}