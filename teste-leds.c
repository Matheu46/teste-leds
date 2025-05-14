#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_A 5    // GPIO conectado ao Botão A

// Configuração dos LEDs RGB como saída
const uint BLUE_LED_PIN = 12;   // LED azul no GPIO 12
const uint RED_LED_PIN  = 13; // LED vermelho no GPIO 13
const uint GREEN_LED_PIN = 11;  // LED verde no GPIO 11


// Cores em RGB: vermelho, verde, azul
const int COLORS[][3] = {
    {1, 0, 0},  // 0: vermelho
    {0, 1, 0},  // 1: verde
    {0, 0, 1},  // 2: azul
    // {1, 1, 0},  // 3: amarelo
    // {0, 1, 1},  // 4: ciano
    // {1, 0, 1},  // 5: magenta
    // {1, 1, 1},  // 6: branco
};
const int NUM_COLORS = sizeof(COLORS) / sizeof(COLORS[0]);

// Configuração do GPIO do Botão A como entrada com pull-up interno
void init_button_A() {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
}

void init_led() {
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);
}

void set_led(int red, int green, int blue) {
    gpio_put(RED_LED_PIN, red);
    gpio_put(GREEN_LED_PIN, green);
    gpio_put(BLUE_LED_PIN, blue);
}


int main()
{
    stdio_init_all();
    init_led();
    init_button_A();


    int current_color = 0;
    // Liga cor inicial
    set_led(
        COLORS[current_color][0],
        COLORS[current_color][1],
        COLORS[current_color][2]
    );

    bool prev_button_state = gpio_get(BUTTON_A);  // HIGH=solto, LOW=pressionado

    set_led(1, 0, 0);

    while (true) {
        bool button_state = gpio_get(BUTTON_A);

        // Detecção de borda de descida: HIGH -> LOW
        if (prev_button_state == 1 && button_state == 0) {
            // Incrementa cor e volta ao início quando chega ao fim
            current_color = (current_color + 1) % NUM_COLORS;
            set_led(
                COLORS[current_color][0],
                COLORS[current_color][1],
                COLORS[current_color][2]
            );

            // Debounce simples: espera um pouco antes de ler de novo
            sleep_ms(200);
        }

        prev_button_state = button_state;
        // Pequena pausa para reduzir uso de CPU
        sleep_ms(10);
        
    }
}
