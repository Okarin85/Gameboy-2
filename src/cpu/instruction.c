/* instruction.c --- 
 * 
 * Filename: instruction.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 12:36:49 2016 (+0100)
 * Last-Updated: Wed Jan  4 20:32:04 2017 (+0100)
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
int cpu_nop(struct CPU * cpu){ return 1; }

/*
 * cpu_halt:
 * Halts the CPU until an interrupt occurs
 */
int cpu_halt(struct CPU * cpu) { cpu->halted = true; return 1; }


/*
 * cpu_stop:
 * At the moment, does exactly like HALT (Takes the byte following the opcode)
 */
int cpu_stop(struct CPU * cpu, uint8_t nothing) { cpu->halted = true; return 1; }

/*
 * cpu_{ei,di}:
 * Enables or disables the interruptions.
 *
 * All flags untouched
 */
int cpu_ei(struct CPU * cpu) { cpu->interrupts   = true;  return 1; }
int cpu_di(struct CPU * cpu) { cpu->interrupts   = false; return 1; }

/* 8-bit simple loads */
static inline int g_ld8_register(struct CPU * cpu, uint8_t * dest, uint8_t value) { (*dest) = value; return 1; }
static inline int g_ld8_memory(struct CPU * cpu, uint16_t dest, uint8_t value) { write_byte(cpu, dest, value); return 2; }

/*
 * cpu_ld_*_*
 * Loads *{2} into *{1}.
 *
 * All flags untouched.
 */
int cpu_ld_a_n(struct CPU * cpu, uint8_t operand) { return g_ld8_register(cpu, &cpu->registers.a, operand); }
int cpu_ld_b_n(struct CPU * cpu, uint8_t operand) { return g_ld8_register(cpu, &cpu->registers.b, operand); }
int cpu_ld_c_n(struct CPU * cpu, uint8_t operand) { return g_ld8_register(cpu, &cpu->registers.c, operand); }
int cpu_ld_d_n(struct CPU * cpu, uint8_t operand) { return g_ld8_register(cpu, &cpu->registers.d, operand); }
int cpu_ld_e_n(struct CPU * cpu, uint8_t operand) { return g_ld8_register(cpu, &cpu->registers.e, operand); }
int cpu_ld_h_n(struct CPU * cpu, uint8_t operand) { return g_ld8_register(cpu, &cpu->registers.h, operand); }
int cpu_ld_l_n(struct CPU * cpu, uint8_t operand) { return g_ld8_register(cpu, &cpu->registers.l, operand); }
int cpu_ld_hl_n(struct CPU * cpu, uint8_t operand){ return g_ld8_memory(cpu, cpu->registers.hl, operand); }

int cpu_ld_a_a(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, cpu->registers.a); }
int cpu_ld_a_b(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, cpu->registers.b); }
int cpu_ld_a_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, cpu->registers.c); }
int cpu_ld_a_d(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, cpu->registers.d); }
int cpu_ld_a_e(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, cpu->registers.e); }
int cpu_ld_a_h(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, cpu->registers.h); }
int cpu_ld_a_l(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, cpu->registers.l); }
int cpu_ld_a_hl(struct CPU * cpu) { return g_ld8_register(cpu,&cpu->registers.a, read_byte(cpu, cpu->registers.hl)); }

int cpu_ld_b_a(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.b, cpu->registers.a); }
int cpu_ld_b_b(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.b, cpu->registers.b); }
int cpu_ld_b_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.b, cpu->registers.c); }
int cpu_ld_b_d(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.b, cpu->registers.d); }
int cpu_ld_b_e(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.b, cpu->registers.e); }
int cpu_ld_b_h(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.b, cpu->registers.h); }
int cpu_ld_b_l(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.b, cpu->registers.l); }
int cpu_ld_b_hl(struct CPU * cpu) { return g_ld8_register(cpu,&cpu->registers.b, read_byte(cpu, cpu->registers.hl)); }

int cpu_ld_c_a(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.c, cpu->registers.a); }
int cpu_ld_c_b(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.c, cpu->registers.b); }
int cpu_ld_c_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.c, cpu->registers.c); }
int cpu_ld_c_d(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.c, cpu->registers.d); }
int cpu_ld_c_e(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.c, cpu->registers.e); }
int cpu_ld_c_h(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.c, cpu->registers.h); }
int cpu_ld_c_l(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.c, cpu->registers.l); }
int cpu_ld_c_hl(struct CPU * cpu) { return g_ld8_register(cpu,&cpu->registers.c, read_byte(cpu, cpu->registers.hl)); }

int cpu_ld_d_a(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.d, cpu->registers.a); }
int cpu_ld_d_b(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.d, cpu->registers.b); }
int cpu_ld_d_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.d, cpu->registers.c); }
int cpu_ld_d_d(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.d, cpu->registers.d); }
int cpu_ld_d_e(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.d, cpu->registers.e); }
int cpu_ld_d_h(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.d, cpu->registers.h); }
int cpu_ld_d_l(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.d, cpu->registers.l); }
int cpu_ld_d_hl(struct CPU * cpu) { return g_ld8_register(cpu,&cpu->registers.d, read_byte(cpu, cpu->registers.hl)); }

int cpu_ld_e_a(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.e, cpu->registers.a); }
int cpu_ld_e_b(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.e, cpu->registers.b); }
int cpu_ld_e_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.e, cpu->registers.c); }
int cpu_ld_e_d(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.e, cpu->registers.d); }
int cpu_ld_e_e(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.e, cpu->registers.e); }
int cpu_ld_e_h(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.e, cpu->registers.h); }
int cpu_ld_e_l(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.e, cpu->registers.l); }
int cpu_ld_e_hl(struct CPU * cpu) { return g_ld8_register(cpu,&cpu->registers.e, read_byte(cpu, cpu->registers.hl)); }

int cpu_ld_h_a(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.h, cpu->registers.a); }
int cpu_ld_h_b(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.h, cpu->registers.b); }
int cpu_ld_h_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.h, cpu->registers.c); }
int cpu_ld_h_d(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.h, cpu->registers.d); }
int cpu_ld_h_e(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.h, cpu->registers.e); }
int cpu_ld_h_h(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.h, cpu->registers.h); }
int cpu_ld_h_l(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.h, cpu->registers.l); }
int cpu_ld_h_hl(struct CPU * cpu) { return g_ld8_register(cpu,&cpu->registers.h, read_byte(cpu, cpu->registers.hl)); }

int cpu_ld_l_a(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.l, cpu->registers.a); }
int cpu_ld_l_b(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.l, cpu->registers.b); }
int cpu_ld_l_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.l, cpu->registers.c); }
int cpu_ld_l_d(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.l, cpu->registers.d); }
int cpu_ld_l_e(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.l, cpu->registers.e); }
int cpu_ld_l_h(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.l, cpu->registers.h); }
int cpu_ld_l_l(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.l, cpu->registers.l); }
int cpu_ld_l_hl(struct CPU * cpu) { return g_ld8_register(cpu,&cpu->registers.l, read_byte(cpu, cpu->registers.hl)); }

int cpu_ld_a_nn(struct CPU * cpu, uint16_t operand) { g_ld8_register(cpu, &cpu->registers.a, read_byte(cpu, operand)); return 4; }

int cpu_ld_bc_a(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.bc, cpu->registers.a); }
int cpu_ld_de_a(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.de, cpu->registers.a); }

int cpu_ld_a_bc(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, read_byte(cpu, cpu->registers.bc)) + 1; }
int cpu_ld_a_de(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, read_byte(cpu, cpu->registers.de)) + 1; }

int cpu_ld_hl_a(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); }
int cpu_ld_hl_b(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.b); }
int cpu_ld_hl_c(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.c); }
int cpu_ld_hl_d(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.d); }
int cpu_ld_hl_e(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.e); }
int cpu_ld_hl_h(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.h); }
int cpu_ld_hl_l(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.l); }

/*
 * cpu_ld_n_a
 * LD (n), a (n = 16bit constant)
 * 
 * All flags untouched.
 */
int cpu_ld_n_a(struct CPU * cpu, uint16_t operand) { return g_ld8_memory(cpu, operand, cpu->registers.a) + 2; }

/*
 * cpu_ld{i,d}_hl_a:
 * Loads A into (HL), then decrements or increments HL.
 *
 * All flags untouched
 */
int cpu_ldd_hl_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); cpu->registers.hl--; return 2; }
int cpu_ldi_hl_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); cpu->registers.hl++; return 2; }

/*
 * cpu_ld{i,d}_a_hl:
 * Loads (HL) into A, then decrements or increments HL.
 *
 * All flags untouched
 */
int cpu_ldd_a_hl(struct CPU * cpu) { cpu->registers.a = read_byte(cpu, cpu->registers.hl);   cpu->registers.hl--; return 2; }
int cpu_ldi_a_hl(struct CPU * cpu) { cpu->registers.a = read_byte(cpu, cpu->registers.hl);   cpu->registers.hl++; return 2; }

/*
 * cpu_ldh_a_*:
 * Loads (0xFF00 + *) into A
 *
 * cpu_ldh_*_a:
 * Loads A into (0xFF00 + *)
 *
 * All flags untouched
 */
int cpu_ldh_c_a(struct CPU * cpu) { write_byte(cpu, 0xff00 + cpu->registers.c, cpu->registers.a); return 2; }
int cpu_ldh_a_c(struct CPU * cpu) { cpu->registers.a = read_byte(cpu, 0xff00 + cpu->registers.c); return 2; }
int cpu_ldh_n_a(struct CPU * cpu, uint8_t operand) { write_byte(cpu, 0xFF00 + operand, cpu->registers.a); return 3; }
int cpu_ldh_a_n(struct CPU * cpu, uint8_t operand) { cpu->registers.a = read_byte(cpu, 0xFF00 + operand); return 3; }

/*
 * cpu_ld_{1}_{2}:
 * Loads {1} into {2}
 *
 * All flags untouched
 */
static inline int g_ld16(struct CPU * cpu, uint16_t * dest, uint16_t value) { (*dest) = value; return 3; }

int cpu_ld_bc_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.bc, operand); }
int cpu_ld_de_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.de, operand); }
int cpu_ld_hl_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.hl, operand); }
int cpu_ld_sp_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.sp, operand); }
int cpu_ld_sp_hl(struct CPU * cpu) { return g_ld16(cpu, &cpu->registers.sp, cpu->registers.hl); }

/*
 * cpu_ld_hl_spnn:
 * Load SP+r8 into HL
 */
int cpu_ld_hl_spnn(struct CPU * cpu, uint8_t operand) {
    int32_t value = (int8_t)operand;
    int32_t res   = cpu->registers.sp + value;
	
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x10, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.hl = cpu->registers.sp + value;
    return 3;
}

/*
 * cpu_ld_nn_sp:
 * Writes SP at (HL).
 */
int cpu_ld_nn_sp(struct CPU * cpu, uint16_t operand) {
    write_word(cpu, operand, cpu->registers.sp);
    return 5;
}

/*
 * cpu_push_*:
 * Pushes * on the stack.
 * 
 * All flags untouched
 */
static inline int g_push16(struct CPU * cpu, uint16_t value) {
    push_word(cpu, value);
    return 4;
}

int cpu_push_bc(struct CPU * cpu) { return g_push16(cpu, cpu->registers.bc); }
int cpu_push_de(struct CPU * cpu) { return g_push16(cpu, cpu->registers.de); }
int cpu_push_hl(struct CPU * cpu) { return g_push16(cpu, cpu->registers.hl); }
int cpu_push_af(struct CPU * cpu) { return g_push16(cpu, cpu->registers.af); }

/*
 * cpu_pop_*:
 * Pop a word off the stack and store it in *
 * 
 * All flags untouched
 */
static inline int g_pop16(struct CPU * cpu, uint16_t * value) {
    (*value) = pop_word(cpu);
    return 3;
}

int cpu_pop_bc(struct CPU * cpu) { return g_pop16(cpu, &cpu->registers.bc); }
int cpu_pop_de(struct CPU * cpu) { return g_pop16(cpu, &cpu->registers.de); }
int cpu_pop_hl(struct CPU * cpu) { return g_pop16(cpu, &cpu->registers.hl); }

/* Since the low nibble of F can only be 0, we can't just use the same function */
int cpu_pop_af(struct CPU * cpu) {
    cpu->registers.af = pop_word(cpu) & 0xFFF0;
    return 3;
}

/*
 * cpu_r*:
 * Almost like the function of the same name in CB, but faster
 * and unsets the zero flag
 */
int cpu_rra(struct CPU * cpu) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF(cpu->registers.a & 0x01, cpu->registers.f, CPU_FLAG_C);
    
    cpu->registers.a = (cpu->registers.a >> 1) | (carry << 7);

    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    
    return 1;
}

int cpu_rrca(struct CPU * cpu) {
    int c = cpu->registers.a & 0x1;
    
    cpu->registers.a = (cpu->registers.a >> 1) | (c << 7);

    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(c,cpu->registers.f,CPU_FLAG_C);

    return 1;
}

int cpu_rla(struct CPU * cpu) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF(cpu->registers.a & 0x80, cpu->registers.f, CPU_FLAG_C);
    
    cpu->registers.a = (cpu->registers.a << 1) | carry;

    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
}

int cpu_rlca(struct CPU * cpu) {
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
static inline int g_add8(struct CPU * cpu, uint8_t reg) {
    uint8_t res = cpu->registers.a + reg;
    
    FLAG_SETIF(!res, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((((cpu->registers.a & 0xF) + (reg & 0xF)) & 0xF0), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(((cpu->registers.a + reg) & 0x100) == 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a = res;
    
    return 1;
}

int cpu_add_a(struct CPU * cpu) { return g_add8(cpu, cpu->registers.a); }
int cpu_add_b(struct CPU * cpu) { return g_add8(cpu, cpu->registers.b); }
int cpu_add_c(struct CPU * cpu) { return g_add8(cpu, cpu->registers.c); }
int cpu_add_d(struct CPU * cpu) { return g_add8(cpu, cpu->registers.d); }
int cpu_add_e(struct CPU * cpu) { return g_add8(cpu, cpu->registers.e); }
int cpu_add_h(struct CPU * cpu) { return g_add8(cpu, cpu->registers.h); }
int cpu_add_l(struct CPU * cpu) { return g_add8(cpu, cpu->registers.l); }
int cpu_add_hl(struct CPU * cpu){ return g_add8(cpu, read_byte(cpu, cpu->registers.hl)) + 1; }
int cpu_add_n(struct CPU * cpu, uint8_t operand) { return g_add8(cpu, operand) + 1; }

/*
 * cpu_adc_*:
 * Adds A, * and carry, result in A
 *
 * Carry: Set if carry
 * Zero:  Set if result == 0
 * Substract: Unset
 * Half-carry: Set if half-carry
 */
static inline int g_adc8(struct CPU * cpu, uint8_t reg) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    int res = cpu->registers.a + reg + carry;
    uint8_t resb = res & 0xFF;
    
    FLAG_CLEARIF(resb, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((((cpu->registers.a & 0xF) + (reg & 0xF) + carry) & 0xF0), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(res & 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a = resb;
}

int cpu_adc_a(struct CPU * cpu) { return g_adc8(cpu, cpu->registers.a); }
int cpu_adc_b(struct CPU * cpu) { return g_adc8(cpu, cpu->registers.b); }
int cpu_adc_c(struct CPU * cpu) { return g_adc8(cpu, cpu->registers.c); }
int cpu_adc_d(struct CPU * cpu) { return g_adc8(cpu, cpu->registers.d); }
int cpu_adc_e(struct CPU * cpu) { return g_adc8(cpu, cpu->registers.e); }
int cpu_adc_h(struct CPU * cpu) { return g_adc8(cpu, cpu->registers.h); }
int cpu_adc_l(struct CPU * cpu) { return g_adc8(cpu, cpu->registers.l); }
int cpu_adc_hl(struct CPU * cpu){ return g_adc8(cpu, read_byte(cpu, cpu->registers.hl)) + 1; }
int cpu_adc_n(struct CPU * cpu, uint8_t operand) { return g_adc8(cpu, operand) + 1; }

/*
 * cpu_sub_*
 * Substracts * from A
 * 
 * Carry: Set if carry
 * Zero:  Set if result == 0
 * Substract: Set
 * Half-carry: Set if half-carry
 */
static inline int g_sub8(struct CPU * cpu, uint8_t reg) {
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((cpu->registers.a & 0xF) < (reg & 0xF), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(cpu->registers.a < reg, cpu->registers.f, CPU_FLAG_C);
    
    cpu->registers.a -= reg;
    
    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
    return 1;
}

int cpu_sub_a(struct CPU * cpu) { return g_sub8(cpu, cpu->registers.a); }
int cpu_sub_b(struct CPU * cpu) { return g_sub8(cpu, cpu->registers.b); }
int cpu_sub_c(struct CPU * cpu) { return g_sub8(cpu, cpu->registers.c); }
int cpu_sub_d(struct CPU * cpu) { return g_sub8(cpu, cpu->registers.d); }
int cpu_sub_e(struct CPU * cpu) { return g_sub8(cpu, cpu->registers.e); }
int cpu_sub_h(struct CPU * cpu) { return g_sub8(cpu, cpu->registers.h); }
int cpu_sub_l(struct CPU * cpu) { return g_sub8(cpu, cpu->registers.l); }
int cpu_sub_hl(struct CPU * cpu){ return g_sub8(cpu, read_byte(cpu, cpu->registers.hl)) + 1; }
int cpu_sub_n(struct CPU * cpu, uint8_t operand) { return g_sub8(cpu, operand) + 1; }

/*
 * cpu_sbc_*
 * Substracts (* + carry) from A
 * 
 * Carry: Set if carry
 * Zero:  Set if result == 0
 * Substract: Set
 * Half-carry: Set if half-carry
 */
static inline int g_sbc8(struct CPU * cpu, uint8_t reg) {
    int c = ((cpu->registers.f & CPU_FLAG_C) != 0);
    int r = cpu->registers.a - reg - c;
    
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_CLEARIF((cpu->registers.a - reg - c) & 0xFF, cpu->registers.f, CPU_FLAG_Z);
    FLAG_SETIF(((cpu->registers.a & 0xF) - (reg & 0xF) - c) < 0, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.a - reg - c) < 0, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a -= (reg + c);
    return 1;
}

int cpu_sbc_a(struct CPU * cpu) { return g_sbc8(cpu, cpu->registers.a); }
int cpu_sbc_b(struct CPU * cpu) { return g_sbc8(cpu, cpu->registers.b); }
int cpu_sbc_c(struct CPU * cpu) { return g_sbc8(cpu, cpu->registers.c); }
int cpu_sbc_d(struct CPU * cpu) { return g_sbc8(cpu, cpu->registers.d); }
int cpu_sbc_e(struct CPU * cpu) { return g_sbc8(cpu, cpu->registers.e); }
int cpu_sbc_h(struct CPU * cpu) { return g_sbc8(cpu, cpu->registers.h); }
int cpu_sbc_l(struct CPU * cpu) { return g_sbc8(cpu, cpu->registers.l); }
int cpu_sbc_hl(struct CPU * cpu){ return g_sbc8(cpu, read_byte(cpu, cpu->registers.hl)) + 1; }
int cpu_sbc_n(struct CPU * cpu, uint8_t operand) { return g_sbc8(cpu, operand) + 1; }

/*
 * cpu_dec_*:
 * Decrement *
 * 
 * Carry: untouched
 * Zero: set if * == 0 after operation
 * Substract: Set
 * Half-carry: Set if half-carry
 */
static inline int g_dec8_r(struct CPU * cpu, uint8_t * reg) {
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_CLEARIF(*reg & 0xf, cpu->registers.f, CPU_FLAG_H);
    (*reg)--;
    FLAG_CLEARIF(*reg, cpu->registers.f, CPU_FLAG_Z);
    
    return 1;
}

int cpu_dec_a(struct CPU * cpu) { return g_dec8_r(cpu, &cpu->registers.a); }
int cpu_dec_b(struct CPU * cpu) { return g_dec8_r(cpu, &cpu->registers.b); }
int cpu_dec_c(struct CPU * cpu) { return g_dec8_r(cpu, &cpu->registers.c); }
int cpu_dec_d(struct CPU * cpu) { return g_dec8_r(cpu, &cpu->registers.d); }
int cpu_dec_e(struct CPU * cpu) { return g_dec8_r(cpu, &cpu->registers.e); }
int cpu_dec_h(struct CPU * cpu) { return g_dec8_r(cpu, &cpu->registers.h); }
int cpu_dec_l(struct CPU * cpu) { return g_dec8_r(cpu, &cpu->registers.l); }

int cpu_decm_hl(struct CPU * cpu) {
    uint8_t val = read_byte(cpu, cpu->registers.hl);
    g_dec8_r(cpu, &val);
    write_byte(cpu, cpu->registers.hl, val);

    return 2;
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
static inline int g_inc8_r(struct CPU * cpu, uint8_t * reg) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((*reg & 0xf) == 0xf, cpu->registers.f, CPU_FLAG_H);
    (*reg)++;
    FLAG_CLEARIF(*reg, cpu->registers.f, CPU_FLAG_Z);

    return 1;
}

int cpu_inc_a(struct CPU * cpu) { return g_inc8_r(cpu, &cpu->registers.a); }
int cpu_inc_b(struct CPU * cpu) { return g_inc8_r(cpu, &cpu->registers.b); }
int cpu_inc_c(struct CPU * cpu) { return g_inc8_r(cpu, &cpu->registers.c); }
int cpu_inc_d(struct CPU * cpu) { return g_inc8_r(cpu, &cpu->registers.d); }
int cpu_inc_e(struct CPU * cpu) { return g_inc8_r(cpu, &cpu->registers.e); }
int cpu_inc_h(struct CPU * cpu) { return g_inc8_r(cpu, &cpu->registers.h); }
int cpu_inc_l(struct CPU * cpu) { return g_inc8_r(cpu, &cpu->registers.l); }

int cpu_incm_hl(struct CPU * cpu) {
    uint8_t val = read_byte(cpu, cpu->registers.hl);
    g_inc8_r(cpu, &val);
    write_byte(cpu, cpu->registers.hl, val);

    return 2;
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
static inline int g_cp(struct CPU * cpu, uint8_t value) {
    FLAG_SETIF(cpu->registers.a == value, cpu->registers.f, CPU_FLAG_Z);
    FLAG_SETIF((cpu->registers.a & 0xf) < (value & 0xf), cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF(cpu->registers.a < value, cpu->registers.f, CPU_FLAG_C);
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    
    return 1;
}

int cpu_cp_a(struct CPU * cpu) { return g_cp(cpu, cpu->registers.a); }
int cpu_cp_b(struct CPU * cpu) { return g_cp(cpu, cpu->registers.b); }
int cpu_cp_c(struct CPU * cpu) { return g_cp(cpu, cpu->registers.c); }
int cpu_cp_d(struct CPU * cpu) { return g_cp(cpu, cpu->registers.d); }
int cpu_cp_e(struct CPU * cpu) { return g_cp(cpu, cpu->registers.e); }
int cpu_cp_h(struct CPU * cpu) { return g_cp(cpu, cpu->registers.h); }
int cpu_cp_l(struct CPU * cpu) { return g_cp(cpu, cpu->registers.l); }
int cpu_cp_hl(struct CPU * cpu) { return g_cp(cpu, read_byte(cpu, cpu->registers.hl)) + 1; }
int cpu_cp_n(struct CPU * cpu, uint8_t operand) { return g_cp(cpu, operand) + 1; }

/*
 * cpu_cpl:
 * Complements all bits of A
 */
int cpu_cpl(struct CPU * cpu) {
    cpu->registers.a = ~(cpu->registers.a);
    
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SET(cpu->registers.f, CPU_FLAG_H);

    return 1;
}

/*
 * cpu_dec_*:
 * Decrement a 16-bit register
 *
 * All flags untouched
 */
static inline int g_dec16(struct CPU * cpu, uint16_t * value) {
    (*value)--;
    return 2;
}

int cpu_dec_bc(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.bc); }
int cpu_dec_de(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.de); }
int cpu_dec_hl(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.hl); }
int cpu_dec_sp(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.sp); }

/*
 * cpu_inc_*:
 * Increment a 16-bit register
 * 
 * All flags untouched
 */
static inline int g_inc16(struct CPU * cpu, uint16_t * value) {
    (*value)++;
    return 2;
}

int cpu_inc_bc(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.bc); }
int cpu_inc_de(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.de); }
int cpu_inc_hl(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.hl); }
int cpu_inc_sp(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.sp); }

/*
 * cpu_add_hl_*:
 * Add * to HL
 *
 * Carry: Set if carry
 * Zero: Untouched
 * Substract: Unset
 * Half-carry: Set if carry from bit 11 to 12
 */
static inline int g_add_hl16(struct CPU * cpu, uint16_t value) {
    FLAG_SETIF(((cpu->registers.hl & 0x0FFF) + (value & 0x0FFF)) & 0x1000, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.hl + value) & 0x10000, cpu->registers.f, CPU_FLAG_C);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);

    cpu->registers.hl += value;
    return 2;
}

int cpu_add_hl_bc(struct CPU * cpu) { return g_add_hl16(cpu, cpu->registers.bc); }
int cpu_add_hl_de(struct CPU * cpu) { return g_add_hl16(cpu, cpu->registers.de); }
int cpu_add_hl_hl(struct CPU * cpu) { return g_add_hl16(cpu, cpu->registers.hl); }
int cpu_add_hl_sp(struct CPU * cpu) { return g_add_hl16(cpu, cpu->registers.sp); }

/*
 * cpu_add_sp_nn:
 * Add signed immediate value to SP
 */
int cpu_add_sp_nn(struct CPU * cpu, uint8_t operand) {
    int32_t value = (int8_t)operand;
    int32_t res   = cpu->registers.sp + value;
    
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x10, cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((cpu->registers.sp ^ value ^ res) & 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.sp += value;
    return 4;
}

/*
 * cpu_jp:
 * Jump to a given address
 */
int cpu_jp(struct CPU * cpu, uint16_t operand) { cpu->registers.pc = operand; return 4; }

/*
 * cpu_jr:
 * Jump to a relative address given a signed offset
 */
int cpu_jr(struct CPU * cpu, uint8_t operand)  { cpu->registers.pc+=((int8_t)operand); return 3; }

/*
 * cpu_jp_hl:
 * Jump to the address pointed by HL
 */
int cpu_jp_hl(struct CPU * cpu) { cpu->registers.pc = cpu->registers.hl; return 1; }

/*
 * cpu_jp_*:
 * Jump to given address if * flag is set
 */
static inline int g_cjp(struct CPU * cpu, uint16_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return cpu_jp(cpu, operand);
    else                         return 2;
}
int cpu_jp_z(struct CPU * cpu, uint16_t operand) { return g_cjp(cpu, operand, CPU_FLAG_Z); }
int cpu_jp_c(struct CPU * cpu, uint16_t operand) { return g_cjp(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_jp_n*:
 * Jump to given address if * flag is unset
 */
static inline int g_cnjp(struct CPU * cpu, uint16_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return 2;
    else                         return cpu_jp(cpu, operand);
}
int cpu_jp_nz(struct CPU * cpu, uint16_t operand) { return g_cnjp(cpu, operand, CPU_FLAG_Z); }
int cpu_jp_nc(struct CPU * cpu, uint16_t operand) { return g_cnjp(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_jr_*:
 * Jump relative if * flag is set
 */
static inline int g_cjr(struct CPU * cpu, uint8_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return cpu_jr(cpu, operand);
    else                         return 2;
}
int cpu_jr_z(struct CPU * cpu, uint8_t operand) { return g_cjr(cpu, operand, CPU_FLAG_Z); }
int cpu_jr_c(struct CPU * cpu, uint8_t operand) { return g_cjr(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_jr_n*:
 * Jump relative if * flag is unset
 */
static inline int g_cnjr(struct CPU * cpu, uint8_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return 2;
    else                         return cpu_jr(cpu, operand);
}
int cpu_jr_nz(struct CPU * cpu, uint8_t operand) { return g_cnjr(cpu, operand, CPU_FLAG_Z); }
int cpu_jr_nc(struct CPU * cpu, uint8_t operand) { return g_cnjr(cpu, operand, CPU_FLAG_C); }

/*
 * cpu_call:
 * Pushes current PC on the stack, then jump to given address
 */
static inline int g_call(struct CPU * cpu, uint16_t address) {
    push_word(cpu, cpu->registers.pc);
    cpu->registers.pc = address;
    return 6;
}

int cpu_call(struct CPU * cpu, uint16_t operand) { return g_call(cpu, operand); }

/*
 * cpu_call_*:
 * Call given address if * flag is set
 */
static inline int g_ccall(struct CPU * cpu, uint16_t address, uint8_t flag) {
    if (cpu->registers.f & flag) return g_call(cpu, address);
    else                         return 3;
}

int cpu_call_c(struct CPU * cpu, uint16_t operand) { return g_ccall(cpu, operand, CPU_FLAG_C); }
int cpu_call_z(struct CPU * cpu, uint16_t operand) { return g_ccall(cpu, operand, CPU_FLAG_Z); }

/*
 * cpu_call_n*:
 * Call given address if * flag is unset
 */
static inline int g_cncall(struct CPU * cpu, uint16_t address, uint8_t flag) {
    if (cpu->registers.f & flag) return 3;
    else                         return g_call(cpu, address);
}

int cpu_call_nc(struct CPU * cpu, uint16_t operand) { return g_cncall(cpu, operand, CPU_FLAG_C); }
int cpu_call_nz(struct CPU * cpu, uint16_t operand) { return g_cncall(cpu, operand, CPU_FLAG_Z); }

/*
 * cpu_ret:
 * Pops a word of the stack, then jump to the address pointed by it
 */
static inline int g_ret(struct CPU * cpu) {
    uint16_t address = pop_word(cpu);
    cpu->registers.pc = address;

    return 2;
}

int cpu_ret(struct CPU * cpu) { return g_ret(cpu); }

/*
 * cpu_reti:
 * Like cpu_ret, but enables interrupts
 */
int cpu_reti(struct CPU * cpu) {
    g_ret(cpu);
    cpu->interrupts = true;

    return 2;
}

/*
 * cpu_ret_*:
 * Returns if * flag is set
 */
static inline int g_cret(struct CPU * cpu, uint8_t flag) {
    if (cpu->registers.f & flag) { g_ret(cpu); return 5; }
    else                         { return 2; }
}

int cpu_ret_z(struct CPU * cpu) { return g_cret(cpu, CPU_FLAG_Z); }
int cpu_ret_c(struct CPU * cpu) { return g_cret(cpu, CPU_FLAG_C); }

/*
 * cpu_ret_n*:
 * Returns if * flag is unset
 */
static inline int g_cnret(struct CPU * cpu, uint8_t flag) {
    if (cpu->registers.f & flag) { return 2; }
    else                         { g_ret(cpu); return 5; }
}

int cpu_ret_nz(struct CPU * cpu){ return g_cnret(cpu, CPU_FLAG_Z); }
int cpu_ret_nc(struct CPU * cpu){ return g_cnret(cpu, CPU_FLAG_C); }

/*
 * cpu_rst_*:
 * Calls *
 */
int cpu_rst_00(struct CPU * cpu) { g_call(cpu, 0x00); return 4; }
int cpu_rst_08(struct CPU * cpu) { g_call(cpu, 0x08); return 4; }
int cpu_rst_10(struct CPU * cpu) { g_call(cpu, 0x10); return 4; }
int cpu_rst_18(struct CPU * cpu) { g_call(cpu, 0x18); return 4; }
int cpu_rst_20(struct CPU * cpu) { g_call(cpu, 0x20); return 4; }
int cpu_rst_28(struct CPU * cpu) { g_call(cpu, 0x28); return 4; }
int cpu_rst_30(struct CPU * cpu) { g_call(cpu, 0x30); return 4; }
int cpu_rst_38(struct CPU * cpu) { g_call(cpu, 0x38); return 4; }

/*
 * Bitwise AND between A and value. Result in A.
 *
 * Carry: Unset
 * Zero: Set if A == 0 after operation
 * Substract: Unset
 * Half-carry: Set
 */
static inline int g_and(struct CPU * cpu, uint8_t value) {
    cpu->registers.a &= value;

    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SET(cpu->registers.f, CPU_FLAG_H);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_C);
    return 1;
}

int cpu_and_a(struct CPU * cpu)  { return g_and(cpu, cpu->registers.a); }
int cpu_and_b(struct CPU * cpu)  { return g_and(cpu, cpu->registers.b); }
int cpu_and_c(struct CPU * cpu)  { return g_and(cpu, cpu->registers.c); }
int cpu_and_d(struct CPU * cpu)  { return g_and(cpu, cpu->registers.d); }
int cpu_and_e(struct CPU * cpu)  { return g_and(cpu, cpu->registers.e); }
int cpu_and_h(struct CPU * cpu)  { return g_and(cpu, cpu->registers.h); }
int cpu_and_l(struct CPU * cpu)  { return g_and(cpu, cpu->registers.l); }
int cpu_and_hl(struct CPU * cpu) { return g_and(cpu, read_byte(cpu, cpu->registers.hl)) + 1; }
int cpu_and_n(struct CPU * cpu, uint8_t operand) { return g_and(cpu, operand) + 1; }

/*
 * Bitwise OR between A and value. Result in A.
 *
 * Carry: Unset
 * Zero: Set if A == 0 after operation
 * Substract: Unset
 * Half-carry: Unset
 */
static inline int g_or(struct CPU * cpu, uint8_t value) {
    cpu->registers.a |= value;

    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_C);
    return 1;
}

int cpu_or_a(struct CPU * cpu)  { return g_or(cpu, cpu->registers.a); }
int cpu_or_b(struct CPU * cpu)  { return g_or(cpu, cpu->registers.b); }
int cpu_or_c(struct CPU * cpu)  { return g_or(cpu, cpu->registers.c); }
int cpu_or_d(struct CPU * cpu)  { return g_or(cpu, cpu->registers.d); }
int cpu_or_e(struct CPU * cpu)  { return g_or(cpu, cpu->registers.e); }
int cpu_or_h(struct CPU * cpu)  { return g_or(cpu, cpu->registers.h); }
int cpu_or_l(struct CPU * cpu)  { return g_or(cpu, cpu->registers.l); }
int cpu_or_hl(struct CPU * cpu) { return g_or(cpu, read_byte(cpu, cpu->registers.hl)); }
int cpu_or_n(struct CPU * cpu, uint8_t operand) { return g_or(cpu, operand) + 1; }

/*
 * Bitwise XOR between A and value. Result in A.
 *
 * Carry: Unset
 * Zero: Set if A == 0 after operation
 * Substract: Unset
 * Half-carry: Unset
 */
static inline int g_xor(struct CPU * cpu, uint8_t value) {
    cpu->registers.a ^= value;

    FLAG_CLEARIF(cpu->registers.a, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_C);
    return 1;
}

int cpu_xor_a(struct CPU * cpu)  { return g_xor(cpu, cpu->registers.a); }
int cpu_xor_b(struct CPU * cpu)  { return g_xor(cpu, cpu->registers.b); }
int cpu_xor_c(struct CPU * cpu)  { return g_xor(cpu, cpu->registers.c); }
int cpu_xor_d(struct CPU * cpu)  { return g_xor(cpu, cpu->registers.d); }
int cpu_xor_e(struct CPU * cpu)  { return g_xor(cpu, cpu->registers.e); }
int cpu_xor_h(struct CPU * cpu)  { return g_xor(cpu, cpu->registers.h); }
int cpu_xor_l(struct CPU * cpu)  { return g_xor(cpu, cpu->registers.l); }
int cpu_xor_hl(struct CPU * cpu) { return g_xor(cpu, read_byte(cpu, cpu->registers.hl)); }
int cpu_xor_n(struct CPU * cpu, uint8_t operand) { return g_xor(cpu, operand) + 1; }

/*
 * cpu_scf:
 * Sets carry flag
 */
int cpu_scf(struct CPU * cpu) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SET(cpu->registers.f, CPU_FLAG_C);
    return 1;
}

/* cpu_ccf:
 * Complement Carry Flag
 */
int cpu_ccf(struct CPU * cpu) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    cpu->registers.f ^= CPU_FLAG_C;
    return 1;
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
int cpu_daa(struct CPU * cpu) {
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
    
    return 1;
}
