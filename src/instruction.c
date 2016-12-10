/* instruction.c --- 
 * 
 * Filename: instruction.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 12:36:49 2016 (+0100)
 * Last-Updated: Sat Dec 10 23:51:11 2016 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "instruction.h"

/*
 * Every instruction. Every instruction returns the number of cycles it took to complete.
 */

/* NOP instruction */
int cpu_nop(struct CPU * cpu) { return 1; }
int cpu_ei(struct CPU * cpu) { cpu->interrupts = true; return 1; }
int cpu_di(struct CPU * cpu) { cpu->interrupts = false;return 1; }

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

int cpu_ld_hl_a(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.a); }
int cpu_ld_hl_b(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.b); }
int cpu_ld_hl_c(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.c); }
int cpu_ld_hl_d(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.d); }
int cpu_ld_hl_e(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.e); }
int cpu_ld_hl_h(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.h); }
int cpu_ld_hl_l(struct CPU * cpu) { return g_ld8_memory(cpu, cpu->registers.hl, cpu->registers.l); }

int cpu_ld_n_a(struct CPU * cpu, uint16_t operand) { return g_ld8_memory(cpu, operand, cpu->registers.a) + 2; }

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

static inline int g_push16(struct CPU * cpu, uint16_t value) {
    push_word(cpu, value);
    return 4;
}

int cpu_push_bc(struct CPU * cpu) { return g_push16(cpu, cpu->registers.bc); }
int cpu_push_de(struct CPU * cpu) { return g_push16(cpu, cpu->registers.de); }
int cpu_push_hl(struct CPU * cpu) { return g_push16(cpu, cpu->registers.hl); }
int cpu_push_af(struct CPU * cpu) { return g_push16(cpu, cpu->registers.af); }

/* 8-bit ALU */
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
int cpu_cp_hl(struct CPU * cpu) { return g_cp(cpu, read_byte(cpu, cpu->registers.hl)); }
int cpu_cp_n(struct CPU * cpu, uint8_t operand) { return g_cp(cpu, operand) + 1; }
/*  Inconditionnal jumps */
int cpu_jp(struct CPU * cpu, uint16_t operand) { cpu->registers.pc = operand - 1; return 4; }
int cpu_jr(struct CPU * cpu, uint8_t operand)  { cpu->registers.pc+=((int8_t)operand); return 3; }

/* Conditionnal jumps */
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

