/* instruction.c --- 
 * 
 * Filename: instruction.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 12:36:49 2016 (+0100)
 * Last-Updated: Mon Dec 26 00:10:01 2016 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "logger.h"
#include "cpu.h"
#include "memory.h"
#include "instruction.h"

/*
 * Every instruction. Every instruction returns the number of cycles it took to complete.
 */

/* NOP instruction */
int cpu_nop(struct CPU * cpu){ return 1; }
int cpu_ei(struct CPU * cpu) { cpu->interrupts = true;  return 1; }
int cpu_di(struct CPU * cpu) { cpu->interrupts = false; return 1; }

/* 8-bit simple loads */
static inline int g_ld8_register(struct CPU * cpu, uint8_t * dest, uint8_t value) { (*dest) = value; return 1; }
static inline int g_ld8_memory(struct CPU * cpu, uint16_t dest, uint8_t value) { write_byte(cpu, dest, value); return 2; }

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

int cpu_ld_n_a(struct CPU * cpu, uint16_t operand) { return g_ld8_memory(cpu, operand, cpu->registers.a) + 2; }

int cpu_ldm_c_a(struct CPU * cpu) { return g_ld8_memory(cpu, 0xff00 + cpu->registers.c, cpu->registers.a); }
int cpu_ldm_a_c(struct CPU * cpu) { return g_ld8_register(cpu, &cpu->registers.a, read_byte(cpu, 0xff00 + cpu->registers.c)) + 1; }

/* 8-bit complex loads */
int cpu_ldd_hl_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); cpu->registers.hl--; return 2; }
int cpu_ldi_hl_a(struct CPU * cpu) { g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); cpu->registers.hl++; return 2; }
int cpu_ldd_a_hl(struct CPU * cpu) { cpu->registers.a = read_byte(cpu, cpu->registers.hl);   cpu->registers.hl--; return 2; }
int cpu_ldi_a_hl(struct CPU * cpu) { cpu->registers.a = read_byte(cpu, cpu->registers.hl);   cpu->registers.hl++; return 2; }
int cpu_ldh_n_a(struct CPU * cpu, uint8_t operand) { write_byte(cpu, 0xFF00 + operand, cpu->registers.a); return 3; }
int cpu_ldh_a_n(struct CPU * cpu, uint8_t operand) { cpu->registers.a = read_byte(cpu, 0xFF00 + operand); return 3; }

/* 16-bit loads */
static inline int g_ld16(struct CPU * cpu, uint16_t * dest, uint16_t value) { (*dest) = value; return 3; }

int cpu_ld_bc_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.bc, operand); }
int cpu_ld_de_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.de, operand); }
int cpu_ld_hl_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.hl, operand); }
int cpu_ld_sp_nn(struct CPU * cpu, uint16_t operand) { return g_ld16(cpu, &cpu->registers.sp, operand); }
int cpu_ld_sp_hl(struct CPU * cpu) { return g_ld16(cpu, &cpu->registers.sp, cpu->registers.hl); }

int cpu_ld_nn_sp(struct CPU * cpu) {
    write_word(cpu, cpu->registers.hl, cpu->registers.sp);
    return 5;
}

static inline int g_push16(struct CPU * cpu, uint16_t value) {
    push_word(cpu, value);
    return 4;
}

int cpu_push_bc(struct CPU * cpu) { return g_push16(cpu, cpu->registers.bc); }
int cpu_push_de(struct CPU * cpu) { return g_push16(cpu, cpu->registers.de); }
int cpu_push_hl(struct CPU * cpu) { return g_push16(cpu, cpu->registers.hl); }
int cpu_push_af(struct CPU * cpu) { return g_push16(cpu, cpu->registers.af); }

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

/* Rotates */
static inline int g_rl(struct CPU * cpu, uint8_t * value) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF((*value) & 0x80, cpu->registers.f, CPU_FLAG_C);
    
    (*value) = ((*value) << 1) | carry;
    
    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);

    return 2;
}

int cpu_rl_a(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.a); }
int cpu_rl_b(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.b); }
int cpu_rl_c(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.c); }
int cpu_rl_d(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.d); }
int cpu_rl_e(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.e); }
int cpu_rl_h(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.h); }
int cpu_rl_l(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.l); }

static inline int g_rr(struct CPU * cpu, uint8_t * value) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF((*value) & 0x01, cpu->registers.f, CPU_FLAG_C);
    
    (*value) = ((*value) >> 1) | (carry << 7);
    
    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    
    return 2;
}

int cpu_rr_a(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.a); }
int cpu_rr_b(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.b); }
int cpu_rr_c(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.c); }
int cpu_rr_d(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.d); }
int cpu_rr_e(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.e); }
int cpu_rr_h(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.h); }
int cpu_rr_l(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.l); }

static inline int g_rlc(struct CPU * cpu, uint8_t * value) {
    (*value) = ((*value) << 1) | ((*value) >> 7);
    
    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((*value) & 1, cpu->registers.f, CPU_FLAG_C);

    return 2;
}

int cpu_rlc_a(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.a); }
int cpu_rlc_b(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.b); }
int cpu_rlc_c(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.c); }
int cpu_rlc_d(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.d); }
int cpu_rlc_e(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.e); }
int cpu_rlc_h(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.h); }
int cpu_rlc_l(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.l); }

/* 8-bit ALU */
static inline int g_add8(struct CPU * cpu, uint8_t reg) {
    uint8_t res = cpu->registers.a + reg;
    
    FLAG_SETIF(!res, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SETIF((((cpu->registers.a & 0xF) + (reg & 0xF)) & 0x10) == 0x10, cpu->registers.f, CPU_FLAG_H);
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

static inline int g_adc8(struct CPU * cpu, uint8_t reg) {
    int carry = (cpu->registers.f & CPU_FLAG_C) >> 4;
    return g_add8(cpu, reg + carry);
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

static inline int g_sub8(struct CPU * cpu, uint8_t reg) {
    FLAG_SETIF((cpu->registers.a - reg), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_CLEARIF((((cpu->registers.a & 0xF) - (reg & 0xF)) & 0x10) == 0x10, cpu->registers.f, CPU_FLAG_H);
    FLAG_CLEARIF(((cpu->registers.a - reg) & 0x100) == 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a -= reg;
    
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

static inline int g_sbc8(struct CPU * cpu, uint8_t reg) {
    uint16_t v = reg + ((cpu->registers.f & CPU_FLAG_C) != 0);

    FLAG_SETIF((cpu->registers.a - v), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_CLEARIF((((cpu->registers.a & 0xF) - (v & 0xF)) & 0x10) == 0x10, cpu->registers.f, CPU_FLAG_H);
    FLAG_CLEARIF(((cpu->registers.a + v) & 0x100) == 0x100, cpu->registers.f, CPU_FLAG_C);

    cpu->registers.a -= v;
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

static inline int g_inc8_r(struct CPU * cpu, uint8_t * reg) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_CLEARIF((*reg & 0xf) == 0xf, cpu->registers.f, CPU_FLAG_H);
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

int cpu_cpl(struct CPU * cpu) {
    cpu->registers.a = ~(cpu->registers.a);
    
    FLAG_SET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SET(cpu->registers.f, CPU_FLAG_H);

    return 1;
}

/* 16-bit ALU */
static inline int g_dec16(struct CPU * cpu, uint16_t * value) {
    (*value)--;
    return 2;
}

int cpu_dec_bc(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.bc); }
int cpu_dec_de(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.de); }
int cpu_dec_hl(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.hl); }
int cpu_dec_sp(struct CPU * cpu) { return g_dec16(cpu, &cpu->registers.sp); }

static inline int g_inc16(struct CPU * cpu, uint16_t * value) {
    (*value)++;
    return 2;
}

int cpu_inc_bc(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.bc); }
int cpu_inc_de(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.de); }
int cpu_inc_hl(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.hl); }
int cpu_inc_sp(struct CPU * cpu) { return g_inc16(cpu, &cpu->registers.sp); }

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

/*  Inconditionnal jumps */
int cpu_jp(struct CPU * cpu, uint16_t operand) { cpu->registers.pc = operand; return 4; }
int cpu_jr(struct CPU * cpu, uint8_t operand)  { cpu->registers.pc+=((int8_t)operand); return 3; }

int cpu_jp_hl(struct CPU * cpu) { cpu->registers.pc = cpu->registers.hl; return 1; }

/* Conditionnal jumps */
static inline int g_cjp(struct CPU * cpu, uint16_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return cpu_jp(cpu, operand);
    else                         return 2;
}
int cpu_jp_z(struct CPU * cpu, uint16_t operand) { return g_cjp(cpu, operand, CPU_FLAG_Z); }
int cpu_jp_c(struct CPU * cpu, uint16_t operand) { return g_cjp(cpu, operand, CPU_FLAG_C); }

static inline int g_cnjp(struct CPU * cpu, uint16_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return 2;
    else                         return cpu_jp(cpu, operand);
}
int cpu_jp_nz(struct CPU * cpu, uint16_t operand) { return g_cnjp(cpu, operand, CPU_FLAG_Z); }
int cpu_jp_nc(struct CPU * cpu, uint16_t operand) { return g_cnjp(cpu, operand, CPU_FLAG_C); }

static inline int g_cjr(struct CPU * cpu, uint8_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return cpu_jr(cpu, operand);
    else                         return 2;
}
int cpu_jr_z(struct CPU * cpu, uint8_t operand) { return g_cjr(cpu, operand, CPU_FLAG_Z); }
int cpu_jr_c(struct CPU * cpu, uint8_t operand) { return g_cjr(cpu, operand, CPU_FLAG_C); }

static inline int g_cnjr(struct CPU * cpu, uint8_t operand, uint8_t flag) {
    if (cpu->registers.f & flag) return 2;
    else                         return cpu_jr(cpu, operand);
}
int cpu_jr_nz(struct CPU * cpu, uint8_t operand) { return g_cnjr(cpu, operand, CPU_FLAG_Z); }
int cpu_jr_nc(struct CPU * cpu, uint8_t operand) { return g_cnjr(cpu, operand, CPU_FLAG_C); }

/* Calls */
static inline int g_call(struct CPU * cpu, uint16_t address) {
    push_word(cpu, cpu->registers.pc);
    cpu->registers.pc = address;
    return 6;
}

int cpu_call(struct CPU * cpu, uint16_t operand) { return g_call(cpu, operand); }

static inline int g_ccall(struct CPU * cpu, uint16_t address, uint8_t flag) {
    if (cpu->registers.f & flag) return g_call(cpu, address);
    else                         return 3;
}

int cpu_call_c(struct CPU * cpu, uint16_t operand) { return g_ccall(cpu, operand, CPU_FLAG_C); }
int cpu_call_z(struct CPU * cpu, uint16_t operand) { return g_ccall(cpu, operand, CPU_FLAG_Z); }

static inline int g_cncall(struct CPU * cpu, uint16_t address, uint8_t flag) {
    if (cpu->registers.f & flag) return 3;
    else                         return g_call(cpu, address);
}

int cpu_call_nc(struct CPU * cpu, uint16_t operand) { return g_cncall(cpu, operand, CPU_FLAG_C); }
int cpu_call_nz(struct CPU * cpu, uint16_t operand) { return g_cncall(cpu, operand, CPU_FLAG_Z); }

/* Returns */
static inline int g_ret(struct CPU * cpu) {
    uint16_t address = pop_word(cpu);
    cpu->registers.pc = address;

    return 2;
}

int cpu_ret(struct CPU * cpu) { return g_ret(cpu); }
int cpu_reti(struct CPU * cpu) {
    g_ret(cpu);
    cpu->interrupts = true;

    return 2;
}
static inline int g_cret(struct CPU * cpu, uint8_t flag) {
    if (cpu->registers.f & flag) { g_ret(cpu); return 5; }
    else                         { return 2; }
}

int cpu_ret_z(struct CPU * cpu) { return g_cret(cpu, CPU_FLAG_Z); }
int cpu_ret_c(struct CPU * cpu) { return g_cret(cpu, CPU_FLAG_C); }

static inline int g_cnret(struct CPU * cpu, uint8_t flag) {
    if (cpu->registers.f & flag) { return 2; }
    else                         { g_ret(cpu); return 5; }
}

int cpu_ret_nz(struct CPU * cpu){ return g_cnret(cpu, CPU_FLAG_Z); }
int cpu_ret_nc(struct CPU * cpu){ return g_cnret(cpu, CPU_FLAG_C); }

/* Restarts */

int cpu_rst_00(struct CPU * cpu) { g_call(cpu, 0x00); return 8; }
int cpu_rst_08(struct CPU * cpu) { g_call(cpu, 0x08); return 8; }
int cpu_rst_10(struct CPU * cpu) { g_call(cpu, 0x10); return 8; }
int cpu_rst_18(struct CPU * cpu) { g_call(cpu, 0x18); return 8; }
int cpu_rst_20(struct CPU * cpu) { g_call(cpu, 0x20); return 8; }
int cpu_rst_28(struct CPU * cpu) { g_call(cpu, 0x28); return 8; }
int cpu_rst_30(struct CPU * cpu) { g_call(cpu, 0x30); return 8; }
int cpu_rst_38(struct CPU * cpu) { g_call(cpu, 0x38); return 8; }

/* ANDs */
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

/* ORs */
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

/* XORs */
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
 * Some "singleton" instructions.
 */
/* SCF (Set Carry Flag) */
int cpu_scf(struct CPU * cpu) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SET(cpu->registers.f, CPU_FLAG_C);
    return 1;
}

/* CCF (Complement Carry Flag */
int cpu_ccf(struct CPU * cpu) {
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    cpu->registers.f ^= CPU_FLAG_C;
    return 1;
}

/* DAA (Decimally Adjust) */
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
