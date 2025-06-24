#include <stdio.h>
#include "pico/stdlib.h"
#include "PWM.h"


int main() {
    stdio_init_all();

    // Example usage
    init_pwm(15);
    run_pwm_spwm(0.0f, 2.0f, 60.0f, 5000.0f); // start at 0s, run for 2s, sine=60Hz, tri=5kHz

    while (1) {
        tight_loop_contents(); // idle
    }
}