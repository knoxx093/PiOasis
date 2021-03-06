#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"
#include "heap.h"

void InitializeHeap()
{
    HeapBase->Length = 40 - 32;
    HeapBase->IsFree = true;
    HeapBase->Previous = NULL;
    HeapBase->Next = NULL;
}

void PrintHeapHeader(HeapHeader* header)
{
    MiniUartWriteString("Address: ");
    MiniUartWriteHex64((uintptr_t)header);

    MiniUartWriteString("\r\nLength: ");
    MiniUartWriteHex64(header->Length);

    MiniUartWriteString("\r\nIs Free: ");
    MiniUartWriteBool(header->IsFree);

    MiniUartWriteString("\r\nPrevious Address: ");
    MiniUartWriteHex64((uintptr_t)header->Previous);

    MiniUartWriteString("\r\nNext Address: ");
    MiniUartWriteHex64((uintptr_t)header->Next);

    MiniUartWriteString("\r\n\r\n");
}

void main()
{
    GpioSetPinFunction(GpioPin2, GpioFunctionOutput);
    GpioSetPinOutput(GpioPin2);

    InitializeHeap();
    MiniUartWriteString("Mini Uart initialized\r\n\r\n");

    while (true)
    {
        char value = MiniUartReadChar();
        switch (value)
        {
            case '0':
                HeapAllocate(5);
                break;

            case '1':
                HeapAllocate(8);
                break;

            case '2':
                HeapAllocate(16);
                break;

            case '3':
                HeapAllocate(32);
                break;

            case '4':
                HeapAllocate(64);
                break;

            case '5':
                HeapAllocate(128);
                break;
                      
            case 'l':;
                HeapHeader* header = HeapBase;
                while (header != NULL)
                {
                    PrintHeapHeader(header);
                    header = header->Next;
                }
                break;
        }

        //MiniUartWriteString("Received: ");
        //MiniUartWriteChar(value);
        //MiniUartWriteString("\r\n");
    }
}
