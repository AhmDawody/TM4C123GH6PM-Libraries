#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "adc.h"


void ADCInit(void){
    SYSCTL_RCGCADC_R |= (1<<0);                 //enable clock for adc0
    while((SYSCTL_RCGCADC_R&0x1)==0);           //wait
    SYSCTL_RCGCGPIO_R |= (1<<4);                //enable port e clock
    while(((SYSCTL_RCGCGPIO_R&(1<<4))==0));       //wait
    GPIO_PORTE_DIR_R &= ~0x04;                  //PE2 Input
    GPIO_PORTE_AFSEL_R |= (1<<2);               //PE2 is alternate function
    GPIO_PORTE_DEN_R &= ~(1<<2);                //PE2 den is disabled
    GPIO_PORTE_AMSEL_R |= (1<<2);               //Enable analog function
    ADC0_SSPRI_R|=(0<<12)|(0x1<<8)|(0x2<<4)|(0x3<<0);   //SS3 Highest, SS0 Lowest
    ADC0_ACTSS_R &= ~(1<<3);                    //SS3 is disabled during initialization
    ADC0_EMUX_R &= ~(0xF<<12);                  //SS3 is processor triggered
    ADC0_SSMUX3_R = (0x1);                     //channel Ain1 (PE2)
    ADC0_SSCTL3_R = 0x6;                       //no TS0 D0, yes IE0 END0
    ADC0_ACTSS_R |= (1<<3);                     //Enable SS3
}

//Sample Capture
uint32_t ADC_IN(void){
    uint32_t r;
    ADC0_PSSI_R |= (1<<3);                  //Initialize SS3
    while((ADC0_RIS_R&(1<<3))==0);          //wait for 1
    r = ADC0_SSFIFO3_R&0xFFF;                //result in r
    ADC0_ISC_R |= (1<<3);                    //clear ss3 by writing 1 to ISC
    return r;
}
