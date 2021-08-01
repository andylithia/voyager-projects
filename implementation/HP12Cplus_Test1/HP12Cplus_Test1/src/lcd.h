/*
 * lcd.h
 *
 * Created: 2021/7/19 22:22:51
 *  Author: andy1
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

#define ANN_STAR  0
#define ANN_MINUS 1
#define ANN_USER  4
#define ANN_F     6
#define ANN_G     9
#define ANN_BEGIN 11
#define ANN_GR    14
#define ANN_RAD   16
#define ANN_DMY   19
#define ANN_C     21
#define ANN_PRGM  24

void LCD_drawDigit(uint8_t pos, uint8_t segments);
void LCD_localClear(void);
void LCD_localLoad(uint32_t DRL0, uint32_t DRL1, uint32_t DRL2, uint32_t DRL3);
void LCD_drawComma(uint8_t pos);
void LCD_drawDRL0(uint8_t pos);
void LCD_localPush(void);

void LCD_emitString(const char* str);


#define SEG(G,S) (((G)<<0x5)|(((S))&0x1F))



#endif /* LCD_H_ */