#include "stm32l432xx.h"
#include "lib_ee152.h"

int main(void){
    //clock_setup_16MHz();		// 16 MHz, AHB and APH1/2 prescale=1x
    clock_setup_80MHz();		// 80 MHz, AHB and APH1/2 prescale=1x

    // The green LED is at Nano D13, or PB3. We'll use D12 for the red LED.
    pinMode(D13, "OUTPUT");
    pinMode(D12, "OUTPUT");

    bool value=0;
    while (1) {
        // The green LED is at PB3, or Nano D13. We put the red one at Nano D12.
        digitalWrite (D13, value);
        digitalWrite (D12, value);

        value = !value;
        delay (500);
    }
}