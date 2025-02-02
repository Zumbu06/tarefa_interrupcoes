#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812b.pio.h"

// Definições dos pinos
#define LED_COUNT 25  // 5x5 matriz de LEDs
#define LED_PIN 7
#define LED_VERMELHO 13
#define BOTAO_A 5
#define BOTAO_B 6

static volatile uint32_t tempo_antes = 0;
static volatile int8_t numero = 0;

static PIO pio;
static uint sm;

// Estrutura para armazenar dados dos LEDs
typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} led;

volatile led matriz_led[LED_COUNT] = {0};

// Função para converter valores RGB em formato adequado
uint32_t valor_rgb(uint8_t B, uint8_t R, uint8_t G) {
    return (G << 24) | (R << 16) | (B << 8);
}

// Função que atualiza o estado dos LEDs na matriz
void set_led(uint8_t indice, uint8_t r, uint8_t g, uint8_t b) {
    if (indice < LED_COUNT) {
        matriz_led[indice].R = r;
        matriz_led[indice].G = g;
        matriz_led[indice].B = b;
    }
}

// Função que limpa a matriz de LEDs
void clear_leds() {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        matriz_led[i].R = 0;
        matriz_led[i].B = 0;
        matriz_led[i].G = 0;
    }
}

// Função que exibe os LEDs da matriz
void print_leds() {
    uint32_t valor;
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        valor = valor_rgb(matriz_led[i].B, matriz_led[i].R, matriz_led[i].G);
        pio_sm_put_blocking(pio, sm, valor);
    }

    // Enviar um LED extra apagado para garantir atualização correta
    pio_sm_put_blocking(pio, sm, valor_rgb(0, 0, 0));
}

// Mapeamento dos números na matriz 5x5
const uint8_t leds_por_numero[10][13] = {
    {23, 22, 21, 16, 18, 13, 11, 6, 8, 3, 2, 1},  // 0
    {22, 16, 17, 12, 7, 3, 2, 1},  // 1
    {23, 22, 21, 18, 13, 12, 11, 6, 3, 2, 1},  // 2
    {23, 22, 21, 18, 13, 12, 11, 8, 3, 2, 1},  // 3
    {21, 17, 18, 13, 11, 5, 6, 7, 8, 9, 1},  // 4
    {23, 22, 21, 16, 13, 12, 11, 8, 1, 2, 3},  // 5
    {23, 22, 21, 16, 13, 6, 3, 2, 1, 8, 11, 12},  // 6
    {24, 23, 22, 21, 20, 18, 12, 6, 4},  // 7
    {23, 22, 21, 18, 16, 13, 12, 11, 6, 8, 3, 2, 1},  // 8
    {23, 22, 21, 16, 18, 13, 12, 11, 8, 3, 2, 1},  // 9
};


void atualizar() {
    clear_leds();

    // Definição da cor (vermelho)
    uint8_t R = 255, G = 0, B = 0;

    // Número total de LEDs que cada número acende
    uint8_t tamanho[] = {12, 8, 11, 11, 11, 11, 12, 9, 13, 12};

    printf("Atualizando número: %d\n", numero);
    printf("Quantidade de LEDs acesos: %d\n", tamanho[numero]);

    // Acende os LEDs corretos para o número atual
    for (uint8_t i = 0; i < tamanho[numero]; i++) {
        uint8_t indice = leds_por_numero[numero][i];
        printf("LED %d acendendo\n", indice);  // Depuração

        if (indice < LED_COUNT) {
            set_led(indice, R, G, B);
        }
    }

    // Atualiza a exibição
    print_leds();
}

// Função que configura os pinos GPIO e a interrupção
void config() {
    gpio_init(LED_VERMELHO);
    gpio_init(BOTAO_A);
    gpio_init(BOTAO_B);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_pull_up(BOTAO_B);
}

// Função que lida com a interrupção dos botões
void gpio_callback(uint gpio, uint32_t events) {
    uint32_t tempo_agora = to_ms_since_boot(get_absolute_time());
    if (tempo_agora - tempo_antes > 200) {  // Debouncing
        if (gpio == BOTAO_A && (numero != 9)) {
            numero++;
            atualizar();
        } else if (gpio == BOTAO_B && (numero != 0)) {
            numero--;
            atualizar();
        }
        tempo_antes = tempo_agora;
    }
}

int main() {
    // Configuração inicial dos pinos e LEDs
    config();

    // Configuração da matriz de LEDs
    pio = pio0;
    bool ok = set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(pio, &ws2812b_program);
    sm = pio_claim_unused_sm(pio, true);
    ws2812b_program_init(pio, sm, offset, LED_PIN);

    // Configuração das interrupções para os botões
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    // Exibição inicial do número 0
    atualizar();

    // Loop principal
    while (true) {
        // Pisca o LED vermelho continuamente 5 vezes por segundo
        gpio_put(LED_VERMELHO, true);
        sleep_ms(100);
        gpio_put(LED_VERMELHO, false);
        sleep_ms(100);
    }

    return 0;
}