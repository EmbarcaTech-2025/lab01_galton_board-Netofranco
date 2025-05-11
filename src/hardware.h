#ifndef HARDWARE_H
#define HARDWARE_H

#include <pico/stdlib.h>
#include <hardware/i2c.h>
#include "config.h"
#include "include/ssd1306.h"            //Biblioteca comunicação com display 

//Definições utilizadas no programa para comunicação com o Display
#define PIN_SDA 14
#define PIN_SCL 15
#define I2C_PORT i2c1

//Definições utilizadas para o controle de variaveis atraves do Botão
#define BUTTON_ESQ 5
#define BUTTON_DIR 6
#define BUTTON_PRINT 22

void hardware_init();
void check_prob_buttons(int *prob);
void check_percentage_button(bool *show_bin_percentage, bool *need_full_redraw, int bins[], int total_balls);

#endif // HARDWARE_H