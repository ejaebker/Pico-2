#include <stdio.h>
#include "pico/stdlib.h"
#include "PWM.h"
#include "hardware/pwm.h"
#include <math.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

//Constants
#define PWM_GPIO 15          // Output pin
#define CLOCK_DIVIDER 4.0   // PWM clock divider
#define PWM_WRAP 255        //PWM setting

//function declarations
void init_pwm(uint); //Code for initalizing the PWM on a specific pin
void run_pwm_spwm(float, float, float, float); //creates the PWM

// Function to initialize PWM on a specific GPIO
void init_pwm(uint gpio) 
{
    //local declarations
    uint sliceNum;

    //initalization;
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    sliceNum = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(sliceNum, PWM_WRAP);
    pwm_set_clkdiv(sliceNum, CLOCK_DIVIDER);
    pwm_set_enabled(sliceNum, true);
}

// Function to output PWM using sine-triangle comparison
void run_pwm_spwm(float startTime, float timeLength, float sinFreq, float triFreq) 
{
    //local declrations 
    uint sliceNum; //The number of the slice choosen

    const float sampleRate = 50000.0;  // 50 kHz sample rate
    const float dt = 1.0 / sampleRate; //step size
    const float amplitude = 0.95;       // Sine wave amplitude

    uint32_t numSamples; //the number of samples pmw will be analyzed for
    float time; //time count
    uint16_t pwmDuty; //pmw duty cycle

    //PMW creation
    sliceNum = pwm_gpio_to_slice_num(PWM_GPIO);
    numSamples = (uint32_t)(timeLength * sampleRate);
    time = startTime;
    
    for (uint32_t i = 0; i < numSamples; ++i) 
    {
        // Generate sine and triangle wave values
        float sinValue = amplitude * sinf(2 * M_PI * sinFreq * time);
        float triValue = 2.0 * (time * triFreq - floorf(0.5 + time * triFreq)); // triangle wave from -1 to 1

        // Compare sine and triangle to determine PWM duty cycle
        pwmDuty = (sinValue > triValue) ? PWM_WRAP : 0;
        pwm_set_gpio_level(PWM_GPIO, pwmDuty);

        sleep_us((uint)(dt * 1e6));
        printf("Time: %.5f | Sine: %.3f | Tri: %.3f | PWM Duty: %u\n", 
        time, sinValue, triValue, pwmDuty);
        time += dt;
    }

    pwm_set_gpio_level(PWM_GPIO, 0);
}