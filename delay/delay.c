#include <stdint.h>
#include <stdbool.h>

#include "delay.h"
#include "inc/tm4c123gh6pm.h"



void Sys_Init(void){
    NVIC_ST_CTRL_R = 0x00;
    NVIC_ST_CTRL_R = 0x05;
}

void Sys_Wait(uint32_t delay){
    NVIC_ST_RELOAD_R = delay - 1;
    NVIC_ST_CURRENT_R = 0x00;
    while((NVIC_ST_CTRL_R&0x10000)==0);
}

//**********************************clock 16MHz or 80MHz****************************************
// Reload = (80M or 16M) * time

void Sys_Wait1ms(uint32_t delay){
    uint32_t i;
    for(i=0; i<delay; i++){
        Sys_Wait(80000);
    }
}

void Sys_Wait10ms(uint32_t delay){
    uint32_t i;
    for(i=0; i<delay; i++){
        Sys_Wait(800000);
    }
}

void Sys_Wait1Us(uint32_t delay){
    uint32_t i;
        for(i=0; i<delay; i++){
            Sys_Wait(80);
        }
}


