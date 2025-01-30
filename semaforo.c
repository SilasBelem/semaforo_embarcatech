#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

volatile int state = 0; // 0 - Vermelho, 1 - Amarelo, 2 - Verde

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(LED_RED, 0);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_GREEN, 0);

    // Acende o LED correspondente ao estado atual
    switch (state) {
        case 0:
            gpio_put(LED_RED, 1);
            state = 1;
            break;
        case 1:
            gpio_put(LED_YELLOW, 1);
            state = 2;
            break;
        case 2:
            gpio_put(LED_GREEN, 1);
            state = 0;
            break;
    }
    return true; // Mantém o temporizador rodando
}

int main() {
    stdio_init_all();

    // Configuração dos pinos como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Inicia com o LED vermelho ligado
    gpio_put(LED_RED, 1);

    // Configuração do temporizador repetitivo
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (1) {
        sleep_ms(1000); // Aguarda 1 segundo antes de imprimir novamente
    }
}
