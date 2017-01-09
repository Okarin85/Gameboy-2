/* instruction.c --- 
 * 
 * Filename: instruction.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 12:36:49 2016 (+0100)
 * Last-Updated: Mon Jan  9 19:18:01 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "cpu/cpu.h"
#include "cpu/instruction.h"
#include "memory/memory.h"
#include "logger.h"

/*
 * Every "normal" (unprefixed) instruction. Every instruction returns the number of cycles it took to complete.
 */

/*
 * cpu_nop:
 * Nothing.
 */
void cpu_nop(struct CPU * cpu) {}

/*
 * cpu_halt:
 * Halts the CPU until an interrupt occurs
 */
void cpu_halt(struct CPU * cpu) { cpu->halted = true; }


/*
 * cpu_stop:
 * At the moment, does exactly like HALT (Takes the byte following the opcode)
 */
void cpu_stop(struct CPU * cpu, uint8_t nothing) { cpu->halted = true; }

/*
 * cpu_{ei,di}:
 * Enables or disables the interruptions.
 *
 * All flags untouched
 */
void cpu_ei(struct CPU * cpu) { cpu->interrupts   = true; }
void cpu_di(struct CPU * cpu) { cpu->interrupts   = false; }

/* 8-bit simple loads */
static inline void g_ld8_register(struct CPU * cpu, uint8_t * dest, uint8_t value) { (*dest) = value; }
static inline void g_ld8_memory(struct CPU * cpu, uint16_t dest, uint8_t value) { store_byte(cpu, dest, value); }

/*
 * cpu_ld_*_*
 * Loads *{2} into *{1}.
 *
 * All flags untouched.
 */
void cpu_ld_a_n(struct CPU * cpu, uint8_t operand) { g_ld8_register(cpu, &cpu->registers.a, operand); }
void cpu_ld_b_n(struct CPU * cpu, uint8_t operand) { g_ld8_register(cpu, &cpu->registers.b, operand); }
void cpu_ld_c_n(struct CPU * cpu, uint8_t operand) { g_ld8_register(cpu, &cpu->registers.c, operand); }
void cpu_ld_d_n(struct CPU * cpu, uint8_t operand) { g_ld8_register(cpu, &cpu->registers.d, operand); }
void cpu_ld_e_n(struct CPU * cpu, uint8_t operand) { g_ld8_register(cpu, &cpu->registers.e, operand); }
void cpu_ld_h_n(struct CPU * cpu, uint8_t operand) { g_ld8_register(cpu, &cpu->registers.h, operand); }
void cpu_ld_l_n(struct CPU * cpu, uint8_t operand) { g_ld8_register(cpu, &cpu->registers.l, operand); }
void cpu_ld_hl_n(struct CPU * cpu, uint8_t operand){ g_ld8_memory(cpu, cpu->registers.hl, operand); }

void cpu_ld_a_a(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, cpu->registers.a); }
void cpu_ld_a_b(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, cpu->registers.b); }
void cpu_ld_a_c(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, cpu->registers.c); }
void cpu_ld_a_d(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, cpu->registers.d); }
void cpu_ld_a_e(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, cpu->registers.e); }
void cpu_ld_a_h(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, cpu->registers.h); }
void cpu_ld_a_l(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, cpu->registers.l); }
void cpu_ld_a_hl(struct CPU * cpu) { g_ld8_register(cpu,&cpu->registers.a, fetch_byte(cpu, cpu->registers.hl)); }

void cpu_ld_b_a(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.b, cpu->registers.a); }
void cpu_ld_b_b(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.b, cpu->registers.b); }
void cpu_ld_b_c(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.b, cpu->registers.c); }
void cpu_ld_b_d(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.b, cpu->registers.d); }
void cpu_ld_b_e(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.b, cpu->registers.e); }
void cpu_ld_b_h(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.b, cpu->registers.h); }
void cpu_ld_b_l(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.b, cpu->registers.l); }
void cpu_ld_b_hl(struct CPU * cpu) { g_ld8_register(cpu,&cpu->registers.b, fetch_byte(cpu, cpu->registers.hl)); }

void cpu_ld_c_a(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.c, cpu->registers.a); }
void cpu_ld_c_b(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.c, cpu->registers.b); }
void cpu_ld_c_c(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.c, cpu->registers.c); }
void cpu_ld_c_d(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.c, cpu->registers.d); }
void cpu_ld_c_e(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.c, cpu->registers.e); }
void cpu_ld_c_h(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.c, cpu->registers.h); }
void cpu_ld_c_l(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.c, cpu->registers.l); }
void cpu_ld_c_hl(struct CPU * cpu) { g_ld8_register(cpu,&cpu->registers.c, fetch_byte(cpu, cpu->registers.hl)); }

void cpu_ld_d_a(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.d, cpu->registers.a); }
void cpu_ld_d_b(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.d, cpu->registers.b); }
void cpu_ld_d_c(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.d, cpu->registers.c); }
void cpu_ld_d_d(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.d, cpu->registers.d); }
void cpu_ld_d_e(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.d, cpu->registers.e); }
void cpu_ld_d_h(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.d, cpu->registers.h); }
void cpu_ld_d_l(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.d, cpu->registers.l); }
void cpu_ld_d_hl(struct CPU * cpu) { g_ld8_register(cpu,&cpu->registers.d, fetch_byte(cpu, cpu->registers.hl)); }

void cpu_ld_e_a(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.e, cpu->registers.a); }
void cpu_ld_e_b(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.e, cpu->registers.b); }
void cpu_ld_e_c(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.e, cpu->registers.c); }
void cpu_ld_e_d(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.e, cpu->registers.d); }
void cpu_ld_e_e(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.e, cpu->registers.e); }
void cpu_ld_e_h(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.e, cpu->registers.h); }
void cpu_ld_e_l(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.e, cpu->registers.l); }
void cpu_ld_e_hl(struct CPU * cpu) { g_ld8_register(cpu,&cpu->registers.e, fetch_byte(cpu, cpu->registers.hl)); }

void cpu_ld_h_a(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.h, cpu->registers.a); }
void cpu_ld_h_b(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.h, cpu->registers.b); }
void cpu_ld_h_c(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.h, cpu->registers.c); }
void cpu_ld_h_d(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.h, cpu->registers.d); }
void cpu_ld_h_e(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.h, cpu->registers.e); }
void cpu_ld_h_h(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.h, cpu->registers.h); }
void cpu_ld_h_l(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.h, cpu->registers.l); }
void cpu_ld_h_hl(struct CPU * cpu) { g_ld8_register(cpu,&cpu->registers.h, fetch_byte(cpu, cpu->registers.hl)); }

void cpu_ld_l_a(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.l, cpu->registers.a); }
void cpu_ld_l_b(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.l, cpu->registers.b); }
void cpu_ld_l_c(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.l, cpu->registers.c); }
void cpu_ld_l_d(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.l, cpu->registers.d); }
void cpu_ld_l_e(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.l, cpu->registers.e); }
void cpu_ld_l_h(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.l, cpu->registers.h); }
void cpu_ld_l_l(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.l, cpu->registers.l); }
void cpu_ld_l_hl(struct CPU * cpu) { g_ld8_register(cpu,&cpu->registers.l, fetch_byte(cpu, cpu->registers.hl)); }

void cpu_ld_a_nn(struct CPU * cpu, uint16_t operand) { g_ld8_register(cpu, &cpu->registers.a, fetch_byte(cpu, operand)); }

void cpu_ld_bc_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.bc, cpu->registers.a); }
void cpu_ld_de_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.de, cpu->registers.a); }

void cpu_ld_a_bc(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, fetch_byte(cpu, cpu->registers.bc)); }
void cpu_ld_a_de(struct CPU * cpu) { g_ld8_register(cpu, &cpu->registers.a, fetch_byte(cpu, cpu->registers.de)); }

void cpu_ld_hl_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); }
void cpu_ld_hl_b(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.b); }
void cpu_ld_hl_c(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.c); }
void cpu_ld_hl_d(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.d); }
void cpu_ld_hl_e(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.e); }
void cpu_ld_hl_h(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.h); }
void cpu_ld_hl_l(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.l); }

/*
 * cpu_ld_n_a
 * LD (n), a (n = 16bit constant)
 * 
 * All flags untouched.
 */
void cpu_ld_n_a(struct CPU * cpu, uint16_t operand) { g_ld8_memory(cpu, operand, cpu->registers.a); }

/*
 * cpu_ld{i,d}_hl_a:
 * Loads A into (HL), then decrements or increments HL.
 *
 * All flags untouched
 */
void cpu_ldd_hl_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); cpu->registers.hl--; }
void cpu_ldi_hl_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); cpu->registers.hl++; }

/*
 * cpu_ld{i,d}_a_hl:
 * Loads (HL) into A, then decrements or increments HL.
 *
 * All flags untouched
 */
void cpu_ldd_a_hl(struct CPU * cpu) { cpu->registers.a = fetch_byte(cpu, cpu->registers.hl);   cpu->registers.hl--; }
void cpu_ldi_a_hl(struct CPU * cpu) { cpu->registers.a = fetch_byte(cpu, cpu->registers.hl);   cpu->registers.hl++; }

/*
 * cpu_ldh_a_*:
 * Loads (0xFF00 + *) into A
 *
 * cpu_ldh_*_a:
 * Loads A into (0xFF00 + *)
 *
 * All flags untouched
 */
void cpu_ldh_c_a(struct CPU * cpu) { store_byte(cpu, 0xff00 + cpu->registers.c, cpu->registers.a); }
void cpu_ldh_a_c(struct CPU * cpu) { cpu->registers.a = fetch_byte(cpu, 0xff00 + cpu->registers.c); }
void cpu_ldh_n_a(struct CPU * cpu, uint8_t operand) { store_byte(cpu, 0xFF00 + operand, cpu->registers.a); }
void cpu_ldh_a_n(struct CPU * cpu, uint8_t operand) { cpu->registers.a = fetch_byte(cpu, 0xFF00 + operand); }

/*
 * cpu_ld_{1}_{2}:
 * Loads {1} into {2}
 *
 * All flags untouched
 */
static inline void g_ld16(struct CPU * cpu, uint16_t * dest, uint16_t value) { (*dest) = value;   }

void cpu_ld_bc_nn(struct CPU * cpu, uint16_t operand) { g_ld16(cpu, &cpu->registers.bc, operand); }
void cpu_ld_de_nn(struct CPU * cpu, uint16_t operand) { g_ld16(cpu, &cpu->registers.de, operand); }
void cpu_ld_hl_nn(struct CPU * cpu, uint16_t operand) { g_ld16(cpu, &cpu->registers.hl, operand); }
void cpu_ld_sp_nn(struct CPU * cpu, uint16_t operand) { g_ld16(cpu, &cpu->registers.sp, operand); }
void cpu_ld_sp_hl(struct CPU * cpu) { g_ld16(cpu, &cpu->registers.sp, cpu->registers.hl); cpu_delay(cpu, 1); }

/*
 * cpu_ld_hl_spnn:
 * Load SP+r8 into HL
 */
void cpu_ld_hl_spnn(struct CPU * cpu, uint8_t operand) {
    int32_t value = (int8_t)operand;
    int32_t res   = cpu->registers.sp + value;
	
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x10, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.hl = cpu->registers.sp + value;
    cpu_delay(cpu, 2);
}

/*
 * cpu_ld_nn_sp:
 * Writes SP at (nn).
 */
void cpu_ld_nn_sp(struct CPU * cpu, uint16_t operand) {
    store_word(cpu, operand, cpu->registers.sp);
}

/*
 * cpu_push_*:
 * Pushes * on the stack.
 * 
 * All flags untouched
 */
static inline void g_push16(struct CPU * cpu, uint16_t value) {
    push_word(cpu, value);
    cpu_delay(cpu, 1);
}

void cpu_push_bc(struct CPU * cpu) { g_push16(cpu, cpu->registers.bc); }
void cpu_push_de(struct CPU * cpu) { g_push16(cpu, cpu->registers.de); }
void cpu_push_hl(struct CPU * cpu) { g_push16(cpu, cpu->registers.hl); }
void cpu_push_af(struct CPU * cpu) { g_push16(cpu, cpu->registers.af); }

/*
 * cpu_pop_*:
 * Pop a word off the stack and store it in *
 * 
 * All flags untouched
 */
static inline void g_pop16(struct CPU * cpu, uint16_t * value) {
    (*value) = pop_word(cpu);
}

void cpu_pop_bc(struct CPU * cpu) { g_pop16(cpu, &cpu->registers.bc); }
void cpu_pop_de(struct CPU * cpu) { g_pop16(cpu, &cpu->registers.de); }
void cpu_pop_hl(struct CPU * cpu) { g_pop16(cpu, &cpu->registers.hl); }

/* Since the low nibble of F can only be 0, we can't just use the same function */
void cpu_pop_af(struct CPU * cpu) {
    cpu->registers.af = pop_word(cpu) & 0xFFF0;
}

/*
 * cpu_r*:
 * Almost like the function of the same name in CB, but faster
 * and unsets the zero flag
 */
void cpu_rra(struct CPU * cpu) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF(cpu->registers.a & 0x01, cpu->registers.f, CPU_FLAG_C);
    
    cpu->registers.a = (cpu->registers.a >> 1) | (carry << 7);

    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
}

void cpu_rrca(struct CPU * cpu) {
    int c = cpu->registers.a & 0x1;
    
    cpu->registers.a = (cpu->registers.a >> 1) | (c << 7);

    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(c,cpu->registers.f,CPU_FLAG_C);
}

void cpu_rla(struct CPU * cpu) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF(cpu->registers.a & 0x80, cpu->registers.f, CPU_FLAG_C);
    
    cpu->registers.a = (cpu->registers.a << 1) | carry;

    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
}

void cpu_rlca(struct CPU * cpu) {
    cpu->registers.a = (cpu->registers.a << 1) | (cpu->registers.a >> 7);
    
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(cpu->registers.a & 0x1, cpu->registers.f, CPU_FLAG_C);
}

/*
 * cpu_add_*:
 * Adds A and *, result in A
 *
 * Carry: Set if carry
 * Zero:  Set if result == 0
 * Substract: Unset
 * Half-carry: Set if half-carry
 */
static inline void g_add8(struct CPU * cpu, uint8_t reg) {
    uint8_t res = cpu->registers.a + reg;
    
    FLAG_SETIF(!res, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((((cpu->registers.a & 0xF) + (reg & 0xF)) & 0xF0), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(((cpu->registers.a + reg) & 0x100) == 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a = res;
}

void cpu_add_a(struct CPU * cpu) { g_add8(cpu, cpu->registers.a); }
void cpu_add_b(struct CPU * cpu) { g_add8(cpu, cpu->registers.b); }
void cpu_add_c(struct CPU * cpu) { g_add8(cpu, cpu->registers.c); }
void cpu_add_d(struct CPU * cpu) { g_add8(cpu, cpu->registers.d); }
void cpu_add_e(struct CPU * cpu) { g_add8(cpu, cpu->registers.e); }
void cpu_add_h(struct CPU * cpu) { g_add8(cpu, cpu->registers.h); }
void cpu_add_l(struct CPU * cpu) { g_add8(cpu, cpu->registers.l); }
void cpu_add_hl(struct CPU * cpu){ g_add8(cpu, fetch_byte(cpu, cpu->registers.hl)); }
void cpu_add_n(struct CPU * cpu, uint8_t operand) { g_add8(cpu, operand); }

/*
 * cpu_adc_*:
 * Adds A, * and carry, result in A
 *
 * Carry: Set if carry
 * Zero:  Set if result == 0
 * Substract: Unset
 * Half-carry: Set if half-carry
 */
static inline void g_adc8(struct CPU * cpu, uint8_t reg) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    int res = cpu->registers.a + reg + carry;
    uint8_t resb = res & 0xFF;
    
    FLAG_CLEARIF(resb, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((((cpu->registers.a & 0xF) + (reg & 0xF) + carry) & 0xF0), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(res & 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a = resb;
}

void cpu_adc_a(struct CPU * cpu) { g_adc8(cpu, cpu->registers.a); }
void cpu_adc_b(struct CPU * cpu) { g_adc8(cpu, cpu->registers.b); }
void cpu_adc_c(struct CPU * cpu) { g_adc8(cpu, cpu->registers.c); }
void cpu_adc_d(struct CPU * cpu) { g_adc8(cpu, cpu->registers.d); }
void cpu_adc_e(struct CPU * cpu) { g_adc8(cpu, cpu->registers.e); }
void cpu_adc_h(struct CPU * cpu) { g_adc8(cpu, cpu->registers.h); }
void cpu_adc_l(struct CPU * cpu) { g_adc8(cpu, cpu->registers.l); }
void cpu_adc_hl(struct CPU * cpu){ g_adc8(cpu, fetch_byte(cpu, cpu->registers.hl)); }
void cpu_adc_n(struct CPU * cpu, uint8_t operand) { g_adc8(cpu, operand); }

/*
 * cpu_sub_*
 * Substracts * from A
 * 
 * Carry: Set if carry
 * Zero:  Set if result == 0
 * Substract: Set
 * Half-carry: Set if half-carry
 */
static inline void g_sub8(struct CPU * cpu, uint8_t reg) {
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((cpu->registers.a & 0xF) < (reg & 0xF), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(cpu->registers.a < reg, cpu->registers.f, CPU_FLAG_C);
    
    cpu->registers.a -= reg;
    
    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
}

void cpu_sub_a(struct CPU * cpu) { g_sub8(cpu, cpu->registers.a); }
void cpu_sub_b(struct CPU * cpu) { g_sub8(cpu, cpu->registers.b); }
void cpu_sub_c(struct CPU * cpu) { g_sub8(cpu, cpu->registers.c); }
void cpu_sub_d(struct CPU * cpu) { g_sub8(cpu, cpu->registers.d); }
void cpu_sub_e(struct CPU * cpu) { g_sub8(cpu, cpu->registers.e); }
void cpu_sub_h(struct CPU * cpu) { g_sub8(cpu, cpu->registers.h); }
void cpu_sub_l(struct CPU * cpu) { g_sub8(cpu, cpu->registers.l); }
void cpu_sub_hl(struct CPU * cpu){ g_sub8(cpu, fetch_byte(cpu, cpu->registers.hl));}
void cpu_sub_n(struct CPU * cpu, uint8_t operand) { g_sub8(cpu, operand);}

/*
 * cpu_sbc_*
 * Substracts (* + carry) from A
 * 
 * Carry: Set if carry
 * Zero:  Set if result == 0
 * Substract: Set
 * Half-carry: Set if half-carry
 */
static inline void g_sbc8(struct CPU * cpu, uint8_t reg) {
    int c = ((cpu->registers.f & CPU_FLAG_C) != 0);
    
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_CLEARIF((cpu->registers.a - reg - c) & 0xFF, cpu->registers.f, CPU_FLAG_Z);
    FLAG_SETIF(((cpu->registers.a & 0xF) - (reg & 0xF) - c) < 0, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.a - reg - c) < 0, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a -= (reg + c);
}

void cpu_sbc_a(struct CPU * cpu) { g_sbc8(cpu, cpu->registers.a); }
void cpu_sbc_b(struct CPU * cpu) { g_sbc8(cpu, cpu->registers.b); }
void cpu_sbc_c(struct CPU * cpu) { g_sbc8(cpu, cpu->registers.c); }
void cpu_sbc_d(struct CPU * cpu) { g_sbc8(cpu, cpu->registers.d); }
void cpu_sbc_e(struct CPU * cpu) { g_sbc8(cpu, cpu->registers.e); }
void cpu_sbc_h(struct CPU * cpu) { g_sbc8(cpu, cpu->registers.h); }
void cpu_sbc_l(struct CPU * cpu) { g_sbc8(cpu, cpu->registers.l); }
void cpu_sbc_hl(struct CPU * cpu){ g_sbc8(cpu, fetch_byte(cpu, cpu->registers.hl)); }
void cpu_sbc_n(struct CPU * cpu, uint8_t operand) { g_sbc8(cpu, operand); }

/*
 * cpu_dec_*:
 * Decrement *
 * 
 * Carry: untouched
 * Zero: set if * == 0 after operation
 * Substract: Set
 * Half-carry: Set if half-carry
 */
static inline void g_dec8_r(struct CPU * cpu, uint8_t * reg) {
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_CLEARIF(*reg & 0xf, cpu->registers.f, CPU_FLAG_H);
    (*reg)--;
    FLAG_CLEARIF(*reg, cpu->registers.f, CPU_FLAG_Z);
}

void cpu_dec_a(struct CPU * cpu) { g_dec8_r(cpu, &cpu->registers.a); }
void cpu_dec_b(struct CPU * cpu) { g_dec8_r(cpu, &cpu->registers.b); }
void cpu_dec_c(struct CPU * cpu) { g_dec8_r(cpu, &cpu->registers.c); }
void cpu_dec_d(struct CPU * cpu) { g_dec8_r(cpu, &cpu->registers.d); }
void cpu_dec_e(struct CPU * cpu) { g_dec8_r(cpu, &cpu->registers.e); }
void cpu_dec_h(struct CPU * cpu) { g_dec8_r(cpu, &cpu->registers.h); }
void cpu_dec_l(struct CPU * cpu) { g_dec8_r(cpu, &cpu->registers.l); }

void cpu_decm_hl(struct CPU * cpu) {
    uint8_t val = fetch_byte(cpu, cpu->registers.hl);
    g_dec8_r(cpu, &val);
    store_byte(cpu, cpu->registers.hl, val);
}

/*
 * cpu_inc_*:
 * Increment *
 * 
 * Carry: untouched
 * Zero: set if * == 0 after operation
 * Substract: Unset
 * Half-carry: Set if half-carry
 */
static inline void g_inc8_r(struct CPU * cpu, uint8_t * reg) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((*reg & 0xf) == 0xf, cpu->registers.f, CPU_FLAG_H);
    (*reg)++;
    FLAG_CLEARIF(*reg, cpu->registers.f, CPU_FLAG_Z);
}

void cpu_inc_a(struct CPU * cpu) { g_inc8_r(cpu, &cpu->registers.a); }
void cpu_inc_b(struct CPU * cpu) { g_inc8_r(cpu, &cpu->registers.b); }
void cpu_inc_c(struct CPU * cpu) { g_inc8_r(cpu, &cpu->registers.c); }
void cpu_inc_d(struct CPU * cpu) { g_inc8_r(cpu, &cpu->registers.d); }
void cpu_inc_e(struct CPU * cpu) { g_inc8_r(cpu, &cpu->registers.e); }
void cpu_inc_h(struct CPU * cpu) { g_inc8_r(cpu, &cpu->registers.h); }
void cpu_inc_l(struct CPU * cpu) { g_inc8_r(cpu, &cpu->registers.l); }

void cpu_incm_hl(struct CPU * cpu) {
    uint8_t val = fetch_byte(cpu, cpu->registers.hl);
    g_inc8_r(cpu, &val);
    store_byte(cpu, cpu->registers.hl, val);
}

/*
 * cpu_cp_*:
 * Compare A and *. Same as a substraction, but the result is thrown away.
 *
 * Carry: Set if carry (if A < *)
 * Zero: Set if A == *
 * Substract: Set
 * Half-carry: Set if low nibble of A < low nibble of *
 */
static inline void g_cp(struct CPU * cpu, uint8_t value) {
    FLAG_SETIF(cpu->registers.a == value, cpu->registers.f, CPU_FLAG_Z);
    FLAG_SETIF((cpu->registers.a & 0xf) < (value & 0xf), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(cpu->registers.a < value, cpu->registers.f, CPU_FLAG_C);
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
}

void cpu_cp_a(struct CPU * cpu) { g_cp(cpu, cpu->registers.a); }
void cpu_cp_b(struct CPU * cpu) { g_cp(cpu, cpu->registers.b); }
void cpu_cp_c(struct CPU * cpu) { g_cp(cpu, cpu->registers.c); }
void cpu_cp_d(struct CPU * cpu) { g_cp(cpu, cpu->registers.d); }
void cpu_cp_e(struct CPU * cpu) { g_cp(cpu, cpu->registers.e); }
void cpu_cp_h(struct CPU * cpu) { g_cp(cpu, cpu->registers.h); }
void cpu_cp_l(struct CPU * cpu) { g_cp(cpu, cpu->registers.l); }
void cpu_cp_hl(struct CPU * cpu) { g_cp(cpu, fetch_byte(cpu, cpu->registers.hl)); }
void cpu_cp_n(struct CPU * cpu, uint8_t operand) { g_cp(cpu, operand);}

/*
 * cpu_cpl:
 * Complements all bits of A
 */
void cpu_cpl(struct CPU * cpu) {
    cpu->registers.a = ~(cpu->registers.a);
    
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SET(cpu->registers.f, CPU_FLAG_H);
}

/*
 * cpu_dec_*:
 * Decrement a 16-bit register
 *
 * All flags untouched
 */
static inline void g_dec16(struct CPU * cpu, uint16_t * value) {
    (*value)--;
    cpu_delay(cpu, 1);
}

void cpu_dec_bc(struct CPU * cpu) { g_dec16(cpu, &cpu->registers.bc); }
void cpu_dec_de(struct CPU * cpu) { g_dec16(cpu, &cpu->registers.de); }
void cpu_dec_hl(struct CPU * cpu) { g_dec16(cpu, &cpu->registers.hl); }
void cpu_dec_sp(struct CPU * cpu) { g_dec16(cpu, &cpu->registers.sp); }

/*
 * cpu_inc_*:
 * Increment a 16-bit register
 * 
 * All flags untouched
 */
static inline void g_inc16(struct CPU * cpu, uint16_t * value) {
    (*value)++;
    cpu_delay(cpu, 1);
}

void cpu_inc_bc(struct CPU * cpu) { g_inc16(cpu, &cpu->registers.bc); }
void cpu_inc_de(struct CPU * cpu) { g_inc16(cpu, &cpu->registers.de); }
void cpu_inc_hl(struct CPU * cpu) { g_inc16(cpu, &cpu->registers.hl); }
void cpu_inc_sp(struct CPU * cpu) { g_inc16(cpu, &cpu->registers.sp); }

/*
 * cpu_add_hl_*:
 * Add * to HL
 *
 * Carry: Set if carry
 * Zero: Untouched
 * Substract: Unset
 * Half-carry: Set if carry from bit 11 to 12
 */
static inline void g_add_hl16(struct CPU * cpu, uint16_t value) {
    FLAG_SETIF(((cpu->registers.hl & 0x0FFF) + (value & 0x0FFF)) & 0x1000, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.hl + value) & 0x10000, cpu->registers.f, CPU_FLAG_C);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);

    cpu->registers.hl += value;
    cpu_delay(cpu, 1);
}

void cpu_add_hl_bc(struct CPU * cpu) { g_add_hl16(cpu, cpu->registers.bc); }
void cpu_add_hl_de(struct CPU * cpu) { g_add_hl16(cpu, cpu->registers.de); }
void cpu_add_hl_hl(struct CPU * cpu) { g_add_hl16(cpu, cpu->registers.hl); }
void cpu_add_hl_sp(struct CPU * cpu) { g_add_hl16(cpu, cpu->registers.sp); }

/*
 * cpu_add_sp_nn:
 * Add signed immediate value to SP
 */
void cpu_add_sp_nn(struct CPU * cpu, uint8_t operand) {
    int32_t value = (int8_t)operand;
    int32_t res   = cpu->registers.sp + value;
    
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x10, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.sp += value;
    cpu_delay(cpu, 2);
}

/*
 * cpu_jp:
 * Jump to a given address
 */
void cpu_jp(struct CPU * cpu, uint16_t operand) { cpu->registers.pc = operand; cpu_delay(cpu, 1); }

/*
 * cpu_jr:
 * Jump to a relative address given a signed offset
 */
void cpu_jr(struct CPU * cpu, uint8_t operand)  { cpu->registers.pc+=((int8_t)operand); cpu_delay(cpu, 1); }

/*
 * cpu_jp_hl:
 * Jump to the address pointed by HL
 */
void cpu_jp_hl(struct CPU * cpu) { cpu->registers.pc = cpu->registers.hl; }

/*
 * cpu_jp_*:
 * Jump to given address if * flag is set
 */
static inline void g_cjp(struct CPU * cpu, uint16_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) cpu_jp(cpu, operand);
    else                         { };
}
void cpu_jp_z(struct CPU * cpu, uint16_t operand) { g_cjp(cpu, operand, CPU_FLAG_Z); }
void cpu_jp_c(struct CPU * cpu, uint16_t operand) { g_cjp(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_jp_n*:
 * Jump to given address if * flag is unset
 */
static inline void g_cnjp(struct CPU * cpu, uint16_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) {}
    else                         cpu_jp(cpu, operand);
}
void cpu_jp_nz(struct CPU * cpu, uint16_t operand) { g_cnjp(cpu, operand, CPU_FLAG_Z); }
void cpu_jp_nc(struct CPU * cpu, uint16_t operand) { g_cnjp(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_jr_*:
 * Jump relative if * flag is set
 */
static inline void g_cjr(struct CPU * cpu, uint8_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) cpu_jr(cpu, operand);
    else                         {};
}
void cpu_jr_z(struct CPU * cpu, uint8_t operand) { g_cjr(cpu, operand, CPU_FLAG_Z); }
void cpu_jr_c(struct CPU * cpu, uint8_t operand) { g_cjr(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_jr_n*:
 * Jump relative if * flag is unset
 */
static inline void g_cnjr(struct CPU * cpu, uint8_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) {}
    else                         cpu_jr(cpu, operand);
}
void cpu_jr_nz(struct CPU * cpu, uint8_t operand) { g_cnjr(cpu, operand, CPU_FLAG_Z); }
void cpu_jr_nc(struct CPU * cpu, uint8_t operand) { g_cnjr(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_call:
 * Pushes current PC on the stack, then jump to given address
 */
static inline void g_call(struct CPU * cpu, uint16_t address) {
    push_word(cpu, cpu->registers.pc);
    cpu->registers.pc = address;
}

void cpu_call(struct CPU * cpu, uint16_t operand) { g_call(cpu, operand); }

/*
 * cpu_call_*:
 * Call given address if * flag is set
 */
static inline void g_ccall(struct CPU * cpu, uint16_t address, uint8_t flag) {
    if (cpu->registers.f & flag) g_call(cpu, address);
    else                         {}
}

void cpu_call_c(struct CPU * cpu, uint16_t operand) { g_ccall(cpu, operand, CPU_FLAG_C); }
void cpu_call_z(struct CPU * cpu, uint16_t operand) { g_ccall(cpu, operand, CPU_FLAG_Z); }

/*
 * cpu_call_n*:
 * Call given address if * flag is unset
 */
static inline void g_cncall(struct CPU * cpu, uint16_t address, uint8_t flag) {
    if (cpu->registers.f & flag) ;
    else                         g_call(cpu, address);
}

void cpu_call_nc(struct CPU * cpu, uint16_t operand) { g_cncall(cpu, operand, CPU_FLAG_C); }
void cpu_call_nz(struct CPU * cpu, uint16_t operand) { g_cncall(cpu, operand, CPU_FLAG_Z); }

/*
 * cpu_ret:
 * Pops a word of the stack, then jump to the address pointed by it
 */
static inline void g_ret(struct CPU * cpu) {
    uint16_t address = pop_word(cpu);
    cpu->registers.pc = address;
    cpu_delay(cpu, 1);
}

void cpu_ret(struct CPU * cpu) { g_ret(cpu); }

/*
 * cpu_reti:
 * Like cpu_ret, but enables interrupts
 */
void cpu_reti(struct CPU * cpu) {
    cpu->interrupts = true;
    g_ret(cpu);
}

/*
 * cpu_ret_*:
 * Returns if * flag is set
 */
static inline void g_cret(struct CPU * cpu, uint8_t flag) {
    cpu_delay(cpu, 1);
    if (cpu->registers.f & flag) { g_ret(cpu); }
    else                         { }
}

void cpu_ret_z(struct CPU * cpu) { g_cret(cpu, CPU_FLAG_Z); }
void cpu_ret_c(struct CPU * cpu) { g_cret(cpu, CPU_FLAG_C); }

/*
 * cpu_ret_n*:
 * Returns if * flag is unset
 */
static inline void g_cnret(struct CPU * cpu, uint8_t flag) {
    if (cpu->registers.f & flag) { }
    else                         { g_ret(cpu); }
}

void cpu_ret_nz(struct CPU * cpu){ g_cnret(cpu, CPU_FLAG_Z); }
void cpu_ret_nc(struct CPU * cpu){ g_cnret(cpu, CPU_FLAG_C); }

/*
 * cpu_rst_*:
 * Calls *
 */
void cpu_rst_00(struct CPU * cpu) { g_call(cpu, 0x00); }
void cpu_rst_08(struct CPU * cpu) { g_call(cpu, 0x08); }
void cpu_rst_10(struct CPU * cpu) { g_call(cpu, 0x10); }
void cpu_rst_18(struct CPU * cpu) { g_call(cpu, 0x18); }
void cpu_rst_20(struct CPU * cpu) { g_call(cpu, 0x20); }
void cpu_rst_28(struct CPU * cpu) { g_call(cpu, 0x28); }
void cpu_rst_30(struct CPU * cpu) { g_call(cpu, 0x30); }
void cpu_rst_38(struct CPU * cpu) { g_call(cpu, 0x38); }

/*
 * Bitwise AND between A and value. Result in A.
 *
 * Carry: Unset
 * Zero: Set if A == 0 after operation
 * Substract: Unset
 * Half-carry: Set
 */
static inline void g_and(struct CPU * cpu, uint8_t value) {
    cpu->registers.a &= value;

    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SET(cpu->registers.f, CPU_FLAG_H);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_C);
}

void cpu_and_a(struct CPU * cpu)  { g_and(cpu, cpu->registers.a); }
void cpu_and_b(struct CPU * cpu)  { g_and(cpu, cpu->registers.b); }
void cpu_and_c(struct CPU * cpu)  { g_and(cpu, cpu->registers.c); }
void cpu_and_d(struct CPU * cpu)  { g_and(cpu, cpu->registers.d); }
void cpu_and_e(struct CPU * cpu)  { g_and(cpu, cpu->registers.e); }
void cpu_and_h(struct CPU * cpu)  { g_and(cpu, cpu->registers.h); }
void cpu_and_l(struct CPU * cpu)  { g_and(cpu, cpu->registers.l); }
void cpu_and_hl(struct CPU * cpu) { g_and(cpu, fetch_byte(cpu, cpu->registers.hl)); }
void cpu_and_n(struct CPU * cpu, uint8_t operand) { g_and(cpu, operand);}

/*
 * Bitwise OR between A and value. Result in A.
 *
 * Carry: Unset
 * Zero: Set if A == 0 after operation
 * Substract: Unset
 * Half-carry: Unset
 */
static inline void g_or(struct CPU * cpu, uint8_t value) {
    cpu->registers.a |= value;

    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_C);
}

void cpu_or_a(struct CPU * cpu)  { g_or(cpu, cpu->registers.a); }
void cpu_or_b(struct CPU * cpu)  { g_or(cpu, cpu->registers.b); }
void cpu_or_c(struct CPU * cpu)  { g_or(cpu, cpu->registers.c); }
void cpu_or_d(struct CPU * cpu)  { g_or(cpu, cpu->registers.d); }
void cpu_or_e(struct CPU * cpu)  { g_or(cpu, cpu->registers.e); }
void cpu_or_h(struct CPU * cpu)  { g_or(cpu, cpu->registers.h); }
void cpu_or_l(struct CPU * cpu)  { g_or(cpu, cpu->registers.l); }
void cpu_or_hl(struct CPU * cpu) { g_or(cpu, fetch_byte(cpu, cpu->registers.hl)); }
void cpu_or_n(struct CPU * cpu, uint8_t operand) { g_or(cpu, operand); }

/*
 * Bitwise XOR between A and value. Result in A.
 *
 * Carry: Unset
 * Zero: Set if A == 0 after operation
 * Substract: Unset
 * Half-carry: Unset
 */
static inline void g_xor(struct CPU * cpu, uint8_t value) {
    cpu->registers.a ^= value;

    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_C);
}

void cpu_xor_a(struct CPU * cpu)  { g_xor(cpu, cpu->registers.a); }
void cpu_xor_b(struct CPU * cpu)  { g_xor(cpu, cpu->registers.b); }
void cpu_xor_c(struct CPU * cpu)  { g_xor(cpu, cpu->registers.c); }
void cpu_xor_d(struct CPU * cpu)  { g_xor(cpu, cpu->registers.d); }
void cpu_xor_e(struct CPU * cpu)  { g_xor(cpu, cpu->registers.e); }
void cpu_xor_h(struct CPU * cpu)  { g_xor(cpu, cpu->registers.h); }
void cpu_xor_l(struct CPU * cpu)  { g_xor(cpu, cpu->registers.l); }
void cpu_xor_hl(struct CPU * cpu) { g_xor(cpu, fetch_byte(cpu, cpu->registers.hl)); }
void cpu_xor_n(struct CPU * cpu, uint8_t operand) { g_xor(cpu, operand); }

/*
 * cpu_scf:
 * Sets carry flag
 */
void cpu_scf(struct CPU * cpu) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SET(cpu->registers.f, CPU_FLAG_C);
}

/* cpu_ccf:
 * Complement Carry Flag
 */
void cpu_ccf(struct CPU * cpu) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    cpu->registers.f ^= CPU_FLAG_C;
}

/*
 * cpu_daa:
 * Decimally adjust A for BCD operations
 * 
 * Carry: Set if carry
 * Zero: Unset
 * Substract: Untouched
 * Half-carry: Unset
 */
void cpu_daa(struct CPU * cpu) {
    uint16_t a = cpu->registers.a;

    if (cpu->registers.f & CPU_FLAG_N) {
	if (cpu->registers.f & CPU_FLAG_H) { a = (a - 0x6) & 0xFF; }
	if (cpu->registers.f & CPU_FLAG_C) { a-= 0x60;             }
    } else {
	if (((a & 0xF) > 9) || (cpu->registers.f & CPU_FLAG_H)) { a += 0x06; }
	if ((a > 0x9F)      || (cpu->registers.f & CPU_FLAG_C)) { a += 0x60; }
    }

    if ((a & 0x100) == 0x100) { FLAG_SET(cpu->registers.f, CPU_FLAG_C); }
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);

    a &= 0xFF;
    if (a == 0) { FLAG_SET(cpu->registers.f, CPU_FLAG_Z); }
    cpu->registers.a = a;
}
