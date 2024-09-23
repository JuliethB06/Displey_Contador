#include "mbed.h"
#include "TM1638x8.h"

TM1638 display(D7, D8, D9);  // DIO, CLK, STB
Ticker ticker;
uint32_t counter = 0;

void updateDisplay() {
    counter++;
    if (counter > 99999999) counter = 0;
    
    // Mostrar el número en los dígitos
    display.setDisplayToDecNumber(counter, true);
    
    // Encender los LEDs en orden inverso según el valor del contador
    for (int i = 0; i < 8; i++) {
        uint32_t threshold = pow(10, i);  // El umbral sigue el orden natural (1, 10, 100, etc.)
        bool ledState = (counter >= threshold);  // Encender el LED cuando el contador alcanza el umbral
        display.setLED(7 - i, ledState);  // Invertir el orden de encendido de los LEDs
    }
}

int main() {
    display.init();
    display.setBrightness(7);  // Máxima intensidad
    
    // Inicialmente, apagar todos los LEDs
    for (int i = 0; i < 8; i++) {
        display.setLED(i, false);
    }
    
    ticker.attach(&updateDisplay, 1s);

    while(1) {
        ThisThread::sleep_for(100ms);
    }
}







