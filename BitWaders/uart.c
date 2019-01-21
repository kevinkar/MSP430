#include "uart.h"

/*
 * Initialize UART for use
 */
void uart_init(void)
{
    UCA0CTL1 |= UCSWRST; // Disable/Halt UART operation.
    //p_uart(RXD); // P1.1 RXD to UART mode.
    p_uart(TXD); // P1.2 TXD to UART mode.
    //p_low(RXD);
    p_low(TXD);
    //pdir_in(RXD);
    pdir_out(TXD);

    UCA0CTL1 = UCSSEL_2; // Clock source select.
    // _0 = UCLK, _1 = ACLK, _2 = SMCLK, _3 = SMCLK.

    // Adjust baud rate by clock frequency, see User Guide p 424
    // Register value N = BRCLK/BAUD
    // 1 MHz/9600=104, 0h68 => UCA0BR0 = 0x68; UCA0BR1 = 0x00; UCA0MCTL = UCBRS_1;
    // 16 MHz/9600=1667, 0h6830a=> UCA0BR0 = 0x83; UCA0BR1 = 0x6; UCA0MCTL = UCBRS_5;
    UCA0BR0 = 0x68;       // 1 MHz 9600 Baud
    UCA0BR1 = 0x00;       // 1 MHz 9600 Baud
    UCA0MCTL = UCBRS_1;   // Modulation USBR1 as in Table 15-
    //UCA0BR0 = 0x83;       // 16 MHz 9600 Baud
    //UCA0BR1 = 0x06;       // 16 MHz 9600 Baud
    //UCA0MCTL = UCBRS_5;   // Modulation USBR1 as in Table 15-4
    UC0IE |= UCA0RXIE;    // Enable USCI_A0 RX interrupt
    //UC0IE &= ~UCA0RXIE;   // Disable USCI_A0 RX interrupt
    UC0IE &= ~UCA0TXIE;   // Disable USCI_A0 TX interrupt
    UCA0CTL1 &= ~UCSWRST; // Enable/Start UART operation.
}

/*
 * Send a string over UART
 */
void uart_write(char *str)
{
    // Outputs string in one busy go
    volatile tByte byteSent = 0;
    while (*str)
    {
        byteSent = 0;
        do
        {
            if (UC0IFG & UCA0TXIFG)
            {   // We are not sending at the moment.
                UCA0TXBUF = *str++; // Send c to buffer immediately.
                byteSent = 1;
            }
        }
        while (!byteSent);
    }
}

