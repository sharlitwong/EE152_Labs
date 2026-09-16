////////////////////////////////////////////////////////////////////
// GPIO stuff
////////////////////////////////////////////////////////////////////

#include "stm32l432xx.h"
#include "lib_ee152.h"

#ifdef USE_HAL
#include "stm32l4xx_hal.h"
#endif

////////////////////////////////////////////////////////////////////
// Two arrays to map an Arduino Nano pin name (e.g., A0, A1, D0, D1, ...) to
// to the actual STM32L432 GPIO port and pin number. While the Nano name is
// easy to see on the Nucleo 432 board, the latter is what we need for CSR
// programming.
////////////////////////////////////////////////////////////////////

// Given an Arduino Nano pin name, return the STM32L432 GPIO port.
// We typically index this array with an item of "enum Pin" (e.g., A0 or A1).
static GPIO_TypeDef * g_GPIO_port[D13+1] = {
 GPIOA,GPIOA,GPIOA,GPIOA,		// A0=PA0,A1=PA1,A2=PA3,A3=PA4
 GPIOA,GPIOA,GPIOA,GPIOA,		// A4=PA5,A5=PA6,A6=PA7,A7=PA2
 GPIOA,GPIOA,GPIOA,GPIOB,		// D0=PA10,D1=PA9,D2=PA12,D3=PB0
 GPIOB,GPIOB,GPIOB,GPIOC,		// D4=PB7,D5=PB6,D6=PB1,D7=PC14
 GPIOC,GPIOA,GPIOA,GPIOB,		// D8=PC15,D9=PA8,D10=PA11,D11=PB5
 GPIOB,GPIOB				// D12=PB4,D13=PB3.
};

// Given an Arduino Nano pin name, return the STM32L432 GPIO pin.
// So, between this and g_GPIO_port[] above, we can translate an Arduino pin
// name into the chip's actual GPIO port and pin number.
static int g_GPIO_pin[D13+1] = {
 0,1,3,4,		// A0=PA0,A1=PA1,A2=PA3,A3=PA4
 5,6,7,2,		// A4=PA5,A5=PA6,A6=PA7,A7=PA2
 10,9,12,0,		// D0=PA10,D1=PA9,D2=PA12,D3=PB0
 7,6,1,14,		// D4=PB7,D5=PB6,D6=PB1,D7=PC14
 15,8,11,5,		// D8=PC15,D9=PA8,D10=PA11,D11=PB5
 4,3			// D12=PB4,D13=PB3.
};

////////////////////////////////////////////////////////////////////
// Finally, the actual Arduino API that's publically visible.
// There are two versions of it: with/without USE_HAL.
////////////////////////////////////////////////////////////////////

#include <string.h>	// for strcmp().
#ifdef USE_HAL
static void MX_GPIO_Init(GPIO_TypeDef *port, uint16_t pin) {
    // YOU GET TO WRITE THIS FUNCTION OR TAKE IT FROM CubeMX
    // This is a function that CubeMX will write for you, if you use CubeMX.
    // You can just take the version that CubeMX writes, or write it yourself.
    // You'll need it because the USE_HAL version of pinMode (which we supply
    // for you just below) uses it.
}

void pinMode(enum Pin Nano_pin, char *mode) {
    GPIO_TypeDef *gpio = g_GPIO_port[Nano_pin];
    unsigned int pin   = g_GPIO_pin [Nano_pin];

    if (strcmp (mode, "OUTPUT")==0) {
        MX_GPIO_Init(gpio, 1<<pin);
    } else if (strcmp (mode, "INPUT")==0) {
    } else if (strcmp (mode, "INPUT_PULLUP")==0) {
    } else error("Illegal mode to pinMode()");
}
void digitalWrite (enum Pin Nano_pin, bool value) {
    // YOU GET TO WRITE THIS FUNCTION.
    // ... hint... use HAL_GPIO_WritePin().
}
#else
// Ignore "mode" for this lab, and just assume it's always "OUTPUT".
void pinMode(enum Pin pin, char *mode) {
    // YOU GET TO WRITE THIS FUNCTION.
    // Enable the pin's port & set the pin to be an output, by writing the
    // correct CSRs.

}
void digitalWrite (enum Pin pin, bool value) {
    // YOU GET TO WRITE THIS FUNCTION.
}
#endif

bool digitalRead (enum Pin pin) {
    // Not written yet.
    error ("digitalRead() isn't written yet, since we don't use it in EE152");
    return (0);	// for now.
}