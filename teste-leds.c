#include <stdio.h>
#include "pico/stdlib.h"

// Configuração dos LEDs RGB como saída
const uint BLUE_LED_PIN = 12;   // LED azul no GPIO 12
const uint RED_LED_PIN  = 13; // LED vermelho no GPIO 13
const uint GREEN_LED_PIN = 11;  // LED verde no GPIO 11

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

    set_led(1, 0, 0);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
