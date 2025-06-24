#ifndef PWM_H
#define PWM_H

void run_pwm_spwm(float startTime, float timeLength, float sinFreq, float triFreq);  //PWM function declaration
void init_pwm(uint gpio); 

#endif