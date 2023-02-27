#ifndef LCD_H_
#define LCD_H_


//=============================System Headers========================

#include <stdint.h>
#include <stdbool.h>


//=============================User Defined Headers===================


#include "driverlib\gpio.h"


//=================================Macros==============================
//LCD connection pins and data port.

#define LCD_DATA_PORT                               GPIO_PORTC_DATA_BITS_R
#define LCD_DATA_PORT_ENABLE                        SYSCTL_RCGC2_GPIOC
#define LCD_D4                                      GPIO_PIN_4
#define LCD_D5                                      GPIO_PIN_5
#define LCD_D6                                      GPIO_PIN_6
#define LCD_D7                                      GPIO_PIN_7

#define LCD_CONTROL_PORT                            GPIO_PORTA_DATA_BITS_R
#define LCD_CONTROL_PORT_ENABLE                     SYSCTL_RCGC2_GPIOA
#define LCD_RS                                      GPIO_PIN_2
#define LCD_EN                                      GPIO_PIN_3

#define LCD_CLEAR                   1
#define LCD_CURSOR_OFF              2
#define LCD_UNDERLINE_ON            3
#define LCD_BLINK_CURSOR_ON         4
#define LCD_FIRST_ROW               5
#define LCD_SECOND_ROW              6
#define LCD_CURSOR_LEFT             7

//==================================Prototypes==================================


void LCD_Init(void);

void LCD_Cmd(uint8_t);

void LCD_Chr(uint8_t, uint8_t, uint8_t);

void LCD_Chr_Cp(uint8_t);

void LCD_Text(uint8_t, uint8_t, uint8_t*);

void LCD_Text_Cp(uint8_t*);

void Set_Address(uint8_t, uint8_t);

#endif /* LCD_H_ */
