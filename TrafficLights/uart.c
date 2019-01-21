#include "uart.h"

/*
 * TODO Automatic clock sync for baud.
 * Right now synced baud to 1 Mhz.
 */

#define RXFULL  (rxb_in == ((rxb_out-1+UART_BUFFER) % UART_BUFFER))
#define RXEMPTY (rxb_in == rxb_out)

#define TXFULL  (txb_in == ((txb_out-1+UART_BUFFER) % UART_BUFFER))
#define TXEMPTY (txb_in == txb_out)

char rxb[UART_BUFFER];
char txb[UART_BUFFER];

tByte rxb_in = 0;
tByte rxb_out = 0;

tByte txb_in = 0;       // TX byte in (queued) counter
tByte txb_out = 0;      // TX byte out (sent) counter

void uart_init(void)
{

    UCA0CTL1 |= UCSWRST;        // Disable/Halt UART operation.

    p_uart(RXD);                // P1.1 RXD to UART mode.
    p_uart(TXD);                // P1.2 TXD to UART mode.
    p_low(RXD);
    p_low(TXD);
    pdir_in(RXD);
    pdir_out(TXD);

    UCA0CTL1 = UCSSEL_2;        // Clock source select.
    // _0 = UCLK, _1 = ACLK, _2 = SMCLK, _3 = SMCLK.

    // Adjust baud rate by clock frequency, see User Guide p 424
    // Register value N = BRCLK/BAUD
    // 1 MHz/9600=104, 0h68 => UCA0BR0 = 0x68; UCA0BR1 = 0x00; UCA0MCTL = UCBRS_1;
    // 16 MHz/9600=1667, 0h6830a=> UCA0BR0 = 0x83; UCA0BR1 = 0x6; UCA0MCTL = UCBRS_5;
    UCA0BR0 = 0x68;         // 1 MHz 9600 Baud
    UCA0BR1 = 0x00;         // 1 MHz 9600 Baud
    UCA0MCTL = UCBRS_1;     // Modulation USBR1 as in Table 15-4
    UC0IE |= UCA0RXIE;      // Enable USCI_A0 RX interrupt
    UCA0CTL1 &= ~UCSWRST;   // Enable/Start UART operation.

}

// Receives characters to be sent.
void uart_write(char *str)
{
    while (*str)
    {
        uart_putc(*str++);
    }

}

// Save the received characters in the given array.
tByte uart_read(char *str, tByte max)
{
    tByte count = 0;
    while (count < max)
    {
        if (!(*str++ = uart_getc()))
        {
            break;
        }
        else
        {
            count++;
        }
    }
    return count;
}

void uart_sendbyte(tByte tosend)
{

    uart_putc(tosend);

}

tByte uart_readbyte(void)
{

    return uart_getc();

}

// Put character in the TX or overload buffer.
inline void uart_putc(tByte c)
{
    // USCI_A0 transmit interrupt flag. UCA0TXIFG is set when UCA0TXBUF is empty.
    if (UC0IFG & UCA0TXIFG)
    {   // We are not sending at the moment.
        UCA0TXBUF = c;           // Send c to buffer immediately.
    }
    else if (!TXFULL)
    {       // Buffer full.
        txb[txb_in] = c;        // Queue buffer.
        txb_in = (txb_in + 1) % UART_BUFFER;  // Increment counter.
        UC0IE |= UCA0TXIE;      // TXIE to enable sending.
    }
    // TODO Error handling. Character is lost here if our own buffer is full.
}

// Save character from RX buffer to overload buffer.
inline tByte uart_getc()
{
    // USCI_A0 receive interrupt flag. UCA0RXIFG is set when UCA0RXBUF has received a complete character.
    tByte c;
    if (!RXEMPTY)
    {
        c = rxb[rxb_out];
        rxb_out = (rxb_out + 1) % UART_BUFFER;
        return c;
    }
    return 0;
}

// RX interrupt when RXIE & RXIFG, when a character is available in buffer
__attribute__((interrupt(USCIAB0RX_VECTOR))) void USCI0RX_ISR(void)
{
    tByte c;
    c = UCA0RXBUF;          // Read byte
    //UART_putc(c+1);       // Proof of concept
    if (!RXFULL)
    {
        rxb[rxb_in] = c;
        rxb_in = (rxb_in + 1) % UART_BUFFER;
    }
    // TODO Error handling. Character is lost here if our own buffer is full.
    // Wakes us up when we have received something.
    __bic_SR_register_on_exit(LPM4_bits);

}

// TX interrupt when TXIE & TXIFG, in other words, when buffer is free for sending
__attribute__((interrupt(USCIAB0TX_VECTOR))) void USCI0TX_ISR(void)
{
    if (TXEMPTY)
    {
        UC0IE &= ~UCA0TXIE;     // Disable TX interrupts to stop sending.
    }
    else
    {
        UCA0TXBUF = txb[txb_out];               // The next char is sent
        txb_out = (txb_out + 1) % UART_BUFFER;    // Increase txb_out counter
    }
}
