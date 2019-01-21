#include "adc.h"

void adc_init(void) {
    // ADC control registers configured as
    // 1.5V Ref, Ref On, ADC On, 64 clocks for sample, interrupts enabled
    ADC10CTL0=SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;
    // Internal temp sensor and ADC10CLK/4
    ADC10CTL1=INCH_10 + ADC10DIV_3;
}

tWord adc_read(void) {
    tWord val = 0;
    //__delay_cycles(1000);             // Wait for ADC Ref to settle, not really necessary, or ?
    ADC10CTL0 |= ENC + ADC10SC;         // Enable and start sampling and conversion
    __bis_SR_register(CPUOFF + GIE);    // Interrupt wait for ADC to finish. May cause odd behaviour...
    //while(ADC10CTL1 & ADC10BUSY);     // Busy wait for ADC to finish
    val=ADC10MEM;                         // Put ADC value to variable
    ADC10CTL0&=~ENC;                    // Disable the ADC
    return val;
}

void __attribute__((interrupt(ADC10_VECTOR))) ADC10_ISR (void) {
  __bic_SR_register_on_exit(CPUOFF + GIE);
}
