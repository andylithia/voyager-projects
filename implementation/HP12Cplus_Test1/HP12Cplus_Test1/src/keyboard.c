/*
 * keyboard.c
 *
 * Created: 2021/7/26 1:40:48
 *  Author: andy1
 */ 
#include <stdint.h>
#include <stdbool.h>
#include "keyboard.h"

key_buffer_t keyBuffer;

void KB_init(){
	
}

void KB_wait() {
	while(!KB_empty()) KB_dequeue();
	while(KB_empty());
}

keycode_t KB_dequeue() {
	uint8_t r = keyBuffer.readPtr;
	if(r==keyBuffer.writePtr) return 0;
	keycode_t key = keyBuffer.buf[r++];
	if(r==KEYBUFFSIZE) r=0;
	keyBuffer.readPtr = r;
	return key;
}
keycode_t KB_peek() {
	if(KB_empty()) return 0;
	return keyBuffer.buf[keyBuffer.readPtr];
}
bool KB_empty() {
	uint8_t r = keyBuffer.readPtr;
	uint8_t w = keyBuffer.writePtr;
	return r==w;
}
void KB_clear() {
	keyBuffer.readPtr  = 0;
	keyBuffer.writePtr = 0;
}
void KB_enqueue(keycode_t k) {
	uint8_t r = keyBuffer.readPtr;
	uint8_t w = keyBuffer.writePtr;
	if(w!=r-1 && (w!=KEYBUFFSIZE || r!=0)) {
		keyBuffer.buf[w] = k;
		uint8_t t = w+1;
		if(t==KEYBUFFSIZE)
			t = 0;
		keyBuffer.writePtr = t;
	}
}
