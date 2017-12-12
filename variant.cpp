/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "UARTClass.h"
#include "USARTClass.h"

// UART objects
RingBuffer rx_buffer1;
RingBuffer tx_buffer1;

UARTClass Serial(UART, UART_IRQn, ID_UART, &rx_buffer1, &tx_buffer1);

void serialEvent() __attribute__((weak));
void serialEvent() { }

// IT handlers
void UART_Handler(void)
{
  Serial.IrqHandler();
}

 // USART objects
RingBuffer rx_buffer2;
RingBuffer rx_buffer3;
RingBuffer rx_buffer4;
RingBuffer tx_buffer2;
RingBuffer tx_buffer3;
RingBuffer tx_buffer4;

USARTClass Serial1(USART0, USART0_IRQn, ID_USART0, &rx_buffer2, &tx_buffer2);
void serialEvent1() __attribute__((weak));
void serialEvent1() { }
USARTClass Serial2(USART1, USART1_IRQn, ID_USART1, &rx_buffer3, &tx_buffer3);
void serialEvent2() __attribute__((weak));
void serialEvent2() { }
USARTClass Serial3(USART3, USART3_IRQn, ID_USART3, &rx_buffer4, &tx_buffer4);
void serialEvent3() __attribute__((weak));
void serialEvent3() { }

// IT handlers
void USART0_Handler(void) { Serial1.IrqHandler(); }
void USART1_Handler(void) { Serial2.IrqHandler(); }
void USART3_Handler(void) { Serial3.IrqHandler(); }

void serialEventRun(void)
{
    if (Serial.available()) serialEvent();
    if (Serial1.available()) serialEvent1();
    if (Serial2.available()) serialEvent2();
    if (Serial3.available()) serialEvent3();
}

extern "C" {

uint32_t pmc_enable_periph_clk(uint32_t ul_id)
{
    if (ul_id < 32) {
        if ((PMC->PMC_PCSR0 & (1u << ul_id)) != (1u << ul_id)) {
            PMC->PMC_PCER0 = 1 << ul_id;
        }
    } else {
        ul_id -= 32;
        if ((PMC->PMC_PCSR1 & (1u << ul_id)) != (1u << ul_id)) {
            PMC->PMC_PCER1 = 1 << ul_id;
        }
    }

    return 0;
}

void __libc_init_array(void);

void init( void )
{
    SystemInit();

    if (SysTick_Config(SystemCoreClock / 1000)) // 1ms interval
        while (true);   // error capture

    __libc_init_array();

    // UART pins
    PIO_SetPeripheral(PIOA, PIO_PERIPH_A, PIO_PA8A_URXD|PIO_PA9A_UTXD);
    PIO_DisableInterrupt(PIOA, PIO_PA8A_URXD|PIO_PA9A_UTXD);
    PIO_PullUp(PIOA, PIO_PA8A_URXD|PIO_PA9A_UTXD, PIO_DEFAULT & PIO_PULLUP);

    // ADC controller
    pmc_enable_periph_clk(ID_ADC);
    adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST);
    adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
    adc_configure_trigger(ADC, ADC_TRIG_SW, 0); // Disable hardware trigger.
    adc_disable_interrupt(ADC, 0xFFFFFFFF); // Disable all ADC interrupts.
    adc_disable_all_channel(ADC);
}

}

