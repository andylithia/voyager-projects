/*
 * lcd.c
 *
 * Created: 2021/7/19 22:22:43
 *  Author: andy1
 */ 
//    0
//   .-.
// 5 |6| 1
//   |-|
// 4 | | 2
//   '-'  * 7
//    3
// Status Bits:
// 7: Refresh
//

#include "BCG.h"
#include "lcd.h"

#include <asf.h>

struct lcdLocal_t {
	uint8_t  status;
	uint32_t DRL0;
	uint32_t DRL1;
	uint32_t DRL2;
	uint32_t DRL3;
} lcdLocal;

const uint8_t lcdSegBase[] = {
	1,4,6,9,11,14,16,19,21,24
};


void LCD_drawDigit(uint8_t pos, uint8_t segments) {
	if(pos&1){
		uint32_t t = 0;
		if(segments&BIT(0)) t |= (0x01)<<(lcdSegBase[pos]-1);
		if(segments&BIT(5)) t |= (0x01)<<(lcdSegBase[pos]);
		if(segments&BIT(1)) t |= (0x01)<<(lcdSegBase[pos]+1);
		lcdLocal.DRL3 |= t;
		t = 0;
		if(segments&BIT(4)) t |= (0x01)<<(lcdSegBase[pos]);
		if(segments&BIT(6)) t |= (0x01)<<(lcdSegBase[pos]+1);
		lcdLocal.DRL2 |= t;
		t = 0;
		if(segments&BIT(2)) t |= (0x01)<<(lcdSegBase[pos]);
		if(segments&BIT(3)) t |= (0x01)<<(lcdSegBase[pos]-1);
		if(segments&BIT(7)) t |= (0x01)<<(lcdSegBase[pos]+1);
		lcdLocal.DRL1 |= t;
	} else {
		uint32_t t = 0;
		if(segments&BIT(5)) t |= (0x01)<<(lcdSegBase[pos]);
		if(segments&BIT(0)) t |= (0x01)<<(lcdSegBase[pos]+1);
		lcdLocal.DRL3 |= t;
		t = 0;
		if(segments&BIT(1)) t |= (0x01)<<(lcdSegBase[pos]+2);
		if(segments&BIT(4)) t |= (0x01)<<(lcdSegBase[pos]);
		if(segments&BIT(6)) t |= (0x01)<<(lcdSegBase[pos]+1);
		lcdLocal.DRL2 |= t;
		t = 0;
		if(segments&BIT(2)) t |= (0x01)<<(lcdSegBase[pos]+1);
		if(segments&BIT(3)) t |= (0x01)<<(lcdSegBase[pos]);
		lcdLocal.DRL1 |= t;
		if(segments&BIT(7)) lcdLocal.DRL0 |= (0x01)<<(lcdSegBase[pos]+2);
	}
	return;
}

void LCD_localClear(){
	lcdLocal.DRL0 = 0;
	lcdLocal.DRL1 = 0;
	lcdLocal.DRL2 = 0;
	lcdLocal.DRL3 = 0;
	return;
}

void LCD_localLoad(uint32_t DRL0, uint32_t DRL1, uint32_t DRL2, uint32_t DRL3){
	lcdLocal.DRL0 = DRL0;
	lcdLocal.DRL1 = DRL1;
	lcdLocal.DRL2 = DRL2;
	lcdLocal.DRL3 = DRL3;
	return;
}

void LCD_localPush(){
	LCDCA->LCDCA_DRL0 = lcdLocal.DRL0;
	LCDCA->LCDCA_DRL1 = lcdLocal.DRL1;
	LCDCA->LCDCA_DRL2 = lcdLocal.DRL2;
	LCDCA->LCDCA_DRL3 = lcdLocal.DRL3;
}

void LCD_drawComma(uint8_t pos){
	lcdLocal.DRL0 |= (0x01)<<(lcdSegBase[pos]+1);
	return;
}

void LCD_drawDRL0(uint8_t pos) {
	lcdLocal.DRL0 |= (0x01)<<pos;
}

const uint8_t LUT_lcdSeg[] = {
	0x00,0x82,0x22,0x7e,0x2d,0x72,0x3c,0x02,
	0x31,0x0e,0x63,0x46,0x0c,0x40,0x80,0x36,
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x09,0x0d,0x60,0x48,0x42,0x83,
	0x7b,0x77,0x7c,0x58,0x5e,0x79,0x71,0x3d,
	0x76,0x04,0x0e,0x75,0x38,0x35,0x54,0x5c,
	0x73,0x67,0x50,0x4d,0x78,0x3e,0x1c,0x3a,
	0x64,0x6e,0x59,0x39,0x1b,0x0f,0x23,0x08
};

void LCD_emitString(const char* str) {
	uint8_t charpos=0;
	uint8_t i=0;
	uint8_t lastsegs;
	lastsegs = LUT_lcdSeg[str[i]-' '];
	i++;
	LCD_localClear();
	do {
		if(charpos>=10) break;
		if((str[i]==',')||(str[i]=='.')) {
			lastsegs |= 0x80;	// The first character shouldn't be a seperator
			if(str[i]==',') LCD_drawComma(charpos);
			} else {
			LCD_drawDigit(charpos, lastsegs);
			charpos++;
			lastsegs = LUT_lcdSeg[str[i]-' '];
		}
		
	} while(str[++i]);
	LCD_drawDigit(charpos, lastsegs);
	return;
}
