/**
 * \file
 *
 * \brief This file contains the interface for default exception handlers.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include "sam4l.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/* Function prototype for exception table items (interrupt handler). */
typedef void (*IntFunc) (void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M3 core handlers */
void DH_Reset				(void);
void DH_NMI					(void);
void DH_HardFault			(void);
void DH_MemManage			(void);
void DH_BusFault			(void);
void DH_UsageFault_Handler	(void);
void DH_SVC					(void);
void DH_DebugMon			(void);
void DH_PendSV				(void);
void DH_SysTick				(void);

/* Peripherals handlers */
void DH_ABDACB 				(void);
void DH_ACIFC 				(void);
void DH_ADCIFE 				(void);
void DH_AESA 				(void);
void DH_AST_ALARM 			(void);
void DH_AST_CLKREADY 		(void);
void DH_AST_OVF 			(void);
void DH_AST_PER 			(void);
void DH_AST_READY 			(void);
void DH_BPM 				(void);
void DH_BSCIF 				(void);
void DH_CATB 				(void);
void DH_CRCCU 				(void);
void DH_DACC 				(void);
void DH_EIC_1 				(void);
void DH_EIC_2 				(void);
void DH_EIC_3 				(void);
void DH_EIC_4 				(void);
void DH_EIC_5 				(void);
void DH_EIC_6 				(void);
void DH_EIC_7 				(void);
void DH_EIC_8 				(void);
void DH_FREQM 				(void);
void DH_GPIO_0 				(void);
void DH_GPIO_1 				(void);
void DH_GPIO_10 			(void);
void DH_GPIO_11 			(void);
void DH_GPIO_2 				(void);
void DH_GPIO_3 				(void);
void DH_GPIO_4 				(void);
void DH_GPIO_5 				(void);
void DH_GPIO_6 				(void);
void DH_GPIO_7 				(void);
void DH_GPIO_8 				(void);
void DH_GPIO_9 				(void);
void DH_HFLASHC 			(void);
void DH_IISC 				(void);
void DH_LCDCA 				(void);
void DH_PARC 				(void);
void DH_PDCA_0 				(void);
void DH_PDCA_1 				(void);
void DH_PDCA_10 			(void);
void DH_PDCA_11 			(void);
void DH_PDCA_12 			(void);
void DH_PDCA_13 			(void);
void DH_PDCA_14 			(void);
void DH_PDCA_15 			(void);
void DH_PDCA_2 				(void);
void DH_PDCA_3 				(void);
void DH_PDCA_4 				(void);
void DH_PDCA_5 				(void);
void DH_PDCA_6 				(void);
void DH_PDCA_7 				(void);
void DH_PDCA_8 				(void);
void DH_PDCA_9 				(void);
void DH_PEVC_OV 			(void);
void DH_PEVC_TR 			(void);
void DH_PM 					(void);
void DH_SCIF 				(void);
void DH_SPI 				(void);
void DH_TC00 				(void);
void DH_TC01 				(void);
void DH_TC02 				(void);
void DH_TC10 				(void);
void DH_TC11 				(void);
void DH_TC12 				(void);
void DH_TRNG 				(void);
void DH_TWIM0 				(void);
void DH_TWIM1 				(void);
void DH_TWIM2 				(void);
void DH_TWIM3 				(void);
void DH_TWIS0 				(void);
void DH_TWIS1 				(void);
void DH_USART0 				(void);
void DH_USART1 				(void);
void DH_USART2 				(void);
void DH_USART3 				(void);
void DH_USBC 				(void);
void DH_WDT 				(void);

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */

#endif /* EXCEPTIONS_H_INCLUDED */
