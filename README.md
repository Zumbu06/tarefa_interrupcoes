Aluno: Rian Barroso Ferreira

Este código controla uma matriz de LEDs WS2812 e um LED rgb usando um microcontrolador Raspberry Pi Pico.
Vou explicar brevemente sobre as funções no codigo:

1: Função clear_leds

Esta função percorre toda a matriz de LEDs (matriz_led) e define os valores de R (vermelho), G (verde) e B (azul) de cada LED como 0, apagando todos os LEDs.

É importante para que antes de atualizar para um novo numero garantir que todos os leds estejam desligados.
Antes de atualizar a matriz de LEDs com um novo número, é necessário garantir que todos os LEDs estejam desligados. Caso contrário, os LEDs que foram acesos anteriormente podem permanecer acesos, causando uma exibição incorreta.

2: Mapeamento da Matriz

Essa matriz define quais LEDs devem ser acesos para exibir cada número (de 0 a 9) em uma matriz 5x5. Cada linha da matriz corresponde a um número, e os valores dentro de cada linha são os índices dos LEDs que devem ser acesos para formar o número correspondente.

3: Função callback

Esta função verifica qual botão foi pressionado e atualiza o número exibido na matriz de LEDs. O debouncing é implementado verificando se o tempo desde a última interrupção é maior que 200 ms.

3.2: Debouncing

O debouncing é necessário para evitar múltiplas detecções de um único pressionamento de botão devido a flutuações mecânicas. No código, o debouncing é implementado verificando o tempo decorrido desde a última interrupção.

4: Função atualizar

Essa função  é responsável por atualizar a matriz de LEDs para exibir o número atual. Pra isso primeiro o clear_leds é chamado como ja foi explicado, definimos a cor que no caso ta vermelho com intensidade 50. Leds_por_numero é importante para obter os índices dos leds que deve ser acesso, por final o print_leds envia os dados de cor para a matriz e atualiza com o número correto.

5: Configuração de interrupções 

Na main, o "gpio_set_irq_enabled_with_callback" habilita interrupções para os botões BOTAO_A e BOTAO_B. As interrupções são configuradas para serem acionadas na borda de descida GPIO_IRQ_EDGE_FALL, ou seja, quando o botão é pressionado. Isso é importante para o programa nao precisar ficar verificando o tempo todo o estado dos pinos e economizar recursos do processador.

6: Loop do led rgb

Foi feito também um loop com 100ms pra cada estado desligado ou ligado para poder ficar piscando constantemente como foi solicitado.

Video demonstração na placa:
https://youtube.com/shorts/WOpCcLdvbYI?si=zkP74Z_wYeQfjLEX
