#include "stm32l432xx.h"
#include "lib_ee152.h"

int main(void){
    //clock_setup_16MHz();		// 16 MHz, AHB and APH1/2 prescale=1x
    clock_setup_80MHz();		// 80 MHz, AHB and APH1/2 prescale=1x

    // The green LED is at Nano D13, or PB3. We'll use D12 for the red LED.
    pinMode(D13, "OUTPUT");
    pinMode(D12, "OUTPUT");

    // bool value=0;
    // while (1) {
    // //     // The green LED is at PB3, or Nano D13. We put the red one at Nano D12.
    // //     // digitalWrite (D13, !value); //red
    // //     // digitalWrite (D12, value); //green

    // //     // value = !value;
    // //     // delay (500);

    // //     //code for 2, 3 combination
    // // }

    int tick = 0;
    bool red = 0;
    bool green = 0;
    while (1) {
        if (tick % 3 == 0) { //every 3/12 = 1/4 seconds, toggle red
            red = !red;   
            digitalWrite(D12, red);   
        }
        if (tick % 2 == 0) { //every 2/12 = 1/6 seconds, toggle green
            green = !green; 
            digitalWrite(D13, green); 
        }
        delay(83); //wait ~1/12 second
        tick = (tick + 1) % 12; //1000ms/12 ~ 83.3ms, 1/12 of a second
    }
}