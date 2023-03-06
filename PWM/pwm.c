
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "pwm.h"


// Initialze PWM module 1 output 6 of PF2

void PWMInit(void){
    SYSCTL_RCGCPWM_R |= (1<<1);                         //Enable clock for PWM module 1
    SYSCTL_RCGCGPIO_R |= (1<<5);                        //Enable port f clock
    while((SYSCTL_RCGCPWM_R & (1<<1)) ==  0);
    while((SYSCTL_RCGCGPIO_R & (1<<5)) ==  0);

    GPIO_PORTF_AFSEL_R |= (1<<2);                       //Enable alternate function on pin 2
    GPIO_PORTF_PCTL_R |= (5<<8);                        //configure PCTL to m1PWM1
    GPIO_PORTF_DEN_R |= (1<<2);                         //Enable digital function on pin 2

    SYSCTL_RCC_R &= ~(1<<20);                           //Use system clock
    PWM1_3_CTL_R &= ~(1<<0);                            //Disable PWM1 at the begining
    PWM1_3_CTL_R &= ~(1<<1);                            //Count down mode
    PWM1_3_LOAD_R = 16000;                               //set load to 16000 at 16 MHz (1k Hz frequency)
    PWM1_3_CMPA_R = 8000;                                //50% Duty cycle
    PWM1_3_GENA_R |= (0x3<<2) | (0x2<<6);              //Go high on count == load and low on count == cmp
    PWM1_3_CTL_R |= (1<<0);                             //Enable PWM1
    PWM1_ENABLE_R |= (1<<6);                            //Enable output 6 on PWM 1
}
