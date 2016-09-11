#ifndef MINI_UART_H
#define MINI_UART_H

#include <stdint.h>
#include "standard.h"

#define MiniUartRegisterViewBase 0x3f215040

struct MiniUartRegisterView
{
    volatile uint32_t IoData;
    volatile uint32_t InterruptEnable;
    volatile uint32_t InterruptIdentify;
    volatile uint32_t LineControl;
    volatile uint32_t ModemControl;
    volatile uint32_t LineStatus;
    volatile uint32_t ModemStatus;
    volatile uint32_t Scratch;
    volatile uint32_t ExtraControl;
    volatile uint32_t ExtraStatus;
    volatile uint32_t Baudrate;
};

extern struct MiniUartRegisterView* MiniUartRegisters;

bool CanReadFromMiniUart();
bool CanWriteToMiniUart();

char ReadMiniUartChar();
void MiniUartWriteChar(char data);
void MiniUartWriteString(const char* string);

#endif