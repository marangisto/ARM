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

#include "USARTClass.h"

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

uint32_t pmc_disable_periph_clk(uint32_t ul_id)
{
	if (ul_id < 32) {
		if ((PMC->PMC_PCSR0 & (1u << ul_id)) == (1u << ul_id)) {
			PMC->PMC_PCDR0 = 1 << ul_id;
		}
	} else {
		ul_id -= 32;
		if ((PMC->PMC_PCSR1 & (1u << ul_id)) == (1u << ul_id)) {
			PMC->PMC_PCDR1 = 1 << ul_id;
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

    // FIXME: move this to UART!
    PIO_SetPeripheral(PIOA, PIO_PERIPH_A, PIO_PA8A_URXD|PIO_PA9A_UTXD);
    PIO_DisableInterrupt(PIOA, PIO_PA8A_URXD|PIO_PA9A_UTXD);
    PIO_PullUp(PIOA, PIO_PA8A_URXD|PIO_PA9A_UTXD, PIO_DEFAULT & PIO_PULLUP);

    // FIXME: make a proper ADC module!
    pmc_enable_periph_clk(ID_ADC);
    adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST);
    adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
    adc_configure_trigger(ADC, ADC_TRIG_SW, 0); // Disable hardware trigger.
    adc_disable_interrupt(ADC, 0xFFFFFFFF); // Disable all ADC interrupts.
    adc_disable_all_channel(ADC);
}

}

