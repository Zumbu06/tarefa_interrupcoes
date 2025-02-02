Aluno: Rian Barroso Ferreira

Este código controla uma matriz de LEDs WS2812 e um LED rgb usando um microcontrolador Raspberry Pi Pico.
Vou explicar brevemente sobre as funções no codigo:

1: Função clear_leds

Esta função percorre toda a matriz de LEDs (matriz_led) e define os valores de R (vermelho), G (verde) e B (azul) de cada LED como 0, apagando todos os LEDs.

É importante para que antes de atualizar para um novo numero garantir que todos os leds estejam desligados.
Antes de atualizar a matriz de LEDs com um novo número, é necessário garantir que todos os LEDs estejam desligados. Caso contrário, os LEDs que foram acesos anteriormente podem permanecer acesos, causando uma exibição incorreta.

2: Mapeamento da Matriz

Essa matriz define quais LEDs devem ser acesos para exibir cada número (de 0 a 9) em uma matriz 5x5. Cada linha da matriz corresponde a um número, e os valores dentro de cada linha são os índices dos LEDs que devem ser acesos para formar o número correspondente.

3:Função callback

Esta função verifica qual botão foi pressionado e atualiza o número exibido na matriz de LEDs. O debouncing é implementado verificando se o tempo desde a última interrupção é maior que 200 ms.

3.2: Debouncing

O debouncing é necessário para evitar múltiplas detecções de um único pressionamento de botão devido a flutuações mecânicas. No código, o debouncing é implementado verificando o tempo decorrido desde a última interrupção

Video demonstração na placa:
https://youtube.com/shorts/WOpCcLdvbYI?si=zkP74Z_wYeQfjLEX
