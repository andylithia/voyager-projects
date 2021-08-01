/**
 * \file
 *
 * \brief This file contains the default exception handlers.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 * \par Purpose
 *
 * This file provides basic support for Cortex-M processor based
 * microcontrollers.
 *
 * \note
 * The exception handler has weak aliases.
 * As they are weak aliases, any function with the same name will override
 * this definition.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "exceptions.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */



/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void){ while (1) {} }




/* Cortex-M3 core handlers */
void DH_Reset				(void){ while (1) {} }
void DH_NMI					(void){ while (1) {} }
void DH_HardFault			(void){ while (1) {} }
void DH_MemManage			(void){ while (1) {} }
void DH_BusFault			(void){ while (1) {} }
void DH_UsageFault_Handler	(void){ while (1) {} }
void DH_SVC					(void){ while (1) {} }
void DH_DebugMon			(void){ while (1) {} }
void DH_PendSV				(void){ while (1) {} }
void DH_SysTick				(void){ while (1) {} }

/* Peripherals handlers */
void DH_ABDACB 				(void){ while (1) {} }
void DH_ACIFC 				(void){ while (1) {} }
void DH_ADCIFE 				(void){ while (1) {} }
void DH_AESA 				(void){ while (1) {} }
void DH_AST_ALARM 			(void){ while (1) {} }
void DH_AST_CLKREADY 		(void){ while (1) {} }
void DH_AST_OVF 			(void){ while (1) {} }
void DH_AST_PER 			(void){ while (1) {} }
void DH_AST_READY 			(void){ while (1) {} }
void DH_BPM 				(void){ while (1) {} }
void DH_BSCIF 				(void){ while (1) {} }
void DH_CATB 				(void){ while (1) {} }
void DH_CRCCU 				(void){ while (1) {} }
void DH_DACC 				(void){ while (1) {} }
void DH_EIC_1 				(void){ while (1) {} }
void DH_EIC_2 				(void){ while (1) {} }
void DH_EIC_3 				(void){ while (1) {} }
void DH_EIC_4 				(void){ while (1) {} }
void DH_EIC_5 				(void){ while (1) {} }
void DH_EIC_6 				(void){ while (1) {} }
void DH_EIC_7 				(void){ while (1) {} }
void DH_EIC_8 				(void){ while (1) {} }
void DH_FREQM 				(void){ while (1) {} }
void DH_GPIO_0 				(void){ while (1) {} }
void DH_GPIO_1 				(void){ while (1) {} }
void DH_GPIO_10 			(void){ while (1) {} }
void DH_GPIO_11 			(void){ while (1) {} }
void DH_GPIO_2 				(void){ while (1) {} }
void DH_GPIO_3 				(void){ while (1) {} }
void DH_GPIO_4 				(void){ while (1) {} }
void DH_GPIO_5 				(void){ while (1) {} }
void DH_GPIO_6 				(void){ while (1) {} }
void DH_GPIO_7 				(void){ while (1) {} }
void DH_GPIO_8 				(void){ while (1) {} }
void DH_GPIO_9 				(void){ while (1) {} }
void DH_HFLASHC 			(void){ while (1) {} }
void DH_IISC 				(void){ while (1) {} }
void DH_LCDCA 				(void){ while (1) {} }
void DH_PARC 				(void){ while (1) {} }
void DH_PDCA_0 				(void){ while (1) {} }
void DH_PDCA_1 				(void){ while (1) {} }
void DH_PDCA_10 			(void){ while (1) {} }
void DH_PDCA_11 			(void){ while (1) {} }
void DH_PDCA_12 			(void){ while (1) {} }
void DH_PDCA_13 			(void){ while (1) {} }
void DH_PDCA_14 			(void){ while (1) {} }
void DH_PDCA_15 			(void){ while (1) {} }
void DH_PDCA_2 				(void){ while (1) {} }
void DH_PDCA_3 				(void){ while (1) {} }
void DH_PDCA_4 				(void){ while (1) {} }
void DH_PDCA_5 				(void){ while (1) {} }
void DH_PDCA_6 				(void){ while (1) {} }
void DH_PDCA_7 				(void){ while (1) {} }
void DH_PDCA_8 				(void){ while (1) {} }
void DH_PDCA_9 				(void){ while (1) {} }
void DH_PEVC_OV 			(void){ while (1) {} }
void DH_PEVC_TR 			(void){ while (1) {} }
void DH_PM 					(void){ while (1) {} }
void DH_SCIF 				(void){ while (1) {} }
void DH_SPI 				(void){ while (1) {} }
void DH_TC00 				(void){ while (1) {} }
void DH_TC01 				(void){ while (1) {} }
void DH_TC02 				(void){ while (1) {} }
void DH_TC10 				(void){ while (1) {} }
void DH_TC11 				(void){ while (1) {} }
void DH_TC12 				(void){ while (1) {} }
void DH_TRNG 				(void){ while (1) {} }
void DH_TWIM0 				(void){ while (1) {} }
void DH_TWIM1 				(void){ while (1) {} }
void DH_TWIM2 				(void){ while (1) {} }
void DH_TWIM3 				(void){ while (1) {} }
void DH_TWIS0 				(void){ while (1) {} }
void DH_TWIS1 				(void){ while (1) {} }
void DH_USART0 				(void){ while (1) {} }
void DH_USART1 				(void){ while (1) {} }
void DH_USART2 				(void){ while (1) {} }
void DH_USART3 				(void){ while (1) {} }
void DH_USBC 				(void){ while (1) {} }
void DH_WDT 				(void){ while (1) {} }

#ifdef __GNUC__
/* Cortex-M core handlers */
void Reset_Handler      ( void ) __attribute__ ((weak, alias("DH_Reset")));
void NMI_Handler        ( void ) __attribute__ ((weak, alias("DH_NMI")));
void HardFault_Handler  ( void ) __attribute__ ((weak, alias("DH_HardFault")));
void MemManage_Handler  ( void ) __attribute__ ((weak, alias("DH_MemManage")));
void BusFault_Handler   ( void ) __attribute__ ((weak, alias("DH_BusFault")));
void UsageFault_Handler ( void ) __attribute__ ((weak, alias("DH_UsageFault_Handler")));
void SVC_Handler        ( void ) __attribute__ ((weak, alias("DH_SVC")));
void DebugMon_Handler   ( void ) __attribute__ ((weak, alias("DH_DebugMon")));
void PendSV_Handler     ( void ) __attribute__ ((weak, alias("DH_PendSV")));
void SysTick_Handler    ( void ) __attribute__ ((weak, alias("DH_SysTick")));

/* Peripherals handlers */
void ABDACB_Handler(void)       __attribute__ ((weak, alias("DH_ABDACB")));
void ACIFC_Handler(void)        __attribute__ ((weak, alias("DH_ACIFC")));
void ADCIFE_Handler(void)       __attribute__ ((weak, alias("DH_ADCIFE")));
void AESA_Handler(void)         __attribute__ ((weak, alias("DH_AESA")));
void AST_ALARM_Handler(void)    __attribute__ ((weak, alias("DH_AST_ALARM")));
void AST_CLKREADY_Handler(void) __attribute__ ((weak, alias("DH_AST_CLKREADY")));
void AST_OVF_Handler(void)      __attribute__ ((weak, alias("DH_AST_OVF")));
void AST_PER_Handler(void)      __attribute__ ((weak, alias("DH_AST_PER")));
void AST_READY_Handler(void)    __attribute__ ((weak, alias("DH_AST_READY")));
void BPM_Handler(void)          __attribute__ ((weak, alias("DH_BPM")));
void BSCIF_Handler(void)        __attribute__ ((weak, alias("DH_BSCIF")));
void CATB_Handler(void)         __attribute__ ((weak, alias("DH_CATB")));
void CRCCU_Handler(void)        __attribute__ ((weak, alias("DH_CRCCU")));
void DACC_Handler(void)         __attribute__ ((weak, alias("DH_DACC")));
void EIC_1_Handler(void)        __attribute__ ((weak, alias("DH_EIC_1")));
void EIC_2_Handler(void)        __attribute__ ((weak, alias("DH_EIC_2")));
void EIC_3_Handler(void)        __attribute__ ((weak, alias("DH_EIC_3")));
void EIC_4_Handler(void)        __attribute__ ((weak, alias("DH_EIC_4")));
void EIC_5_Handler(void)        __attribute__ ((weak, alias("DH_EIC_5")));
void EIC_6_Handler(void)        __attribute__ ((weak, alias("DH_EIC_6")));
void EIC_7_Handler(void)        __attribute__ ((weak, alias("DH_EIC_7")));
void EIC_8_Handler(void)        __attribute__ ((weak, alias("DH_EIC_8")));
void FREQM_Handler(void)        __attribute__ ((weak, alias("DH_FREQM")));
void GPIO_0_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_0")));
void GPIO_1_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_1")));
void GPIO_10_Handler(void)      __attribute__ ((weak, alias("DH_GPIO_10")));
void GPIO_11_Handler(void)      __attribute__ ((weak, alias("DH_GPIO_11")));
void GPIO_2_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_2")));
void GPIO_3_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_3")));
void GPIO_4_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_4")));
void GPIO_5_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_5")));
void GPIO_6_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_6")));
void GPIO_7_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_7")));
void GPIO_8_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_8")));
void GPIO_9_Handler(void)       __attribute__ ((weak, alias("DH_GPIO_9")));
void HFLASHC_Handler(void)      __attribute__ ((weak, alias("DH_HFLASHC")));
void IISC_Handler(void)         __attribute__ ((weak, alias("DH_IISC")));
void LCDCA_Handler(void)        __attribute__ ((weak, alias("DH_LCDCA")));
void PARC_Handler(void)         __attribute__ ((weak, alias("DH_PARC")));
void PDCA_0_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_0")));
void PDCA_1_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_1")));
void PDCA_10_Handler(void)      __attribute__ ((weak, alias("DH_PDCA_10")));
void PDCA_11_Handler(void)      __attribute__ ((weak, alias("DH_PDCA_11")));
void PDCA_12_Handler(void)      __attribute__ ((weak, alias("DH_PDCA_12")));
void PDCA_13_Handler(void)      __attribute__ ((weak, alias("DH_PDCA_13")));
void PDCA_14_Handler(void)      __attribute__ ((weak, alias("DH_PDCA_14")));
void PDCA_15_Handler(void)      __attribute__ ((weak, alias("DH_PDCA_15")));
void PDCA_2_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_2")));
void PDCA_3_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_3")));
void PDCA_4_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_4")));
void PDCA_5_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_5")));
void PDCA_6_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_6")));
void PDCA_7_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_7")));
void PDCA_8_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_8")));
void PDCA_9_Handler(void)       __attribute__ ((weak, alias("DH_PDCA_9")));
void PEVC_OV_Handler(void)      __attribute__ ((weak, alias("DH_PEVC_OV")));
void PEVC_TR_Handler(void)      __attribute__ ((weak, alias("DH_PEVC_TR")));
void PM_Handler(void)           __attribute__ ((weak, alias("DH_PM")));
void SCIF_Handler(void)         __attribute__ ((weak, alias("DH_SCIF")));
void SPI_Handler(void)          __attribute__ ((weak, alias("DH_SPI")));
void TC00_Handler(void)         __attribute__ ((weak, alias("DH_TC00")));
void TC01_Handler(void)         __attribute__ ((weak, alias("DH_TC01")));
void TC02_Handler(void)         __attribute__ ((weak, alias("DH_TC02")));
void TC10_Handler(void)         __attribute__ ((weak, alias("DH_TC10")));
void TC11_Handler(void)         __attribute__ ((weak, alias("DH_TC11")));
void TC12_Handler(void)         __attribute__ ((weak, alias("DH_TC12")));
void TRNG_Handler(void)         __attribute__ ((weak, alias("DH_TRNG")));
void TWIM0_Handler(void)        __attribute__ ((weak, alias("DH_TWIM0")));
void TWIM1_Handler(void)        __attribute__ ((weak, alias("DH_TWIM1")));
void TWIM2_Handler(void)        __attribute__ ((weak, alias("DH_TWIM2")));
void TWIM3_Handler(void)        __attribute__ ((weak, alias("DH_TWIM3")));
void TWIS0_Handler(void)        __attribute__ ((weak, alias("DH_TWIS0")));
void TWIS1_Handler(void)        __attribute__ ((weak, alias("DH_TWIS1")));
void USART0_Handler(void)       __attribute__ ((weak, alias("DH_USART0")));
void USART1_Handler(void)       __attribute__ ((weak, alias("DH_USART1")));
void USART2_Handler(void)       __attribute__ ((weak, alias("DH_USART2")));
void USART3_Handler(void)       __attribute__ ((weak, alias("DH_USART3")));
void USBC_Handler(void)         __attribute__ ((weak, alias("DH_USBC")));
void WDT_Handler(void)          __attribute__ ((weak, alias("DH_WDT")));
#endif /* __GNUC__ */

#ifdef __ICCARM__

/* Cortex-M3 core handlers */
#pragma weak Reset_Handler      = DH_Reset				
#pragma weak NMI_Handler        = DH_NMI					
#pragma weak HardFault_Handler  = DH_HardFault			
#pragma weak MemManage_Handler  = DH_MemManage			
#pragma weak BusFault_Handler   = DH_BusFault			
#pragma weak UsageFault_Handler = DH_UsageFault_Handler	
#pragma weak SVC_Handler        = DH_SVC					
#pragma weak DebugMon_Handler   = DH_DebugMon			
#pragma weak PendSV_Handler     = DH_PendSV				
#pragma weak SysTick_Handler    = DH_SysTick				

/* Peripherals handlers */
#pragma weak ABDACB_Handler       = DH_ABDACB 				
#pragma weak ACIFC_Handler        = DH_ACIFC 				
#pragma weak ADCIFE_Handler       = DH_ADCIFE 				
#pragma weak AESA_Handler         = DH_AESA 				
#pragma weak AST_ALARM_Handler    = DH_AST_ALARM 			
#pragma weak AST_CLKREADY_Handler = DH_AST_CLKREADY 		
#pragma weak AST_OVF_Handler      = DH_AST_OVF 			
#pragma weak AST_PER_Handler      = DH_AST_PER 			
#pragma weak AST_READY_Handler    = DH_AST_READY 			
#pragma weak BPM_Handler          = DH_BPM 				
#pragma weak BSCIF_Handler        = DH_BSCIF 				
#pragma weak CATB_Handler         = DH_CATB 				
#pragma weak CRCCU_Handler        = DH_CRCCU 				
#pragma weak DACC_Handler         = DH_DACC 				
#pragma weak EIC_1_Handler        = DH_EIC_1 				
#pragma weak EIC_2_Handler        = DH_EIC_2 				
#pragma weak EIC_3_Handler        = DH_EIC_3 				
#pragma weak EIC_4_Handler        = DH_EIC_4 				
#pragma weak EIC_5_Handler        = DH_EIC_5 				
#pragma weak EIC_6_Handler        = DH_EIC_6 				
#pragma weak EIC_7_Handler        = DH_EIC_7 				
#pragma weak EIC_8_Handler        = DH_EIC_8 				
#pragma weak FREQM_Handler        = DH_FREQM 				
#pragma weak GPIO_0_Handler       = DH_GPIO_0 				
#pragma weak GPIO_1_Handler       = DH_GPIO_1 				
#pragma weak GPIO_10_Handler      = DH_GPIO_10 			
#pragma weak GPIO_11_Handler      = DH_GPIO_11 			
#pragma weak GPIO_2_Handler       = DH_GPIO_2 				
#pragma weak GPIO_3_Handler       = DH_GPIO_3 				
#pragma weak GPIO_4_Handler       = DH_GPIO_4 				
#pragma weak GPIO_5_Handler       = DH_GPIO_5 				
#pragma weak GPIO_6_Handler       = DH_GPIO_6 				
#pragma weak GPIO_7_Handler       = DH_GPIO_7 				
#pragma weak GPIO_8_Handler       = DH_GPIO_8 				
#pragma weak GPIO_9_Handler       = DH_GPIO_9 				
#pragma weak HFLASHC_Handler      = DH_HFLASHC 			
#pragma weak IISC_Handler         = DH_IISC 				
#pragma weak LCDCA_Handler        = DH_LCDCA 				
#pragma weak PARC_Handler         = DH_PARC 				
#pragma weak PDCA_0_Handler       = DH_PDCA_0 				
#pragma weak PDCA_1_Handler       = DH_PDCA_1 				
#pragma weak PDCA_10_Handler      = DH_PDCA_10 			
#pragma weak PDCA_11_Handler      = DH_PDCA_11 			
#pragma weak PDCA_12_Handler      = DH_PDCA_12 			
#pragma weak PDCA_13_Handler      = DH_PDCA_13 			
#pragma weak PDCA_14_Handler      = DH_PDCA_14 			
#pragma weak PDCA_15_Handler      = DH_PDCA_15 			
#pragma weak PDCA_2_Handler       = DH_PDCA_2 				
#pragma weak PDCA_3_Handler       = DH_PDCA_3 				
#pragma weak PDCA_4_Handler       = DH_PDCA_4 				
#pragma weak PDCA_5_Handler       = DH_PDCA_5 				
#pragma weak PDCA_6_Handler       = DH_PDCA_6 				
#pragma weak PDCA_7_Handler       = DH_PDCA_7 				
#pragma weak PDCA_8_Handler       = DH_PDCA_8 				
#pragma weak PDCA_9_Handler       = DH_PDCA_9 				
#pragma weak PEVC_OV_Handler      = DH_PEVC_OV 			
#pragma weak PEVC_TR_Handler      = DH_PEVC_TR 			
#pragma weak PM_Handler           = DH_PM 					
#pragma weak SCIF_Handler         = DH_SCIF 				
#pragma weak SPI_Handler          = DH_SPI 				
#pragma weak TC00_Handler         = DH_TC00 				
#pragma weak TC01_Handler         = DH_TC01 				
#pragma weak TC02_Handler         = DH_TC02 				
#pragma weak TC10_Handler         = DH_TC10 				
#pragma weak TC11_Handler         = DH_TC11 				
#pragma weak TC12_Handler         = DH_TC12 				
#pragma weak TRNG_Handler         = DH_TRNG 				
#pragma weak TWIM0_Handler        = DH_TWIM0 				
#pragma weak TWIM1_Handler        = DH_TWIM1 				
#pragma weak TWIM2_Handler        = DH_TWIM2 				
#pragma weak TWIM3_Handler        = DH_TWIM3 				
#pragma weak TWIS0_Handler        = DH_TWIS0 				
#pragma weak TWIS1_Handler        = DH_TWIS1 				
#pragma weak USART0_Handler       = DH_USART0 				
#pragma weak USART1_Handler       = DH_USART1 				
#pragma weak USART2_Handler       = DH_USART2 				
#pragma weak USART3_Handler       = DH_USART3 				
#pragma weak USBC_Handler         = DH_USBC 				
#pragma weak WDT_Handler          = DH_WDT 				
#endif /* __ICCARM__ */


/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */
