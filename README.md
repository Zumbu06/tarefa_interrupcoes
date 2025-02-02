Aluno: Rian Barroso Ferreira
Este código controla uma matriz de LEDs WS2812 e um LED rgb usando um microcontrolador Raspberry Pi Pico.
Vou explicar brevemente sobre as funções no codigo:
1: Função clear_leds
Esta função percorre toda a matriz de LEDs (matriz_led) e define os valores de R (vermelho), G (verde) e B (azul) de cada LED como 0, apagando todos os LEDs.
É importante para que antes de atualizar para um novo numero garantir que todos os leds estejam desligados.
Antes de atualizar a matriz de LEDs com um novo número, é necessário garantir que todos os LEDs estejam desligados. Caso contrário, os LEDs que foram acesos anteriormente podem permanecer acesos, causando uma exibição incorreta.
