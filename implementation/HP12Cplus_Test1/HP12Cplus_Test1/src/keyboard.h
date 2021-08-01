/*
 * keyboard.h
 *
 * Created: 2021/7/26 1:10:53
 *  Author: andy1
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_

typedef uint8_t keycode_t;
#define KEY_NULL    0
#define KEYBUFFSIZE 16

typedef struct {
	volatile uint8_t   readPtr;
	volatile uint8_t   writePtr;
	volatile keycode_t buf[KEYBUFFSIZE];
	} key_buffer_t;

void      KB_init(void);
keycode_t KB_dequeue(void);
keycode_t KB_peek(void);
bool      KB_empty(void);
void      KB_clear(void);
void      KB_enqueue(keycode_t);
void      KB_wait(void);




#endif /* KEYBOARD_H_ */