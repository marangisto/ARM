#pragma once

#include "startup.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void TimeTick_Increment( void );

/********************************************************************************
 * Device interrupt vector. Functions are overwritable (weak aliases).
 ********************************************************************************/
static void __phantom_handler(void) { while(1); }

void NMI_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void HardFault_Handler (void) __attribute__ ((weak, alias("__phantom_handler")));
void MemManage_Handler (void) __attribute__ ((weak, alias("__phantom_handler")));
void BusFault_Handler  (void) __attribute__ ((weak, alias("__phantom_handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("__phantom_handler")));
void DebugMon_Handler  (void) __attribute__ ((weak, alias("__phantom_handler")));
void SVC_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void PendSV_Handler    (void) __attribute__ ((weak, alias("__phantom_handler")));
void SysTick_Handler(void) { TimeTick_Increment(); }
void SUPC_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void RSTC_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void RTC_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void RTT_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void WDT_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void PMC_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void EFC0_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void EFC1_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void UART_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#ifdef _SAM3XA_SMC_INSTANCE_
void SMC_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
#ifdef _SAM3XA_SDRAMC_INSTANCE_
void SDRAMC_Handler     (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
void PIOA_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void PIOB_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#ifdef _SAM3XA_PIOC_INSTANCE_
void PIOC_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
#ifdef _SAM3XA_PIOD_INSTANCE_
void PIOD_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
#ifdef _SAM3XA_PIOE_INSTANCE_
void PIOE_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
#ifdef _SAM3XA_PIOF_INSTANCE_
void PIOF_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
void USART0_Handler     (void) __attribute__ ((weak, alias("__phantom_handler")));
void USART1_Handler     (void) __attribute__ ((weak, alias("__phantom_handler")));
void USART2_Handler     (void) __attribute__ ((weak, alias("__phantom_handler")));
#ifdef _SAM3XA_USART3_INSTANCE_
void USART3_Handler     (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
void HSMCI_Handler      (void) __attribute__ ((weak, alias("__phantom_handler")));
void TWI0_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void TWI1_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void SPI0_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#ifdef _SAM3XA_SPI1_INSTANCE_
void SPI1_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
void SSC_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC0_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC1_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC2_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC3_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC4_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC5_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
#ifdef _SAM3XA_TC2_INSTANCE_
void TC6_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC7_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void TC8_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
void PWM_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void ADC_Handler        (void) __attribute__ ((weak, alias("__phantom_handler")));
void DACC_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void DMAC_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void UOTGHS_Handler     (void) __attribute__ ((weak, alias("__phantom_handler")));
void TRNG_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#ifdef _SAM3XA_EMAC_INSTANCE_
void EMAC_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
#endif
void CAN0_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));
void CAN1_Handler       (void) __attribute__ ((weak, alias("__phantom_handler")));

#define SYS_BOARD_OSCOUNT   (CKGR_MOR_MOSCXTST(0x8))
#define SYS_BOARD_PLLAR     (CKGR_PLLAR_ONE \
							| CKGR_PLLAR_MULA(0xdUL) \
							| CKGR_PLLAR_PLLACOUNT(0x3fUL) \
							| CKGR_PLLAR_DIVA(0x1UL))
#define SYS_BOARD_MCKR      (PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK)

/* Clock Definitions */
#define SYS_UTMIPLL     		(480000000UL)	/* UTMI PLL frequency */

#define SYS_CKGR_MOR_KEY_VALUE	CKGR_MOR_KEY(0x37) /* Key to unlock MOR register */

/* FIXME: should be generated by sock */
uint32_t SystemCoreClock = CHIP_FREQ_MAINCK_RC_4MHZ;

void SystemInit(void)
{
	/* Set FWS according to SYS_BOARD_MCKR configuration */
	EFC0->EEFC_FMR = EEFC_FMR_FWS(4);
	EFC1->EEFC_FMR = EEFC_FMR_FWS(4);

	/* Initialize main oscillator */
	if (!(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL)) {
		PMC->CKGR_MOR = SYS_CKGR_MOR_KEY_VALUE | SYS_BOARD_OSCOUNT | 
			                     CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
		while (!(PMC->PMC_SR & PMC_SR_MOSCXTS)) {
		}
	}

	/* Switch to 3-20MHz Xtal oscillator */
	PMC->CKGR_MOR = SYS_CKGR_MOR_KEY_VALUE | SYS_BOARD_OSCOUNT | 
	                           CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;

	while (!(PMC->PMC_SR & PMC_SR_MOSCSELS)) {
	}
 	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)PMC_MCKR_CSS_Msk) | 
		                     PMC_MCKR_CSS_MAIN_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) {
	}

	/* Initialize PLLA */
	PMC->CKGR_PLLAR = SYS_BOARD_PLLAR;
	while (!(PMC->PMC_SR & PMC_SR_LOCKA)) {
	}

	/* Switch to main clock */
	PMC->PMC_MCKR = (SYS_BOARD_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) {
	}

	/* Switch to PLLA */
	PMC->PMC_MCKR = SYS_BOARD_MCKR;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) {
	}

	SystemCoreClock = CHIP_FREQ_CPU_MAX;
}

void SystemCoreClockUpdate(void)
{
	/* Determine clock frequency according to clock register values */
	switch (PMC->PMC_MCKR & PMC_MCKR_CSS_Msk) {
	case PMC_MCKR_CSS_SLOW_CLK:	/* Slow clock */
		if (SUPC->SUPC_SR & SUPC_SR_OSCSEL) {
			SystemCoreClock = CHIP_FREQ_XTAL_32K;
		} else {
			SystemCoreClock = CHIP_FREQ_SLCK_RC;
		}
		break;
	case PMC_MCKR_CSS_MAIN_CLK:	/* Main clock */
		if (PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) {
			SystemCoreClock = CHIP_FREQ_XTAL_12M;
		} else {
			SystemCoreClock = CHIP_FREQ_MAINCK_RC_4MHZ;

			switch (PMC->CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) {
			case CKGR_MOR_MOSCRCF_4_MHz:
				break;
			case CKGR_MOR_MOSCRCF_8_MHz:
				SystemCoreClock *= 2U;
				break;
			case CKGR_MOR_MOSCRCF_12_MHz:
				SystemCoreClock *= 3U;
				break;
			default:
				break;
			}
		}
		break;
	case PMC_MCKR_CSS_PLLA_CLK:	/* PLLA clock */
	case PMC_MCKR_CSS_UPLL_CLK:	/* UPLL clock */
		if (PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) {
			SystemCoreClock = CHIP_FREQ_XTAL_12M;
		} else {
			SystemCoreClock = CHIP_FREQ_MAINCK_RC_4MHZ;

			switch (PMC->CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) {
			case CKGR_MOR_MOSCRCF_4_MHz:
				break;
			case CKGR_MOR_MOSCRCF_8_MHz:
				SystemCoreClock *= 2U;
				break;
			case CKGR_MOR_MOSCRCF_12_MHz:
				SystemCoreClock *= 3U;
				break;
			default:
				break;
			}
		}
		if ((PMC->PMC_MCKR & PMC_MCKR_CSS_Msk) == PMC_MCKR_CSS_PLLA_CLK) {
			SystemCoreClock *= ((((PMC->CKGR_PLLAR) & CKGR_PLLAR_MULA_Msk) >> 
				                            CKGR_PLLAR_MULA_Pos) + 1U);
			SystemCoreClock /= ((((PMC->CKGR_PLLAR) & CKGR_PLLAR_DIVA_Msk) >> 
				                             CKGR_PLLAR_DIVA_Pos));
		} else {
			SystemCoreClock = SYS_UTMIPLL / 2U;
		}
		break;
	}

	if ((PMC->PMC_MCKR & PMC_MCKR_PRES_Msk) == PMC_MCKR_PRES_CLK_3) {
		SystemCoreClock /= 3U;
	} else {
		SystemCoreClock >>= ((PMC->PMC_MCKR & PMC_MCKR_PRES_Msk) >> 
			                          PMC_MCKR_PRES_Pos);
	}
}


/** Tick Counter united by ms */
static volatile uint32_t _dwTickCount=0 ;

/*----------------------------------------------------------------------------
 *         Exported Functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for Sytem Tick interrupt.
 */
extern void TimeTick_Increment( void )
{
    _dwTickCount++ ;
}

/**
 *  \brief Configures the SAM3 SysTick & reset tickCount.
 *  Systick interrupt handler will generates 1ms interrupt and increase a
 *  tickCount.
 *  \param dwNew_MCK  Current master clock.
 */
extern uint32_t TimeTick_Configure( uint32_t dwNew_MCK )
{
    _dwTickCount = 0 ;

    return SysTick_Config( dwNew_MCK/1000 ) ;
}

/**
 *  \brief Get current Tick Count, in ms.
 */
extern uint32_t GetTickCount( void )
{
    return _dwTickCount ;
}

/**
 *  \brief Sync Wait for several ms
 */
extern void Wait( volatile uint32_t dwMs )
{
    uint32_t dwStart ;
    uint32_t dwCurrent ;

    dwStart = _dwTickCount ;
    do
    {
        dwCurrent = _dwTickCount ;
    } while ( dwCurrent - dwStart < dwMs ) ;
}

/**
 *  \brief Sync Sleep for several ms
 */
extern void Sleep( volatile uint32_t dwMs )
{
    uint32_t dwStart ;
    uint32_t dwCurrent ;

    dwStart = _dwTickCount ;

    do
    {
        dwCurrent = _dwTickCount ;

        if ( dwCurrent - dwStart > dwMs )
        {
            break ;
        }

        __WFI() ;
    } while( 1 ) ;
}


extern void WDT_Disable( Wdt* pWDT )
{
    pWDT->WDT_MR = WDT_MR_WDDIS;
}


/********************************************************************************
 * Controller initialisation. Call this function in main(), which is itself called
 * from Reset_Handler()
 ********************************************************************************/

void init_controller(void)
{
  /*
   * SAM System init: Initializes the PLL / clock.
   * Defined in CMSIS/ATMEL/sam3xa/source/system_sam3xa.c
   */
  SystemInit();
  /*
   * Config systick interrupt timing, core clock is in microseconds --> 1ms
   * Defined in CMSIS/CMSIS/include/core_cm3.h
   */
  if (SysTick_Config(SystemCoreClock / 1000))
      while (1) /* stuck forever */;

  /*
   * No watchdog now
   *
   */
  WDT_Disable(WDT);
}

#ifdef  __cplusplus
}
#endif

