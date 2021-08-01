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
#include <stdint.h>
#include <stdbool.h>

#include "conf_example.h"

#include "lcd.h"
#include "keyboard.h"
#include "BCG.h"
#include "nut.h"




extern const uint8_t LUT_lcdSeg[];
extern nut_reg_t nutr;

/**
 * \brief Callback handler for LCDCA Interrupt.
 */
static void lcdca_callback(void)
{
	/* Do nothing here */
}


typedef struct help_msg {
	const uint8_t  keycode;
	const char* str;
} help_msg_t;

help_msg_t* help_messages_ptr;

static const help_msg_t help_messages_16C[] = {
	{ 0x13,"A,   5L,  LJ"}, { 0x33,"B,   5R, A5R"}, { 0x73,"[,   RL, RLC"}, { 0xC3,"D,   RR, RRC"}, { 0x83,"E, RLN, RLCN"},
	{ 0x82,"F, RRN, RRCN"}, { 0xC2,"7, MA5KL, #B"}, { 0x72,"8, MA5KR,AB5"}, { 0x32,"9, RMD, DBLR"}, { 0x12,"DIV,XOR,DBLD"},
	{ 0x10,"G5B,X.[I],RTN"},{ 0x30,"GTO, X.I, LBL"},{ 0x70,"HEX,5H0W,D52"}, { 0xC0,"DEC,5H0W,152"}, { 0x80,"OCT,5H0W,5QR"},
	{ 0x87,"BIN,5H0W,RCP"}, { 0xC7,"4,   5B,  5F"}, { 0x77,"5,   [B,  [F"}, { 0x37,"6,   BQ,  FQ"}, { 0x17,"MUL,AND,DBLM"},
	{ 0x11,"R/5, [I],P/R"}, { 0x31,"55T,  I, B5T"}, { 0x71,"RDN,[LPG,RUP"}, { 0xC1,"X.Y, [LR, P5E"},{ 0x81,"B5P, [LF,[LX"},
	{ 0x84,"ENT,W1N,L5TX"}, { 0xC4,"1, 1'5N,XLEY"}, { 0x74,"2, 2'5N,XLT0"}, { 0x34,"3, U5GN,XLTY"}, { 0x14,"5UB,NOT,XGT0"},
	                        { 0x38,"F"},            { 0x78,"G"},            { 0xC8,"5TO,W512E, L"}, { 0x88,"RCL,FL0AT, R"},
	                        { 0xC5,"0, MEM, XNEY"}, { 0x75," . ,5TAT,XNE0"},{ 0x35,"[H5,EEX,XEQY"}, { 0x15,"ADD,OR, XEQ0"},
	{ 0x00,""}
};

static const help_msg_t help_messages_15C[] = {
	{ 0x13,"5QR,  A,  5Q"}, { 0x33,"EXP,  B,  LN"}, { 0x73,"E10,  [, LOG"}, { 0xC3,"YEX, D, PCTG"}, { 0x83,"RCP, E, DLTA"},
	{ 0x82,"[H5,MATX,AB5"}, { 0xC2,"7,  FIX, DEG"}, { 0x72,"8,  5CI, RAD"}, { 0x32,"9,  ENG, GRD"}, { 0x12,"DIV,5LV,XLEY"},
	{ 0x10,"55R, LBL,B5T"}, { 0x30,"GTO,HYP,AHYP"}, { 0x70,"5IN,DIM,A5IN"}, { 0xC0,"[05,[I],ACO5"}, { 0x80,"TAN, I ,ATAN"},
	{ 0x87,"EEX,RE5LT,PI"}, { 0xC7,"4,  XCHG, 5F"}, { 0x77,"5,  DSE,  [F"}, { 0x37,"6,  15G,  FQ"}, { 0x17,"MUL,1TG,XEQ0"},
	{ 0x11,"R/5, PSE,P/R"}, { 0x31,"G5B,[L5G,RTN"}, { 0x71,"RDN,[LPG,RUP"}, { 0xC1,"X.Y, [LR, RND"},{ 0x81,"B5P, [LF,[LX"},
	{ 0x84,"ENT,RAN#,L5X"}, { 0xC4,"1,   -R,  -P"}, { 0x74,"2,  -HM5, -H"}, { 0x34,"3, -RAD,-DEG"}, { 0x14,"5UB,RE.1M,T5T"},
	                        { 0x38,"F"},            { 0x78,"G"},            { 0xC8,"5TO,FRAC,INT"}, { 0x88,"RCL,U5ER,MEM"},
	                        { 0xC5,"0,  X- ,FRAC"},{ 0x75," . , 5, YHAT.R"},{ 0x35,"5G+, L.R. ,5G-"},{ 0x15,"ADD, PY.X,CY.X"},
	{ 0x00,""}
};

#define AST_AR0_RST        0x32
#define KBB_DEBOUNCE_CYCLE 100

void LCD_helpMessage(uint8_t scancode) {
	uint8_t k;
	uint8_t i = 0;
	while((k=(help_messages_16C[i]).keycode)) {
		if(k==scancode) {
			LCD_emitString(help_messages_ptr[i].str);
			return;
		}
		i++;
	}
}

//     1  2  3  4  5  6  7  8  9  0
// 1 - 13 33 73 c3 83 82 c2 72 32 12
// 2 - 10 30 70 c0 80 87 c7 77 37 17
// 3 - 11 31 73 c1 81 84 c4 74 34 14
// 4 - 18 38 78 c8 88    c5 75 35 15
//
//
//                           0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16
const uint8_t KBB_kclut[] = {0x00, 0x10, 0x30, 0x00, 0x70, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, \
                                   0xC0, 0x00, 0x70, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10};
const uint8_t KBB_krlut[] = {0,0,3,2,0,7,1,4,8,5};

const uint8_t bcd2ascii[] = {'0'-' ','1'-' ','2'-' ','3'-' ','4'-' ','5'-' ','6'-' ','7'-' ','8'-' ','9'-' ','A'-' ','B'-' ','C'-' ','D'-' ','E'-' ','F'-' '};
uint8_t  KBB_lastKey;
uint8_t  KBB_sameKeyCount;
uint16_t KBB_keyDuration;
uint8_t  KBB_keyFlag;
uint16_t KBB_keyDuration1;
uint8_t showing_help;
static void ast_alarm_callback(void) {
	ast_disable_interrupt(AST, AST_INTERRUPT_ALARM);
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_ALARM);
	
	ast_write_counter_value(AST, 0);
	ast_write_alarm0_value(AST, AST_AR0_RST);
	ast_enable_interrupt(AST, AST_INTERRUPT_ALARM);
	return;
	uint8_t scancode;
	for(uint8_t i=1;i<5;i++){
		GPIO->GPIO_PORT[2].GPIO_ODERC = BIT(3)|BIT(4)|BIT(5)|BIT(6);
		GPIO->GPIO_PORT[2].GPIO_ODERS = BIT((2+i));
		delay_us(1);
		uint8_t t_PA = GPIO->GPIO_PORT[0].GPIO_PVR;
		uint8_t t_PB = GPIO->GPIO_PORT[1].GPIO_PVR;
		uint8_t t_PC = GPIO->GPIO_PORT[2].GPIO_PVR;
		scancode = ((~t_PC&BIT(7))>>3)|((~t_PA&BIT(7))>>4)|((~t_PB&0x30)>>3)|(~t_PB&BIT(0));
		if(scancode) {
			scancode = KBB_kclut[15+scancode]|KBB_krlut[(i<<1)];
			break;
			} else {
			scancode = ((~t_PB&0x04)<<2)|(~t_PB&0x08)|(~t_PC&0x07);
			if(scancode) {
				scancode = KBB_kclut[scancode]|KBB_krlut[(i<<1)+1];
				break;
			}
		}
	}
	if(scancode!=KBB_lastKey) {
		KBB_lastKey = scancode;
		KBB_keyDuration1=0;
		if(scancode!=0) {
			KB_enqueue(scancode);
			KBB_sameKeyCount++;
			// LCD_localClear();
			// LCD_drawDigit(0, LUT_lcdSeg[bcd2ascii[(scancode&0xF0)>>4]]);
			// LCD_drawDigit(1, LUT_lcdSeg[bcd2ascii[(scancode&0x0F)]]|0x80);
			// LCD_drawDigit(2, LUT_lcdSeg[bcd2ascii[(KBB_sameKeyCount&0xF0)>>4]]);
			// LCD_drawDigit(3, LUT_lcdSeg[bcd2ascii[(KBB_sameKeyCount&0x0F)]]|0x80);
			KBB_keyDuration = 1;
		}
	} else if(scancode!=0) {
		KBB_keyDuration1++;
		/*
		if(KBB_keyDuration1>3)
			LCD_drawDigit(1, 0x80);
		if(KBB_keyDuration1>6)
			LCD_drawDigit(2, 0x80);
		if(KBB_keyDuration1>9)
			LCD_drawDigit(3, 0x80);
		if(KBB_keyDuration1>12)
			LCD_drawDigit(4, 0x80);
		if(KBB_keyDuration1>15)
			LCD_drawDigit(5, 0x80);
		if(KBB_keyDuration1>18)
			LCD_drawDigit(6, 0x80);
		if(KBB_keyDuration1>21)
			LCD_drawDigit(7, 0x80);
		if(KBB_keyDuration1>24)
			LCD_drawDigit(8, 0x80);
		if(KBB_keyDuration1>27)
			LCD_drawDigit(9, 0x80);
		if(KBB_keyDuration1>30)
			// showing_help=1;
			LCD_helpMessage(scancode);
		*/
	}
	
	if(KBB_keyDuration!=0)
		KBB_keyDuration++;
	if(KBB_keyDuration>=KBB_DEBOUNCE_CYCLE) {
		scancode = 0;
		KBB_keyDuration=0;
	}
	// LCD_localPush();
	/*
	if(KBB_keyDuration!=0) {
		// A key's been pressed
		KBB_keyDuration++;
		if(KBB_keyDuration<KBB_DEBOUNCE_CYCLE) {
			// No retrigger
		} else {
			// Allow for releasing
			if(scancode==0) KBB_keyDuration=0;
		}
	} else {
		if(scancode!=0) {
			KBB_lastKey = scancode;
			KBB_sameKeyCount++;
			LCD_localClear();
			LCD_drawDigit(0, LUT_lcdSeg[bcd2ascii[(scancode&0xF0)>>4]]);
			LCD_drawDigit(1, LUT_lcdSeg[bcd2ascii[(scancode&0x0F)]]|0x80);
			LCD_drawDigit(2, LUT_lcdSeg[bcd2ascii[(KBB_sameKeyCount&0xF0)>>4]]);
			LCD_drawDigit(3, LUT_lcdSeg[bcd2ascii[(KBB_sameKeyCount&0x0F)]]|0x80);
		}
	}
	*/
	
	

	
	ast_write_counter_value(AST, 0);
	ast_write_alarm0_value(AST, AST_AR0_RST);
	ast_enable_interrupt(AST, AST_INTERRUPT_ALARM);
}

static void config_ast(void) {
	struct ast_config ast_conf;
	osc_enable(OSC_ID_OSC32);
	/*
	if(!osc_is_ready(OSC_ID_OSC32)) {
		
		osc_wait_ready(OSC_ID_OSC32);
	}
	*/
	ast_enable(AST);
	ast_conf.mode     = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel     = 0x04;
	ast_conf.counter  = 0;
	if(!ast_set_config(AST, &ast_conf)) {
		LCD_localClear();
		LCD_drawDigit(0, LUT_lcdSeg['F'-' ']);
		LCD_drawDigit(1, LUT_lcdSeg['A'-' ']);
		LCD_drawDigit(2, LUT_lcdSeg['I'-' ']);
		LCD_drawDigit(3, LUT_lcdSeg['L'-' ']);
		LCD_drawDigit(4, LUT_lcdSeg['-'-' ']);
		LCD_drawDigit(5, LUT_lcdSeg['A'-' ']);
		LCD_drawDigit(6, LUT_lcdSeg['S'-' ']);
		LCD_drawDigit(7, LUT_lcdSeg['T'-' ']);
		LCD_drawDigit(8, LUT_lcdSeg[' '-' ']);
		LCD_drawDigit(9, LUT_lcdSeg[' '-' ']);
		LCD_localPush();
		while(1);
	}
	
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_ALARM);
	ast_enable_wakeup(AST, AST_WAKEUP_ALARM);
	ast_set_callback(AST, AST_INTERRUPT_ALARM, ast_alarm_callback,
		AST_ALARM_IRQn, 1);
	ast_disable_interrupt(AST, AST_INTERRUPT_ALARM);
}

static void config_wakeup(void) {
	bpm_enable_wakeup_source(BPM, (1<<BPM_BKUPWEN_AST));
}
/**
 * \brief Application entry point for LCDCA example.
 *
 * \return Unused (ANSI-C compatibility).
 */

#include "vROM.h"

int main(void)
{
	/* LCDCA configuration */
	struct lcdca_config lcdca_cfg;
	uint32_t str_id = 0;
	/* Initialize the SAM system */
	sysclk_init();
	
	/*
	// Enable HCACHE
	sysclk_enable_peripheral_clock(HCACHE);
	HCACHE->HCACHE_CTRL = HCACHE_CTRL_CEN_YES;
	while (!(HCACHE->HCACHE_SR & HCACHE_SR_CSTS_EN));

	sysclk_set_prescalers(CONFIG_SYSCLK_CPU_DIV,
	CONFIG_SYSCLK_PBA_DIV,
	CONFIG_SYSCLK_PBB_DIV,
	CONFIG_SYSCLK_PBC_DIV,
	CONFIG_SYSCLK_PBD_DIV
	);

	uint32_t ps_value = 0;
	bool is_fwu_enabled = false;

	if (sysclk_get_cpu_hz() <= FLASH_FREQ_PS1_FWS_1_MAX_FREQ) {
		ps_value = BPM_PS_1;
		if (sysclk_get_cpu_hz() > FLASH_FREQ_PS1_FWS_0_MAX_FREQ) {
			bpm_enable_fast_wakeup(BPM);
			is_fwu_enabled = true;
		}
	} else {
		ps_value = BPM_PS_0;
	}
	
	osc_enable(OSC_ID_RCFAST);
	osc_wait_ready(OSC_ID_RCFAST);
	// Set a flash wait state depending on the new cpu frequency.
	flash_set_bus_freq(sysclk_get_cpu_hz(), ps_value, is_fwu_enabled);
	sysclk_set_source(SYSCLK_SRC_RCFAST);
	
	// Automatically switch to low power mode
	bpm_configure_power_scaling(BPM, ps_value, BPM_PSCM_CPU_NOT_HALT);
	while ((bpm_get_status(BPM) & BPM_SR_PSOK) == 0);

	// irqflags_t const flags = cpu_irq_save();
	// ...
	// cpu_irq_restore(flags);
	
	*/
	
	board_init();
	// sleepmgr_init();
	
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
	
	config_ast();
	
	ast_write_counter_value(AST, 0);
	ast_write_alarm0_value(AST, AST_AR0_RST);
	// ast_enable_interrupt(AST, AST_INTERRUPT_ALARM);
	
	LCD_localClear();
	LCD_localPush();
	
	// help_messages_ptr = help_messages_15C;

	/* Set callback for LCDCA interrupt */
	// lcdca_set_callback(lcdca_callback, LCDCA_IRQn, 1);

	/* Enable LCDCA wake-up */
	// lcdca_enable_wakeup();

	// GPIO->GPIO_PORT[2].GPIO_ODERC = BIT(0)|BIT(1)|BIT(2);
	// GPIO->GPIO_PORT[1].GPIO_ODERC = BIT(7)|BIT(5)|BIT(4)|BIT(0)|BIT(1)|BIT(2)|BIT(3);
	// GPIO->GPIO_PORT[0].GPIO_ODERC = BIT(7);
	
	
	
	GPIO->GPIO_PORT[2].GPIO_OVRC  = BIT(3)|BIT(4)|BIT(5)|BIT(6);
	GPIO->GPIO_PORT[2].GPIO_ODERC = BIT(3)|BIT(4)|BIT(5)|BIT(6);
	
	 GPIO->GPIO_PORT[1].GPIO_ODERC = BIT(1);
	GPIO->GPIO_PORT[1].GPIO_PUERS = BIT(1);
	GPIO->GPIO_PORT[1].GPIO_PDERC = BIT(1);
	nut_reset();
	volatile uint32_t t=0;
	// printf("Enter power save mode.\n\r");
	// printf("It'll display power save string sequence and"
	//		"blink wireless icon when every wake up.\n\r");
	
	uint16_t di = 0;
	unsigned int cnt  = 0;
	while (1) {
		/* Display lowpower string repeatly */
		// c42364a_write_alpha_packet(lowpower_str[str_id]);
		// str_id = (str_id + 1) % MAX_NUM_LOWPOWER_STR;

		/* Toggle wireless icon */
		// lcdca_toggle_pixel(ICON_WLESS);
		// delay_ms(20);
		
		
		
		LCD_localClear();
		// nut_execute_cycle();
		cnt++;
		uint16_t opcode = (vROM[(cnt/2)+1])<<8;
		opcode |= (vROM[(cnt/2)]);
		LCD_drawDigit(3, LUT_lcdSeg[bcd2ascii[opcode&0x0F]]|0x80);
		LCD_drawDigit(2, LUT_lcdSeg[bcd2ascii[(opcode>>4)&0x0F]]);
		LCD_drawDigit(1, LUT_lcdSeg[bcd2ascii[(opcode>>8)&0x0F]]);
		LCD_drawDigit(0, LUT_lcdSeg[bcd2ascii[(opcode>>12)&0x0F]]);
		
		LCD_drawDigit(6, LUT_lcdSeg[bcd2ascii[nut_get_ucode(nutr.prev_pc)&0x0F]]|0x80);
		LCD_drawDigit(5, LUT_lcdSeg[bcd2ascii[(nut_get_ucode(nutr.prev_pc)>>4)&0x0F]]);
		LCD_drawDigit(4, LUT_lcdSeg[bcd2ascii[(nut_get_ucode(nutr.prev_pc)>>8)&0x0F]]);
		
		LCD_drawDigit(9, LUT_lcdSeg[bcd2ascii[(cnt>>8)&0x0F]]);
		LCD_drawDigit(8, LUT_lcdSeg[bcd2ascii[(cnt>>12)&0x0F]]);
		LCD_drawDigit(7, LUT_lcdSeg[bcd2ascii[(cnt>>16)&0x0F]]);
		LCD_localPush();
			
			/*
			di  = (GPIO->GPIO_PORT[2].GPIO_PVR & BIT(7))<<2;		// Bit 9
			di |= (GPIO->GPIO_PORT[0].GPIO_PVR & BIT(7))<<1;		// Bit 8
			di |= (GPIO->GPIO_PORT[1].GPIO_PVR & B8(00110000))<<2;	// Bit 7,6
			di |= (GPIO->GPIO_PORT[1].GPIO_PVR & BIT(0))<<5;		// Bit 5
			di |= (GPIO->GPIO_PORT[1].GPIO_PVR & BIT(2))<<2;		// Bit 4
			di |=  GPIO->GPIO_PORT[1].GPIO_PVR & BIT(3);
			di |=  GPIO->GPIO_PORT[2].GPIO_PVR & B8(00000111);
			*/
			
			// di ^= 0x03FF;
	
		/* Enter in sleep mode */
		// sleepmgr_enter_sleep();
	}
}
