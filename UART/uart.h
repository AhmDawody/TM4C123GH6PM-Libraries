#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>

void UARTInit(void);

void Send_Char(uint8_t);
uint8_t Get_Char(void);

void Send_Char1(uint8_t c);
uint8_t Get_Char1(void);

void GetString(uint8_t*, uint8_t);
void GetString1(uint8_t*, uint8_t);

void Send_String(uint8_t*);
void Send_String1(uint8_t *s);





#endif /* UART_H_ */
