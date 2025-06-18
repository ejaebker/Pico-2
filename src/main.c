#include <stdio.h>
#include "pico/stdlib.h"
int main() {
    // Configures our microcontroller to 
    // communicate over UART through the TX/RX pins
    stdio_init_all();

    // Initialize pins 22, 23, 24, 25 
    // (each 1 bit corresponds to a pin, hence 0xff << 22)
    gpio_init_mask(0xf << 22);
    // Set them all to outputs 
    gpio_set_dir_out_masked64(0xf << 22);

    for(;;) {
        // Turn on the LEDs successively
        for (int i = 0; i < 4; i++) {
            gpio_put(22 + i, true);
            sleep_ms(500);
        }

        // Turn off the LEDs successively
        for (int i = 0; i < 4; i++) {
            gpio_put(22 + i, false);    
            sleep_ms(500);
        }

        // Print "Hello, world!" to the serial monitor
        printf("Hello, world!\n");
    }

}