/*
$Id: proc_nut.h 811 2005-06-19 20:23:39Z eric $
Copyright 1995, 2003, 2004, 2005 Eric L. Smith <eric@brouhaha.com>

Simplified & Flash Constant-ified for SAM4L Implementation
Jul.23.2021 Anhang.Li <thelithcore@gmail.com>

Nonpareil is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.  Note that I am not
granting permission to redistribute or modify Nonpareil under the
terms of any later version of the General Public License.

Nonpareil is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program (in the file "COPYING"); if not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111, USA.
*/


#ifndef NUT_H_
#define NUT_H_

#define WSIZE   14
#define EXPSIZE 3
#define SSIZE   14
#define EXT_FLAG_SIZE 14
#define STACK_DEPTH 4
#define PAGE_SIZE   4096
#define MAX_PAGE    16
#define MAX_BANK    4


// Reserved Space for RAM
// (May not be fully addressable by the VROM)
#define RAMSIZE 1024
#define PFSIZE  256

typedef uint8_t  digit_t;		// Unpacked BCD 
typedef digit_t  reg_t [WSIZE];
typedef uint32_t addr_t;
typedef uint16_t rom_word_t;
typedef uint16_t rom_addr_t;
typedef uint64_t packed_reg_t;	// Packing 56-bit into this for storage
typedef void call_t(rom_word_t opcode);
// BCD Calculation Prototypes
// CM4 Doesn't provide BCD functionality, but it's possible to perform 32bit(8nibs) addition using 
// 32bit ARM instructions for the highest performance.
void reg_zero (digit_t* dest, uint8_t first, uint8_t last);
void reg_copy (digit_t* dest, const digit_t* src, uint8_t first, uint8_t last);
void reg_add  (digit_t *dest, const digit_t *src1, const digit_t *src2,
               uint8_t first, uint8_t last, bool *carry, uint8_t base);
void reg_sub  (digit_t *dest, const digit_t *src1, const digit_t *src2,
               uint8_t first, uint8_t last, bool *carry, uint8_t base);
void reg_exch (digit_t* dest, digit_t* src, uint8_t first, uint8_t last);
// sets carry if equal
void reg_teq  (const digit_t *src1, const digit_t *src2,
               uint8_t first, uint8_t last, bool *carry);
// sets carry if nonequal
void reg_tneq (const digit_t *src1, const digit_t *src2,
               uint8_t first, uint8_t last, bool *carry);
void reg_sr   (digit_t *reg, uint8_t first, uint8_t last);
void reg_sl   (digit_t *reg, uint8_t first, uint8_t last);
// BCD to native host binary and vice versa
uint64_t bcd_reg_to_binary (digit_t* reg, uint8_t digits);
void     binary_to_bcd_reg (uint64_t val, digit_t *reg, uint8_t digits);

rom_word_t nut_get_ucode(rom_addr_t addr);
bool nut_execute_cycle(void);
void nut_reset(void);
void nut_clear_memory(void);

// 
typedef enum {
	norm,
	long_branch,
	cxisa,
	ldi,
	selprf         // "smart" peripheral selected (NPIC, PIL)
} inst_state_t;


typedef struct nut_reg_t {
	reg_t   a;
	reg_t   b;
	reg_t   c;
	reg_t   m;
	reg_t   n;
	digit_t g[2];
	digit_t p;
	digit_t q;
	bool    q_sel;			// true is q is the selected pointer, false for p
	bool    dec_hexn;		// true for arithemetic radix 10, false for 16
	bool    carry;			// carry being generated in the current instruction
	bool    prev_carry;		// carry that resulted from previous calculation
	uint8_t prev_tef_last;	// last digit of fied of previous arith. inrtruction
							// used to simulate bug in logical or and and.
	uint8_t  s[SSIZE];		// Modified to use a single variable
	uint16_t fo;			// flag output registers, used to drive bender;
	
	rom_addr_t pc;
	rom_addr_t prev_pc;
	rom_addr_t stack [STACK_DEPTH];
	rom_addr_t cxisa_addr;
	inst_state_t inst_state;
	rom_word_t first_word;	// for long-branch instructions
	bool       lbr_carry;	// 
	bool       key_down;
	uint16_t   key_code;
	// the keyboard scanning & state control is implemented elsewhere
	bool       awake;
	// the opcode LUT is implemented as a flash-ROM constant
	// void (* op_fcn [1024])(struct nut_reg_t* regs, rom_word_t opcode);
	
	// ROM:
	int     bank_group [MAX_PAGE];
	uint8_t active_bank;
	// uint8_t active_bank [MAX_PAGE]; // Simplified for Voyager
	// the ROM I/O & debugging functions are not implemented for voyager
	// the ROM itself is implemented as a flash-ROM constant
	
	// RAM:
	uint16_t ram_addr;	// selected RAM address
	reg_t    ram[RAMSIZE];		// probably use packed word instead
	// the RAM Access functions are hard-coded instead
	
	// Peripherals:
	// Not implemented for voyagers
	uint16_t pf_addr;
	
	// Display and I/O are hard-coded
	} nut_reg_t;
typedef void ram_access_fn_t (struct nut_reg_t* nut_reg, uint16_t addr, reg_t* reg);





#endif /* NUT_H_ */