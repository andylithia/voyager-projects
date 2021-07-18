/**
 * \file
 *
 * \brief SAM4L LCDCA example.
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>
#include "conf_example.h"


/**
 * \brief Callback handler for LCDCA Interrupt.
 */
static void lcdca_callback(void)
{
	/* Do nothing here */
}

/**
 * \brief Application entry point for LCDCA example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* LCDCA configuration */
	struct lcdca_config lcdca_cfg;
	/* Automated display configuration */
	//! [lcd_example_scroll_config_1]	
	struct lcdca_automated_char_config automated_char_cfg;

	uint32_t str_id = 0;

	struct lcdca_blink_config blink_cfg;
	struct lcdca_circular_shift_config cs_cfg;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	sleepmgr_init();
	
	//! [lcd_example_init]
	// LCDCA Controller initialization
	// - Clock,
	// - Connect to C42364A glass LCD component,
	// - Timing:  64 Hz frame rate & low power waveform, FC0, FC1, FC2
	// - Interrupt: off.
	//! [lcd_example_init_clock]
	lcdca_clk_init();
	//! [lcd_example_init_clock]
	lcdca_cfg.port_mask = PORT_MASK;
	lcdca_cfg.x_bias = false;
	lcdca_cfg.lp_wave = true;
	lcdca_cfg.duty_type = LCD_DUTY;
	lcdca_cfg.lcd_pres = false;
	lcdca_cfg.lcd_clkdiv = 3;
	lcdca_cfg.fc0 = 16;
	lcdca_cfg.fc1 = 2;
	lcdca_cfg.fc2 = 6;
	lcdca_cfg.contrast = LCD_CONTRAST_LEVEL;
	lcdca_set_config(&lcdca_cfg);
	lcdca_enable();
	//! [lcd_example_enable_module]
	//! [lcd_example_enable_timers]
	// lcdca_enable_timer(LCDCA_TIMER_FC0);
	// lcdca_enable_timer(LCDCA_TIMER_FC1);
	// lcdca_enable_timer(LCDCA_TIMER_FC2);
	//! [lcd_example_enable_timers]

	/* Turn on LCD back light */
	//! [lcd_example_backlight_on]
	// ioport_set_pin_level(LCD_BL_GPIO, IOPORT_PIN_LEVEL_HIGH);
	//! [lcd_example_backlight_on]
	//! [lcd_example_init]
	
	/* Display some texts and icon on segment LCD */
	// lcdca_set_pixel(ICON_ARM);
	// c42364a_write_num_packet((const uint8_t *)"0123");
	// c42364a_write_alpha_packet((const uint8_t *)"Welcome");

	LCDCA->LCDCA_DRL0 = 0xFFFFFFFF;
	LCDCA->LCDCA_DRL1 = 0xFFFFFFFF;
	LCDCA->LCDCA_DRL2 = 0xFFFFFFFF;
	LCDCA->LCDCA_DRL3 = 0xFFFFFFFF;
	
	

	/* Set callback for LCDCA interrupt */
	// lcdca_set_callback(lcdca_callback, LCDCA_IRQn, 1);

	/* Enable LCDCA wake-up */
	// lcdca_enable_wakeup();

	// printf("Enter power save mode.\n\r");
	// printf("It'll display power save string sequence and"
	//		"blink wireless icon when every wake up.\n\r");
	while (1) {
		/* Display lowpower string repeatly */
		// c42364a_write_alpha_packet(lowpower_str[str_id]);
		// str_id = (str_id + 1) % MAX_NUM_LOWPOWER_STR;

		/* Toggle wireless icon */
		// lcdca_toggle_pixel(ICON_WLESS);

		/* Enter in sleep mode */
		sleepmgr_enter_sleep();
	}
}
