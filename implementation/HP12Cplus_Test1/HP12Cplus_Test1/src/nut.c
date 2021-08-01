/*
 * nut.c
 *
 * Created: 2021/7/24 16:55:43
 *  Author: andy1
 */ 

#include <stdint.h>
#include <stdbool.h>
#include "nut.h"
#include "keyboard.h"
#include "lcd.h"

nut_reg_t nutr;




// static void nut_set_ucode(); Not implemented
// nut_set_bank_group ,not Implemented




// BCD to native host binary and vice versa
uint64_t bcd_reg_to_binary (digit_t *reg, uint8_t digits) {
	uint64_t val = 0;
	reg += digits;
	while (digits--) {
		val *= 10;
		val += *(--reg);
	}
	return val;
}
void binary_to_bcd_reg (uint64_t val, digit_t *reg, uint8_t digits) {
	while (digits--) {
		*(reg++) = val % 10;
		val /= 10;
	}
}

// Page Size 4096 Words

#include "vROM.h"

static bool nut_read_rom (rom_addr_t bank, rom_addr_t addr, rom_word_t* val) {
	// if(vROM[(bank<<12)|addr]){
		*val =   vROM[(((bank<<12)|addr)<<1)+1]<<8;
		*val |=  vROM[((bank<<12)|addr)<<1];
	//	return true;
	//} else
	//return false;
	return true;
}

rom_word_t nut_get_ucode(rom_addr_t addr) {
	// Simplified for Voyager, the original impl. uses bank mapping
	// (akin to MMU), restore this for HP41
	// Use nut_read_rom
	rom_addr_t bank = nutr.active_bank;
	rom_addr_t rtn;
	nut_read_rom(bank, addr, &rtn);
	return rtn;
}


// Write ROM is not implemented

// Not useful
static uint8_t arithmetic_base(){
	return nutr.dec_hexn?10:16;
}

static uint8_t* pt (){
	return nutr.q_sel?&(nutr.q):&(nutr.p);
}

// nut_print_state, Not Implemented
static void op_UNDEF (rom_word_t opcode) {
	// Fail Catch
	while(1);
}
//
// BCD Operations
//
void reg_zero(digit_t* dest, uint8_t first, uint8_t last) {
	uint8_t i;
	for(i=first;i<=last;i++)
	dest[i] = 0;
}
void reg_copy (digit_t* dest, const digit_t*  src, uint8_t first, uint8_t last) {
	uint8_t i;
	for(i=first;i<=last;i++)
	dest[i]=src[1];
}
void reg_exch (digit_t* dest, digit_t* src, uint8_t first, uint8_t last) {
	uint8_t i, t;
	for (i=first;i<=last;i++) {
		t = dest[i];
		dest[i] = src[i];
		src[i] = t;
	}
}
static digit_t do_add (digit_t x, digit_t y, bool* carry, uint8_t base) {
	uint8_t res;
	res = x + y + *carry;
	if(res>=base) {
		res -= base;
		*carry = 1;
	} else
	*carry = 0;
	return res;
}
static digit_t do_sub (digit_t x, digit_t y, bool* carry, uint8_t base) {
	int8_t res;
	res = (x - y) - *carry;
	if(res<0) {
		res += base;
		*carry = 1;
	} else
	*carry = 0;
	return (uint8_t)res;
}
void reg_add (digit_t* dest, const digit_t* src1, const digit_t* src2,
uint8_t first, uint8_t last, bool* carry, uint8_t base) {
	uint8_t i;
	for(i=first;i<=last;i++) {
		uint8_t s2 = src2 ? src2[i] : 0;
		dest[i] = do_add(src1[i], s2, carry, base);
	}
}
void reg_sub (digit_t* dest, const digit_t* src1, const digit_t* src2,
uint8_t first, uint8_t last, bool* carry, uint8_t base) {
	uint8_t i;
	for(i=first;i<=last;i++) {
		uint8_t s1 = src1?src1[i]:0;
		uint8_t s2 = src2?src2[i]:0;
		// dest validity test is omitted
		dest[i] = do_sub(s1, s2, carry, base);
	}
}
void reg_teq (const digit_t* src1, const digit_t* src2,
uint8_t first, uint8_t last, bool* carry) {
	uint8_t i;
	*carry = true;
	for(i=first;i<=last;i++) {
		uint8_t s2 = src2?src2[i]:0;
		(*carry) &= (src1[i]==s2);
	}
}
void reg_tneq (const digit_t* src1, const digit_t* src2,
uint8_t first, uint8_t last, bool* carry) {
	uint8_t i;
	*carry = false;
	for(i=first;i<=last;i++) {
		uint8_t s2 = src2?src2[i]:0;
		(*carry) |= (src1[i]!=s2);
	}
}
void reg_sr (digit_t* reg, uint8_t first, uint8_t last) {
	uint8_t i;
	for(i=first;i<=last;i++)
	reg[i] = (i==last)?0:reg[i+1];
}
void reg_sl (digit_t* reg, uint8_t first, uint8_t last) {
	uint8_t i;
	for(i=last;i>=first;i--)
	reg[i] = (i==first)?0:reg[i-1];
}
// TYPE-2 OPCODES - Arithmetic
static void op_arith(rom_word_t opcode){
	uint8_t op, field;
	uint8_t first, last;
	op    =  opcode>>5;
	field = (opcode>>2)&0x7;
	switch(field) {
		case 0:  /* p  */  first = *pt();     last = *pt ();    break;
		case 1:  /* x  */  first = 0;         last = EXPSIZE-1; break;
		case 2:  /* wp */  first = 0;         last = *pt ();    break;
		case 3:  /* w  */  first = 0;         last = WSIZE-1;   break;
		case 4:  /* pq */  first = nutr.p;    last = nutr.q;
		                   if (first > last)  last = WSIZE-1;   break;
		case 5:  /* xs */  first = EXPSIZE-1; last = EXPSIZE-1; break;
		case 6:  /* m  */  first = EXPSIZE;   last = WSIZE-2;   break;
		case 7:  /* s  */  first = WSIZE-1;   last = WSIZE-1;   break;
	}
	nutr.prev_tef_last = last;
	switch(op) {
		case 0x00:  /* a=0 */
			reg_zero (nutr.a, first, last);
		break;
		case 0x01:  /* b=0 */
			reg_zero (nutr.b, first, last);
		break;
		case 0x02:  /* c=0 */
			reg_zero (nutr.c, first, last);
		break;
		case 0x03:  /* ab ex */
			reg_exch (nutr.a, nutr.b, first, last);
		break;
		case 0x04:  /* b=a */
			reg_copy (nutr.b, nutr.a, first, last);
		break;
		case 0x05:  /* ac ex */
			reg_exch (nutr.a, nutr.c, first, last);
		break;
		case 0x06:  /* c=b */
			reg_copy (nutr.c, nutr.b, first, last);
		break;
		case 0x07:  /* bc ex */
			reg_exch (nutr.b, nutr.c, first, last);
		break;
		case 0x08:  /* a=c */
			reg_copy (nutr.a, nutr.c, first, last);
		break;
		case 0x09:  /* a=a+b */
			reg_add (nutr.a, nutr.a, nutr.b, first, last, \
			         &(nutr.carry), arithmetic_base());
		break;
		case 0x0a:  /* a=a+c */
			reg_add (nutr.a, nutr.a, nutr.c, first, last, \
		& nutr.carry, arithmetic_base ());
		break;

		case 0x0b:    /* a=a+1 */
		nutr.carry = 1;
		reg_add (nutr.a, nutr.a, 0,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x0c:  /* a=a-b */
		reg_sub (nutr.a, nutr.a, nutr.b,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x0d:  /* a=a-1 */
		nutr.carry = 1;
		reg_sub (nutr.a, nutr.a, 0,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x0e:  /* a=a-c */
		reg_sub (nutr.a, nutr.a, nutr.c,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x0f:  /* c=c+c */
		reg_add (nutr.c, nutr.c, nutr.c,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x10:  /* c=a+c */
		reg_add (nutr.c, nutr.a, nutr.c,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x11:  /* c=c+1 */
		nutr.carry = 1;
		reg_add (nutr.c, nutr.c, 0,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x12:  /* c=a-c */
		reg_sub (nutr.c, nutr.a, nutr.c,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x13:  /* c=c-1 */
		nutr.carry = 1;
		reg_sub (nutr.c, nutr.c, 0,
		first, last,
		& nutr.carry, arithmetic_base ());
		break;

		case 0x14:  /* c=-c */
			reg_sub (nutr.c, 0, nutr.c, first, last, \
		             &(nutr.carry), arithmetic_base());
		break;
		case 0x15:  /* c=-c-1 */
			nutr.carry = 1;
			reg_sub (nutr.c, 0, nutr.c, first, last, \
			         &(nutr.carry), arithmetic_base()); break;
		case 0x16:  /* ? b<>0 */
			reg_tneq (nutr.b, 0, first, last, &(nutr.carry)); break;
		case 0x17:  /* ? c<>0 */
			reg_tneq (nutr.c, 0, first, last, &(nutr.carry)); break;
		case 0x18:  /* ? a<c */
			reg_sub (0, nutr.a, nutr.c, first, last, \
			         & nutr.carry, arithmetic_base ()); break;
		case 0x19:  /* ? a<b */
			reg_sub (0, nutr.a, nutr.b, first, last, \
			         & nutr.carry, arithmetic_base ()); break;
		case 0x1a:  /* ? a<>0 */
			reg_tneq (nutr.a, 0, first, last, & nutr.carry); break;
		case 0x1b:  /* ? a<>c */
			reg_tneq (nutr.a, nutr.c, first, last, & nutr.carry); break;
		case 0x1c:  /* a sr */
			reg_sr (nutr.a, first, last); break;
		case 0x1d:  /* b sr */
			reg_sr (nutr.b, first, last); break;
		case 0x1e:  /* c sr */
			reg_sr (nutr.c, first, last); break;
		case 0x1f:  /* a sl */
			reg_sl (nutr.a, first, last); break;
		default:
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
}

//
// Stack Operations
//
static rom_addr_t pop () {
	uint8_t i;
	rom_addr_t ret;
	ret = nutr.stack[0];
	for(i=0;i<STACK_DEPTH-1;i++)
		nutr.stack[i] = nutr.stack[i+1];
	nutr.stack[STACK_DEPTH-1]=0;
	return(ret);
	// r
}
static void push (rom_addr_t a) {
	uint8_t i;
	for(i=STACK_DEPTH-1;i>0;i--)
		nutr.stack[i] = nutr.stack[i-1];
	nutr.stack[0] = a;
}
static void op_return             (rom_word_t opcode) {
	nutr.pc = pop();
}
static void op_return_if_carry    (rom_word_t opcode) {
	if(nutr.prev_carry)
		nutr.pc = pop();
}
static void op_return_if_no_carry (rom_word_t opcode) {
	if(!nutr.prev_carry)
		nutr.pc = pop();
}
static void op_pop                (rom_word_t opcode) {
	(void) pop();
}
static void op_pop_c              (rom_word_t opcode) {
	rom_addr_t a;
	a = pop();
	nutr.c[6] =  a>>12;
	nutr.c[5] = (a>>8) & 0x0F;
	nutr.c[4] = (a>>4) & 0x0F;
	nutr.c[3] =  a     & 0x0F;
}
static void op_push_c             (rom_word_t opcode) {
	push((nutr.c[6]<<12)|(nutr.c[5]<<8)|(nutr.c[4]<<4)|nutr.c[3]);
}

//
// Branch Operations
//
static void op_short_branch  (rom_word_t opcode) {
	int offset;
	offset = (opcode >> 3) & 0x3F;
	if(opcode & 0x200) offset -= 64;
	if(((opcode >> 2) & 1) == nutr.prev_carry)
		nutr.pc = nutr.pc + offset - 1;
}
static void op_long_branch   (rom_word_t opcode) {
	nutr.inst_state = long_branch;
	nutr.first_word = opcode;
	nutr.lbr_carry  = nutr.prev_carry;
}
static void op_long_branch_2 (rom_word_t opcode) {
	rom_addr_t target;
	nutr.inst_state = norm;
	target = (nutr.first_word>>2) | ((opcode &0x3FC) <<6 );
	if((opcode&0x001)==nutr.lbr_carry) {
		if(opcode&0x002) nutr.pc = target;
		else {
			push(nutr.pc);
			nutr.pc = target;
			if(nut_get_ucode(nutr.pc)==0)
				nutr.pc = pop();
		}
	}
}
static void op_goto_c        (rom_word_t opcode) {
	nutr.pc = ((nutr.c[6]<<12)|(nutr.c[5]<<8)|(nutr.c[4]<<4)|(nutr.c[3]));
}

// Bank selection used in 41CX, Advantage ROM, and perhaps others
// Check whether voyager series has this opcode or not
static void select_bank (rom_addr_t addr, uint8_t new_bank){

}
static void op_enbank   (rom_word_t opcode) {
	select_bank(nutr.prev_pc, ((opcode >> 5) & 2) + ((opcode >> 7) & 1));
}

//
// M, N operations
//
static void op_c_to_m   (rom_word_t opcode) {
	reg_copy(nutr.m, nutr.c, 0, WSIZE-1);
}
static void op_m_to_c   (rom_word_t opcode) {
	reg_copy(nutr.c, nutr.m, 0, WSIZE-1);
}
static void op_c_exch_m (rom_word_t opcode) {
	reg_exch(nutr.c, nutr.m, 0, WSIZE-1);
}
static void op_c_to_n   (rom_word_t opcode) {
	reg_copy(nutr.n, nutr.c, 0, WSIZE-1);
}
static void op_n_to_c   (rom_word_t opcode) {
	reg_copy(nutr.c, nutr.n, 0, WSIZE-1);
}
static void op_c_exch_n (rom_word_t opcode) {
	reg_exch(nutr.c, nutr.n, 0, WSIZE-1);
}

//
// RAM and peripheral operations
//
static void nut_ram_read_zero    (addr_t addr, reg_t* reg) {
	int i=0;
	for(i=0;i<WSIZE;i++) (*reg)[i] = 0;
}
static void nut_ram_write_ignore (addr_t addr, reg_t* reg) {
	;
}
static void op_c_to_dadd     (rom_word_t opcode) {
	nutr.ram_addr = ((nutr.c[2]<<8)|(nutr.c[1]<<4)|(nutr.c[0])) & 0x3FF;
	// ram select
}
static void op_c_to_pfad     (rom_word_t opcode) {
	// nutr.pf_addr = ((nutr.c[1]<<4)|(nutr.c[0]));
	// Peripheral Select
}
static void op_read_reg_n    (rom_word_t opcode) {
	uint16_t ram_addr;
	uint8_t  pf_addr;
	uint8_t      i;
	uint8_t      is_ram, is_pf;
	// for(i=0;i<WSIZE;i++) 
	nutr.c[0] = 0;
	nutr.c[1] = 0;
	nutr.c[2] = 0;
	nutr.c[3] = 0;
	nutr.c[4] = 0;
	nutr.c[5] = 0;
	nutr.c[6] = 0;
	nutr.c[7] = 0;
	nutr.c[8] = 0;
	nutr.c[9] = 0;
	nutr.c[10] = 0;
	nutr.c[11] = 0;
	nutr.c[12] = 0;
	nutr.c[13] = 0;
	if((opcode>>6)!=0)   
		nutr.ram_addr = (nutr.ram_addr & ~0x0F) | (opcode>>6);
	ram_addr = nutr.ram_addr;
	// pf_addr  = nutr.pf_addr;
	// is_ram = nutr.ram_exists[ram_addr];
	// PF & MMIO are not implemented
	for(i=0;i<WSIZE;i++) 
		nutr.c[i] = nutr.ram[ram_addr][i];
}
static void op_write_reg_n   (rom_word_t opcode) {
	uint16_t ram_addr;
	uint8_t  pf_addr;
	uint8_t      i;
	uint8_t      is_ram, is_pf;
	nutr.ram_addr = (nutr.ram_addr& ~0x0F) | (opcode >> 6);
	ram_addr = nutr.ram_addr;
	// pf_addr  = nutr.pf_addr;
	for(i=0;i<WSIZE;i++) nutr.ram[ram_addr][i] = nutr.c[i];
}
static void op_c_to_data     (rom_word_t opcode) {
	uint16_t ram_addr;
	uint8_t  pf_addr;
	int      i;
	int      is_ram, is_pf;
	
	for(i=0;i<WSIZE;i++) nutr.ram[ram_addr][i] = nutr.c[i];	
}
static void op_test_ext_flag (rom_word_t opcode) {}
static void op_selprf        (rom_word_t opcode) {}
static void op_smart_periph  (rom_word_t opcode) {}
	
//
// S operations
//
static int8_t tmap[16] = 
	{ 3, 4, 5, 10, 8, 6, 11, -1, 2, 9, 7, 13, 1, 12, 0, -1 };
static uint8_t itmap[WSIZE] =
	{ 0xe, 0xc, 0x8, 0x0, 0x1, 0x2, 0x5, 0xa, 0x4, 0x9, 0x3, 0x6, 0xd, 0xb };

static void op_set_s (rom_word_t opcode) {
	nutr.s[tmap[opcode>>6]]=1;
}
static void op_clr_s       (rom_word_t opcode) {
	nutr.s[tmap[opcode>>6]] = 0;
}
static void op_test_s      (rom_word_t opcode) {
	nutr.carry = nutr.s[tmap[opcode>>6]];
}
static uint16_t get_s_bits (uint8_t first, uint8_t count) {
	int mask = 1;
	int r = 0;
	for(int i=first;i<first+count;i++) {
		if(nutr.s[i]) r=r+mask;
		mask <<=1;
	}
	return (r);
}
static void set_s_bits (uint8_t first, uint8_t count, uint16_t a) {
	int mask = 1;
	int r = 0;
	for (int i=first;i<first+count;i++) {
		nutr.s[i] = (a&mask)!=0;
		mask <<= 1;
	}
}
static void op_clear_all_s (rom_word_t opcode) {
	set_s_bits(0,8,0);
}
static void op_c_to_s      (rom_word_t opcode) {
	set_s_bits(0,4,nutr.c[0]);
	set_s_bits(4,4,nutr.c[1]);
}
static void op_s_to_c      (rom_word_t opcode) {
	nutr.c[0] = get_s_bits(0,4);
	nutr.c[1] = get_s_bits(4,4);
}
static void op_c_exch_s    (rom_word_t opcode) {
	uint16_t t;
	t = get_s_bits(0,4);
	set_s_bits(0,4,nutr.c[0]);
	nutr.c[0] = t;
	t = get_s_bits(4,4);
	set_s_bits(4,4,nutr.c[1]);
	nutr.c[1] = t;
}
static void op_sb_to_f     (rom_word_t opcode) {
	nutr.fo = get_s_bits(0,8);
}
static void op_f_to_sb     (rom_word_t opcode) {
	set_s_bits(0,8,nutr.fo);
}
static void op_f_exch_sb   (rom_word_t opcode) {
	uint16_t t = get_s_bits(0,8);
	set_s_bits(0,8,nutr.fo);
	nutr.fo = t;
}

//
// Pointer operations
//
static void op_dec_pt   (rom_word_t opcode) {
	(*pt())--;
	if((*pt()) >= WSIZE)
		(*pt()) = WSIZE - 1;
}
static void op_inc_pt   (rom_word_t opcode) {
	(*pt())++;
	if((*pt()) >= WSIZE)
		(*pt()) = 0;
}
static void op_set_pt   (rom_word_t opcode) {
	(*pt()) = tmap[opcode>>6];
}
static void op_test_pt  (rom_word_t opcode) {
	nutr.carry = ((*pt()) == tmap[opcode>>6]);
}
static void op_sel_p    (rom_word_t opcode) {
	nutr.q_sel = false;
}
static void op_sel_q    (rom_word_t opcode) {
	nutr.q_sel = true;
}
static void op_test_pq  (rom_word_t opcode) {
	if(nutr.p == nutr.q)
		nutr.carry = 1;
}
static void op_lc       (rom_word_t opcode) {
	nutr.c[(*pt())--] = opcode>>6;
	if((*pt()) >= WSIZE)
		*pt() = WSIZE - 1; 
}
static void op_c_to_g   (rom_word_t opcode) {
	nutr.g[0] = nutr.c[*pt()];
	if((*pt()) == (WSIZE-1))
		nutr.g[1] = 0;
	else
		nutr.g[1] = nutr.c[(*pt())+1];
}
static void op_g_to_c   (rom_word_t opcode) {
	nutr.c[(*pt())] = nutr.g[0];
	if((*pt()) != (WSIZE-1))
		nutr.c[(*pt())+1] = nutr.g[1];
}
static void op_c_exch_g (rom_word_t opcode) {
	int t = nutr.g[0];
	nutr.c[*pt()]=t;
	if((*pt())==(WSIZE-1))
		nutr.g[1] = 0;
	else {
		t = nutr.g[1];
		nutr.g[1] = nutr.c[(*pt())+1];
		nutr.c[(*pt())+1]=t;
	}
}

//
// Keyboard operations
//
static void op_keys_to_rom_addr (rom_word_t opcode) {
	uint8_t keycode = KB_dequeue();
	if(keycode)
		nutr.pc = (nutr.pc&0xFF00) | KB_dequeue();
	else {
		// Shouldn't have happened
	}
}

static void op_keys_to_c (rom_word_t opcode) {
	
}


static void op_test_kb (rom_word_t opcode) {
	if(!KB_empty()) nutr.carry = 1;
}

static void op_reset_kb (rom_word_t opcode) {
	
}

//
// Misc operations
//
static void op_nop       (rom_word_t opcode) {}
static void op_set_hex   (rom_word_t opcode) {
	nutr.dec_hexn = false;
}
static void op_set_dec   (rom_word_t opcode) {
	nutr.dec_hexn = true;
}
static void op_rom_to_c  (rom_word_t opcode) {
	nutr.cxisa_addr = ((nutr.c[6]<<12)|(nutr.c[5]<<8)|(nutr.c[4]<<4)|(nutr.c[3]));
	nutr.inst_state = cxisa;
}
static void op_rom_to_c_cycle_2 (rom_word_t opcode) {
	nutr.c[2] = opcode>>8;
	nutr.c[1] = (opcode>>4) & 0x0F;
	nutr.c[0] = opcode & 0x0F;
	nutr.inst_state = norm;	
}
static void op_clear_abc (rom_word_t opcode) {
	reg_zero(nutr.a, 0, WSIZE-1);
	reg_zero(nutr.b, 0, WSIZE-1);
	reg_zero(nutr.c, 0, WSIZE-1);
}
static void op_ldi       (rom_word_t opcode) {
	nutr.inst_state = ldi;
}
static void op_ldi_cycle_2 (rom_word_t opcode) {
	nutr.c[2] = opcode>>8;
	nutr.c[1] = (opcode>>4)&0x0F;
	nutr.c[0] = opcode&0x00F;
	nutr.inst_state = norm;
}
static void op_or        (rom_word_t opcode) {
	int i;
	for(i = 0; i < WSIZE; i++)
		nutr.c[i] |= nutr.a[i];
	if(nutr.prev_carry && (nutr.prev_tef_last == (WSIZE - 1))) {
		nutr.c[WSIZE-1] = nutr.c[0];
		nutr.c[WSIZE-1] = nutr.c[0];
	}
}
static void op_and       (rom_word_t opcode) {
	int i;
	for(i = 0; i < WSIZE; i++)
		nutr.c[i] &= nutr.a[i];
	if(nutr.prev_carry && (nutr.prev_tef_last == (WSIZE - 1))) {
		nutr.c[WSIZE-1] = nutr.c[0];
		nutr.c[WSIZE-1] = nutr.c[0];
	}
}
static void op_rcr       (rom_word_t opcode) {
	int i, j;
	reg_t t;
	j = tmap[opcode>>6];
	for (i = 0; i < WSIZE; i++) {
		t[i] = nutr.c[j++];
		if(j>=WSIZE) j=0;
	}	
	for (i=0; i<WSIZE; i++)
		nutr.c[i] = t[i];
}
static void op_lld       (rom_word_t opcode) {
	// Battery Check: if batteries are low, set carry to 1
	nutr.carry = 0;
}
static void op_powoff    (rom_word_t opcode) {
	
}

//
// Voyager
//
static void op_voyager_dispblk (rom_word_t opcode) {}
static void op_voyager_dispoff (rom_word_t opcode) {}
static void op_voyager_disptog (rom_word_t opcode) {}


// Type 0 LUT
#include "nut_type0_map.h"

bool nut_execute_cycle(){
	if(nutr.inst_state==cxisa)
		nutr.prev_pc = nutr.cxisa_addr;
	else
		nutr.prev_pc = nutr.pc;
	rom_word_t opcode = nut_get_ucode(nutr.prev_pc);
	nutr.prev_carry = nutr.carry;
	nutr.carry = 0;
	switch(nutr.inst_state) {
		case norm:
			nutr.pc++;
			// deal with ops...
			uint8_t op_type = opcode&0x03;
			if(op_type==0)
				// LUT
				(type0_ptr[opcode>>2])(opcode);
			else if(op_type==1) op_long_branch(opcode);
			else if(op_type==2) op_arith(opcode);
			else                op_short_branch(opcode);
			break;
		case long_branch:
			nutr.pc++;
			op_long_branch_2(opcode);
			break;
		case cxisa:
			op_rom_to_c_cycle_2 (opcode);
			break;
		case ldi:
			nutr.pc++;
			op_ldi_cycle_2(opcode);
			break;
		case selprf:
			nutr.pc++;
			// op_smart_periph(opcode);
			// Not implemented for voyagers
			break;
		default:
			// Bad state
			// Emit Error message and failcatch
			break;
	}
	return true;
}

void nut_reset(){
	int i;
	for(i=0;i<WSIZE;i++) {
		nutr.a[i] = 0;
		nutr.b[i] = 0;
		nutr.c[i] = 0;
		nutr.m[i] = 0;
		nutr.n[i] = 0;
	}
	
	for(i=0;i<SSIZE;i++)
		nutr.s[i] = 0;
	nutr.p = 0;
	nutr.q = 0;
	nutr.q_sel = false;
	
	nutr.active_bank = 0;
	nutr.pc = 0;
	nutr.inst_state = norm;
	nutr.carry = 1;
	nutr.awake = true;
}

void nut_clear_memory(){
	
}

// Packed ops
static bool nut_read_ram(int addr, uint64_t* val){
	return true;
}

static bool nut_write_ram(int addr, uint64_t* val){
	return true;
}

