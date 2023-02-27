#include "inc/tm4c123gh6pm.h"
#include "uart.h"

    // 16 MHz : BRD = 16,000,000 / (16 * 9600) = 104.1666
    // 16 MHz : UARTFBRD[DIVFRAC] = integer(0.166667 * 64 + 0.5) = 11
    // 80 MHz : BRD = 80,000,000 / (16 * 9600) = 520.8333
    // 80 MHz : UARTFBRD[DIVFRAC] = integer(0.8333 * 64 + 0.5) = 53
    // 80 MHz : BRD = 80,000,000 / (16 * 115200) = 43.40278
    // 80 MHz : UARTFBRD[DIVFRAC] = integer(0.40278 * 64 + 0.5) = 26

void UARTInit(void){

    // Enable UART0 and GPIO port A
    SYSCTL_RCGCUART_R |= (1<<0);
    SYSCTL_RCGCGPIO_R |= (1<<0);

    // Wait until UART0 and GPIO port A are ready
    while((SYSCTL_RCGCUART_R & 0x01) == 0);
    while((SYSCTL_RCGCGPIO_R & 0x01) == 0);

    // Enable alternate function for PA0 and PA1
    GPIO_PORTA_AFSEL_R |= (1<<0) | (1<<1);

    // Configure PA0 and PA1 for UART
    GPIO_PORTA_PCTL_R |= (1<<0) | (1<<4);

    // Enable digital function for PA0 and PA1
    GPIO_PORTA_DEN_R |= (1<<0) | (1<<1);

    // Disable UART0
    UART0_CTL_R  &= ~(1<<0);

    // Set baud rate
    UART0_IBRD_R = 43;
    UART0_FBRD_R = 26;

    // Set data format: 8 data bits, 1 stop bit, no parity
    UART0_LCRH_R = (0x03<<5);

    // Use system clock for UART0
    UART0_CC_R = 0x00;

    // Enable UART0, transmitter, and receiver
    UART0_CTL_R  |= (1<<0) | (1<<8) | (1<<9);

/*********************************************************************/

    // Enable UART1 and GPIO port B clocks
    SYSCTL_RCGCUART_R |= (1 << 1);
    SYSCTL_RCGCGPIO_R |= (1 << 1);

    // Wait until UART1 and GPIO port B are ready
    while((SYSCTL_RCGCUART_R & (1 << 1)) == 0);
    while((SYSCTL_RCGCGPIO_R & (1 << 1)) == 0);

    // Configure PB0 and PB1 pins for UART1
    GPIO_PORTB_DEN_R |= (1 << 0) | (1 << 1);
    GPIO_PORTB_AFSEL_R |= (1 << 0) | (1 << 1);
    GPIO_PORTB_PCTL_R |= (1 << 0) | (1 << 4);

    // Disable UART1
    UART1_CTL_R &= ~(1 << 0);

    // Set baud rate
    UART1_IBRD_R = 43;  // for 80MHz clock
    UART1_FBRD_R = 26;   // for 80MHz clock

    // Set data format: 8 data bits, 1 stop bit, no parity
    UART1_LCRH_R = (0x03 << 5);

    // Use system clock for UART1
    UART1_CC_R = 0x00;

    // Enable UART1, transmitter, and receiver
    UART1_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);
}


void Send_Char(uint8_t c){
    while((UART0_FR_R&(1<<5)) != 0);    //FR5 != 0 = full, wait until it is not full = 0, then send
    UART0_DR_R = c;
}

uint8_t Get_Char(void){
    uint8_t c;
    while((UART0_FR_R&(1<<4)) != 0);    //FR4 != 0 = empty, wait until it is not empty = 0, then receive
        c = UART0_DR_R;
    return c;
}
void Send_Char1(uint8_t c){
    while((UART1_FR_R&(1<<5)) != 0);    //FR5 != 0 = full, wait until it is not full = 0, then send
    UART1_DR_R = c;
}

uint8_t Get_Char1(void){
    uint8_t c;
    while((UART1_FR_R&(1<<4)) != 0);    //FR4 != 0 = empty, wait until it is not empty = 0, then receive
        c = UART1_DR_R;
    return c;
}

void GetString(uint8_t* buffer, uint8_t buffer_size) {
    uint8_t i = 0;
    uint8_t c;

    do {
        c = Get_Char();
        buffer[i++] = c;
        //Send_Char(c);                                  // Echo the character back to the terminal
    } while(c != '\r' && i < buffer_size - 1);           // Keep reading until "enter" is pressed or buffer is full

    buffer[i] = '\0';                                    // Add null terminator
}

void Send_String(uint8_t *s){
    while(*s){
        Send_Char(*(s++));
    }
}

void GetString1(uint8_t* buffer, uint8_t buffer_size) {
    uint8_t i = 0;
    uint8_t c;

    do {
        c = Get_Char1();
        buffer[i++] = c;
        //Send_Char(c);                                  // Echo the character back to the terminal
    } while(c != '\r' && i < buffer_size - 1);           // Keep reading until "enter" is pressed or buffer is full

    buffer[i] = '\0';                                    // Add null terminator
}

void Send_String1(uint8_t *s){
    while(*s){
        Send_Char1(*(s++));
    }
}
