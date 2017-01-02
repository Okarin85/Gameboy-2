/* cb.c --- 
 * 
 * Filename: cb.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 22:40:29 2016 (+0100)
 * Last-Updated: Mon Jan  2 07:48:17 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include <unistd.h>
#include "cpu/cpu.h"
#include "cpu/instruction.h"
#include "memory/memory.h"
#include "logger.h"

/*
 * cb_sla_*:
 * Shift value left into Carry.
 * 
 * Carry: old value of bit 7
 * Zero: set if * equals zero after the operation
 * Substract and Half-carry: Unset
 */
static inline int gcb_sla(struct CPU * cpu, uint8_t * value) {
    FLAG_SETIF((*value) & 0x80, cpu->registers.f, CPU_FLAG_C);

    (*value) <<= 1;

    FLAG_CLEARIF((*value) & 0x7f, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    return 2;
}

int cb_sla_a(struct CPU * cpu) { return gcb_sla(cpu, &cpu->registers.a); }
int cb_sla_b(struct CPU * cpu) { return gcb_sla(cpu, &cpu->registers.b); }
int cb_sla_c(struct CPU * cpu) { return gcb_sla(cpu, &cpu->registers.c); }
int cb_sla_d(struct CPU * cpu) { return gcb_sla(cpu, &cpu->registers.d); }
int cb_sla_e(struct CPU * cpu) { return gcb_sla(cpu, &cpu->registers.e); }
int cb_sla_h(struct CPU * cpu) { return gcb_sla(cpu, &cpu->registers.h); }
int cb_sla_l(struct CPU * cpu) { return gcb_sla(cpu, &cpu->registers.l); }

/*
 * cb_sra_*:
 * Shift value right into carry. MSB unchanged.
 * 
 * Carry: Old bit 0
 * Zero: Set if value == 0 after the operation
 * Substract and Half-carry: Unset 
 */
static inline int gcb_sra(struct CPU * cpu, uint8_t * value) {
    FLAG_SETIF((*value) & 0x1, cpu->registers.f, CPU_FLAG_C);

    (*value) = ((*value) & 0x80) | ((*value) >> 1);

    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    return 2;
}

int cb_sra_a(struct CPU * cpu) { return gcb_sra(cpu, &cpu->registers.a); }
int cb_sra_b(struct CPU * cpu) { return gcb_sra(cpu, &cpu->registers.b); }
int cb_sra_c(struct CPU * cpu) { return gcb_sra(cpu, &cpu->registers.c); }
int cb_sra_d(struct CPU * cpu) { return gcb_sra(cpu, &cpu->registers.d); }
int cb_sra_e(struct CPU * cpu) { return gcb_sra(cpu, &cpu->registers.e); }
int cb_sra_h(struct CPU * cpu) { return gcb_sra(cpu, &cpu->registers.h); }
int cb_sra_l(struct CPU * cpu) { return gcb_sra(cpu, &cpu->registers.l); }

/*
 * cb_srl_*:
 * Shift value right into carry. MSB set to 0.
 *
 * Carry: Old bit 0
 * Zero: Set if value == 0 after the operation
 * Substract and Half-carry: Unset
 */
static inline int gcb_srl(struct CPU * cpu, uint8_t * value) {
    FLAG_SETIF((*value) & 0x01, cpu->registers.f, CPU_FLAG_C);
    (*value) >>= 1;

    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    return 2;
}

int cb_srl_a(struct CPU * cpu) { return gcb_srl(cpu, &cpu->registers.a); }
int cb_srl_b(struct CPU * cpu) { return gcb_srl(cpu, &cpu->registers.b); }
int cb_srl_c(struct CPU * cpu) { return gcb_srl(cpu, &cpu->registers.c); }
int cb_srl_d(struct CPU * cpu) { return gcb_srl(cpu, &cpu->registers.d); }
int cb_srl_e(struct CPU * cpu) { return gcb_srl(cpu, &cpu->registers.e); }
int cb_srl_h(struct CPU * cpu) { return gcb_srl(cpu, &cpu->registers.h); }
int cb_srl_l(struct CPU * cpu) { return gcb_srl(cpu, &cpu->registers.l); }


/*
 * cb_swap_*:
 * Swap the two nibbles of value.
 *
 * Zero: Set if value == 0
 * Carry, Substract and Half-carry: Unset
 */
static inline int gcb_swap(struct CPU * cpu, uint8_t * value) {
    FLAG_CLEARIF(*value, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_C);

    (*value) = (((*value) & 0x0F) << 4) | (((*value) & 0xF0) >> 4);
    return 2;
}

int cb_swap_a(struct CPU * cpu) { return gcb_swap(cpu, &cpu->registers.a); }
int cb_swap_b(struct CPU * cpu) { return gcb_swap(cpu, &cpu->registers.b); }
int cb_swap_c(struct CPU * cpu) { return gcb_swap(cpu, &cpu->registers.c); }
int cb_swap_d(struct CPU * cpu) { return gcb_swap(cpu, &cpu->registers.d); }
int cb_swap_e(struct CPU * cpu) { return gcb_swap(cpu, &cpu->registers.e); }
int cb_swap_h(struct CPU * cpu) { return gcb_swap(cpu, &cpu->registers.h); }
int cb_swap_l(struct CPU * cpu) { return gcb_swap(cpu, &cpu->registers.l); }

/*
 * cb_bit_*_*:
 * Tests bit in value
 * 
 * Zero: Set if the `bit`th bit in value is unset
 * Substract and Half-carry: Unset
 * Carry: Untouched
 */
static inline int gcb_bit(struct CPU * cpu, uint8_t value, uint8_t bit) {
    FLAG_CLEARIF(value & (1 << bit), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_SET(cpu->registers.f, CPU_FLAG_H);
    return 2;
}

static inline int gcb_bit_hl(struct CPU * cpu, uint8_t bit) {
    gcb_bit(cpu, read_byte(cpu, cpu->registers.hl), bit);
    return 3;
}

int cb_bit_0_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 0); }
int cb_bit_0_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 0); }
int cb_bit_0_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 0); }
int cb_bit_0_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 0); }
int cb_bit_0_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 0); }
int cb_bit_0_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 0); }
int cb_bit_0_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 0); }
int cb_bit_0_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 0); }
int cb_bit_1_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 1); }
int cb_bit_1_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 1); }
int cb_bit_1_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 1); }
int cb_bit_1_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 1); }
int cb_bit_1_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 1); }
int cb_bit_1_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 1); }
int cb_bit_1_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 1); }
int cb_bit_1_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 1); }
int cb_bit_2_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 2); }
int cb_bit_2_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 2); }
int cb_bit_2_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 2); }
int cb_bit_2_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 2); }
int cb_bit_2_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 2); }
int cb_bit_2_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 2); }
int cb_bit_2_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 2); }
int cb_bit_2_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 2); }
int cb_bit_3_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 3); }
int cb_bit_3_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 3); }
int cb_bit_3_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 3); }
int cb_bit_3_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 3); }
int cb_bit_3_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 3); }
int cb_bit_3_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 3); }
int cb_bit_3_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 3); }
int cb_bit_3_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 3); }
int cb_bit_4_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 4); }
int cb_bit_4_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 4); }
int cb_bit_4_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 4); }
int cb_bit_4_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 4); }
int cb_bit_4_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 4); }
int cb_bit_4_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 4); }
int cb_bit_4_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 4); }
int cb_bit_4_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 4); }
int cb_bit_5_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 5); }
int cb_bit_5_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 5); }
int cb_bit_5_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 5); }
int cb_bit_5_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 5); }
int cb_bit_5_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 5); }
int cb_bit_5_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 5); }
int cb_bit_5_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 5); }
int cb_bit_5_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 5); }
int cb_bit_6_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 6); }
int cb_bit_6_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 6); }
int cb_bit_6_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 6); }
int cb_bit_6_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 6); }
int cb_bit_6_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 6); }
int cb_bit_6_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 6); }
int cb_bit_6_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 6); }
int cb_bit_6_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 6); }
int cb_bit_7_b(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.b, 7); }
int cb_bit_7_c(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.c, 7); }
int cb_bit_7_d(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.d, 7); }
int cb_bit_7_e(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.e, 7); }
int cb_bit_7_h(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.h, 7); }
int cb_bit_7_l(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.l, 7); }
int cb_bit_7_hl(struct CPU * cpu){ return gcb_bit_hl(cpu, 7); }
int cb_bit_7_a(struct CPU * cpu) { return gcb_bit(cpu, cpu->registers.a, 7); }

/*
 * cb_res_*_*:
 * Sets the `bit`th bit in value to 0
 * 
 * All flags are untouched.
 */
static inline int gcb_res(struct CPU * cpu, uint8_t * value, uint8_t bit) {
    (*value) &= ~(1 << bit);
    return 2;
}

static inline int gcb_res_hl(struct CPU * cpu, uint8_t bit) {
    uint8_t value = read_byte(cpu, cpu->registers.hl) & ~(1 << bit);
    write_byte(cpu, cpu->registers.hl, value);
    return 3;
}

int cb_res_0_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 0); }
int cb_res_0_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 0); }
int cb_res_0_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 0); }
int cb_res_0_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 0); }
int cb_res_0_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 0); }
int cb_res_0_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 0); }
int cb_res_0_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 0); }
int cb_res_0_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 0); }
int cb_res_1_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 1); }
int cb_res_1_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 1); }
int cb_res_1_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 1); }
int cb_res_1_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 1); }
int cb_res_1_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 1); }
int cb_res_1_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 1); }
int cb_res_1_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 1); }
int cb_res_1_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 1); }
int cb_res_2_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 2); }
int cb_res_2_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 2); }
int cb_res_2_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 2); }
int cb_res_2_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 2); }
int cb_res_2_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 2); }
int cb_res_2_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 2); }
int cb_res_2_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 2); }
int cb_res_2_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 2); }
int cb_res_3_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 3); }
int cb_res_3_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 3); }
int cb_res_3_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 3); }
int cb_res_3_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 3); }
int cb_res_3_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 3); }
int cb_res_3_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 3); }
int cb_res_3_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 3); }
int cb_res_3_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 3); }
int cb_res_4_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 4); }
int cb_res_4_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 4); }
int cb_res_4_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 4); }
int cb_res_4_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 4); }
int cb_res_4_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 4); }
int cb_res_4_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 4); }
int cb_res_4_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 4); }
int cb_res_4_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 4); }
int cb_res_5_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 5); }
int cb_res_5_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 5); }
int cb_res_5_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 5); }
int cb_res_5_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 5); }
int cb_res_5_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 5); }
int cb_res_5_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 5); }
int cb_res_5_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 5); }
int cb_res_5_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 5); }
int cb_res_6_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 6); }
int cb_res_6_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 6); }
int cb_res_6_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 6); }
int cb_res_6_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 6); }
int cb_res_6_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 6); }
int cb_res_6_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 6); }
int cb_res_6_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 6); }
int cb_res_6_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 6); }
int cb_res_7_b(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.b, 7); }
int cb_res_7_c(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.c, 7); }
int cb_res_7_d(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.d, 7); }
int cb_res_7_e(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.e, 7); }
int cb_res_7_h(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.h, 7); }
int cb_res_7_l(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.l, 7); }
int cb_res_7_hl(struct CPU * cpu){ return gcb_res_hl(cpu, 7); }
int cb_res_7_a(struct CPU * cpu) { return gcb_res(cpu, &cpu->registers.a, 7); }

/*
 * cb_set_*_*:
 * Sets the `bit`th bit of value to 1
 *
 * All flags are untouched.
 */
static inline int gcb_set(struct CPU * cpu, uint8_t * value, uint8_t bit) {
    (*value) &= ~(1 << bit);
    return 2;
}

static inline int gcb_set_hl(struct CPU * cpu, uint8_t bit) {
    uint8_t value = read_byte(cpu, cpu->registers.hl) & ~(1 << bit);
    write_byte(cpu, cpu->registers.hl, value);
    return 3;
}

int cb_set_0_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 0); }
int cb_set_0_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 0); }
int cb_set_0_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 0); }
int cb_set_0_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 0); }
int cb_set_0_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 0); }
int cb_set_0_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 0); }
int cb_set_0_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 0); }
int cb_set_0_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 0); }
int cb_set_1_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 1); }
int cb_set_1_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 1); }
int cb_set_1_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 1); }
int cb_set_1_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 1); }
int cb_set_1_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 1); }
int cb_set_1_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 1); }
int cb_set_1_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 1); }
int cb_set_1_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 1); }
int cb_set_2_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 2); }
int cb_set_2_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 2); }
int cb_set_2_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 2); }
int cb_set_2_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 2); }
int cb_set_2_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 2); }
int cb_set_2_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 2); }
int cb_set_2_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 2); }
int cb_set_2_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 2); }
int cb_set_3_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 3); }
int cb_set_3_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 3); }
int cb_set_3_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 3); }
int cb_set_3_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 3); }
int cb_set_3_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 3); }
int cb_set_3_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 3); }
int cb_set_3_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 3); }
int cb_set_3_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 3); }
int cb_set_4_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 4); }
int cb_set_4_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 4); }
int cb_set_4_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 4); }
int cb_set_4_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 4); }
int cb_set_4_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 4); }
int cb_set_4_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 4); }
int cb_set_4_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 4); }
int cb_set_4_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 4); }
int cb_set_5_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 5); }
int cb_set_5_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 5); }
int cb_set_5_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 5); }
int cb_set_5_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 5); }
int cb_set_5_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 5); }
int cb_set_5_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 5); }
int cb_set_5_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 5); }
int cb_set_5_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 5); }
int cb_set_6_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 6); }
int cb_set_6_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 6); }
int cb_set_6_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 6); }
int cb_set_6_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 6); }
int cb_set_6_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 6); }
int cb_set_6_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 6); }
int cb_set_6_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 6); }
int cb_set_6_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 6); }
int cb_set_7_b(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.b, 7); }
int cb_set_7_c(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.c, 7); }
int cb_set_7_d(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.d, 7); }
int cb_set_7_e(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.e, 7); }
int cb_set_7_h(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.h, 7); }
int cb_set_7_l(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.l, 7); }
int cb_set_7_hl(struct CPU * cpu){ return gcb_set_hl(cpu, 7); }
int cb_set_7_a(struct CPU * cpu) { return gcb_set(cpu, &cpu->registers.a, 7); }

/*
 * cb_rr_*:
 * Rotates value right through carry.
 *
 * Carry: old bit 1
 * Zero: Set if value == 0 after operation
 * Substract and Half-carry: Unset
 */
static inline int g_rr(struct CPU * cpu, uint8_t * value) {
    int carry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF((*value) & 0x01, cpu->registers.f, CPU_FLAG_C);
    
    (*value) = ((*value) >> 1) | (carry << 7);
    
    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    
    return 2;
}

int cb_rr_a(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.a); }
int cb_rr_b(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.b); }
int cb_rr_c(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.c); }
int cb_rr_d(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.d); }
int cb_rr_e(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.e); }
int cb_rr_h(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.h); }
int cb_rr_l(struct CPU * cpu) { return g_rr(cpu, &cpu->registers.l); }

/*
 * cb_rrc_*:
 * Rotates value right.
 *
 * Carry: Old bit 0
 * Zero: Set if value == 0 after the operation
 * Substract Half-carry: Unset
 */
static inline int g_rrc(struct CPU * cpu, uint8_t * value) {
    (*value) = ((*value) >> 1) | ((*value) << 7);

    FLAG_CLEARIF(*value, cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((*value) & 0x80, cpu->registers.f, CPU_FLAG_C);

    return 2;
}

int cb_rrc_a(struct CPU * cpu) { return g_rrc(cpu, &cpu->registers.a); }
int cb_rrc_b(struct CPU * cpu) { return g_rrc(cpu, &cpu->registers.b); }
int cb_rrc_c(struct CPU * cpu) { return g_rrc(cpu, &cpu->registers.c); }
int cb_rrc_d(struct CPU * cpu) { return g_rrc(cpu, &cpu->registers.d); }
int cb_rrc_e(struct CPU * cpu) { return g_rrc(cpu, &cpu->registers.e); }
int cb_rrc_h(struct CPU * cpu) { return g_rrc(cpu, &cpu->registers.h); }
int cb_rrc_l(struct CPU * cpu) { return g_rrc(cpu, &cpu->registers.l); }

/*
 * cb_rl_*:
 * Rotates value left through carry
 *
 * Carry: Old bit 7
 * Zero: Set if value == 0 after the operation
 * Substract and Half-carry: Unset
 */
static inline int g_rl(struct CPU * cpu, uint8_t * value) {
    uint8_t ocarry = (cpu->registers.f & CPU_FLAG_C) != 0;
    FLAG_SETIF((*value) & 0x80, cpu->registers.f, CPU_FLAG_C);
    
    (*value) = ((*value) << 1) | ocarry;
    
    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    
    return 2;
}

int cb_rl_a(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.a); }
int cb_rl_b(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.b); }
int cb_rl_c(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.c); }
int cb_rl_d(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.d); }
int cb_rl_e(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.e); }
int cb_rl_h(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.h); }
int cb_rl_l(struct CPU * cpu) { return g_rl(cpu, &cpu->registers.l); }

/*
 * cb_rlc_*:
 * Rotates value left.
 * 
 * Carry: Old bit 7.
 * Zero: Set if value == 0 after the operation
 * Substract and Half-carry: Unset
 */
static inline int g_rlc(struct CPU * cpu, uint8_t * value) {
    (*value) = ((*value) << 1) | ((*value) >> 7);
    
    FLAG_CLEARIF((*value), cpu->registers.f, CPU_FLAG_Z);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_N);
    FLAG_UNSET(cpu->registers.f, CPU_FLAG_H);
    FLAG_SETIF((*value) & 1, cpu->registers.f, CPU_FLAG_C);

    return 2;
}

int cb_rlc_a(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.a); }
int cb_rlc_b(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.b); }
int cb_rlc_c(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.c); }
int cb_rlc_d(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.d); }
int cb_rlc_e(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.e); }
int cb_rlc_h(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.h); }
int cb_rlc_l(struct CPU * cpu) { return g_rlc(cpu, &cpu->registers.l); }

static struct Instruction cb_instructions[] = {
    {"RLC B",      0, cb_rlc_b},  // 0x0X
    {"RLC C",      0, cb_rlc_c},
    {"RLC D",      0, cb_rlc_d},
    {"RLC E",      0, cb_rlc_e},
    {"RLC H",      0, cb_rlc_h},
    {"RLC L",      0, cb_rlc_l},
    {"RLC (HL)",   0, NULL},
    {"RLC A",      0, cb_rlc_a},
    {"RRC B",      0, cb_rrc_b},
    {"RRC C",      0, cb_rrc_c},
    {"RRC D",      0, cb_rrc_d},
    {"RRC E",      0, cb_rrc_e},
    {"RRC H",      0, cb_rrc_h},
    {"RRC L",      0, cb_rrc_l},
    {"RRC (HL)",   0, NULL},
    {"RRC A",      0, cb_rrc_a},
    {"RL B",       0, cb_rl_b},  // 0x1X
    {"RL C",       0, cb_rl_c},
    {"RL D",       0, cb_rl_d},
    {"RL E",       0, cb_rl_e},
    {"RL H",       0, cb_rl_h},
    {"RL L",       0, cb_rl_l},
    {"RL (HL) ",   0, NULL},
    {"RL A",       0, cb_rl_a},
    {"RR B",       0, cb_rr_b},
    {"RR C",       0, cb_rr_c},
    {"RR D",       0, cb_rr_d},
    {"RR E",       0, cb_rr_e},
    {"RR H",       0, cb_rr_h},
    {"RR L",       0, cb_rr_l},
    {"RR (HL) ",   0, NULL},
    {"RR A",       0, cb_rr_a},
    {"SLA B",      0, cb_sla_b},  // 0x2X
    {"SLA C",      0, cb_sla_c},
    {"SLA D",      0, cb_sla_d},
    {"SLA E",      0, cb_sla_e},
    {"SLA H",      0, cb_sla_h},
    {"SLA L",      0, cb_sla_l},
    {"SLA (HL)",   0, NULL},
    {"SLA A",      0, cb_sla_a},
    {"SRA B",      0, cb_sra_b},
    {"SRA C",      0, cb_sra_c},
    {"SRA D",      0, cb_sra_d},
    {"SRA E",      0, cb_sra_e},
    {"SRA H",      0, cb_sra_h},
    {"SRA L",      0, cb_sra_l},
    {"SRA (HL)",   0, NULL},
    {"SRA A",      0, cb_sra_a},
    {"SWAP B",     0, cb_swap_b},  // 0x3X
    {"SWAP C",     0, cb_swap_c},
    {"SWAP D",     0, cb_swap_d},
    {"SWAP E",     0, cb_swap_e},
    {"SWAP H",     0, cb_swap_h},
    {"SWAP L",     0, cb_swap_l},
    {"SWAP (HL)",  0, NULL},
    {"SWAP A",     0, cb_swap_a},
    {"SRL B",      0, cb_srl_b},
    {"SRL C",      0, cb_srl_c},
    {"SRL D",      0, cb_srl_d},
    {"SRL E",      0, cb_srl_e},
    {"SRL H",      0, cb_srl_h},
    {"SRL L",      0, cb_srl_l},
    {"SRL (HL)",   0, NULL},
    {"SRL A",      0, cb_srl_a},
    {"BIT 0, B",   0, cb_bit_0_b},  // 0x4X
    {"BIT 0, C",   0, cb_bit_0_c},
    {"BIT 0, D",   0, cb_bit_0_d},
    {"BIT 0, E",   0, cb_bit_0_e},
    {"BIT 0, H",   0, cb_bit_0_h},
    {"BIT 0, L",   0, cb_bit_0_l},
    {"BIT 0, (HL)",0, cb_bit_0_hl},
    {"BIT 0, A",   0, cb_bit_0_a},
    {"BIT 1, B",   0, cb_bit_1_b},
    {"BIT 1, C",   0, cb_bit_1_c},
    {"BIT 1, D",   0, cb_bit_1_d},
    {"BIT 1, E",   0, cb_bit_1_e},
    {"BIT 1, H",   0, cb_bit_1_h},
    {"BIT 1, L",   0, cb_bit_1_l},
    {"BIT 1, (HL)",0, cb_bit_1_hl},
    {"BIT 1, A",   0, cb_bit_1_a},
    {"BIT 2, B",   0, cb_bit_2_b},  // 0x5X
    {"BIT 2, C",   0, cb_bit_2_c},
    {"BIT 2, D",   0, cb_bit_2_d},
    {"BIT 2, E",   0, cb_bit_2_e},
    {"BIT 2, H",   0, cb_bit_2_h},
    {"BIT 2, L",   0, cb_bit_2_l},
    {"BIT 2, (HL)",0, cb_bit_2_hl},
    {"BIT 2, A",   0, cb_bit_2_a},
    {"BIT 3, B",   0, cb_bit_3_b},
    {"BIT 3, C",   0, cb_bit_3_c},
    {"BIT 3, D",   0, cb_bit_3_d},
    {"BIT 3, E",   0, cb_bit_3_e},
    {"BIT 3, H",   0, cb_bit_3_h},
    {"BIT 3, L",   0, cb_bit_3_l},
    {"BIT 3, (HL)",0, cb_bit_3_hl},
    {"BIT 3, A",   0, cb_bit_3_a},
    {"BIT 4, B",   0, cb_bit_4_b},  // 0x6X
    {"BIT 4, C",   0, cb_bit_4_c},
    {"BIT 4, D",   0, cb_bit_4_d},
    {"BIT 4, E",   0, cb_bit_4_e},
    {"BIT 4, H",   0, cb_bit_4_h},
    {"BIT 4, L",   0, cb_bit_4_l},
    {"BIT 4, (HL)",0, cb_bit_4_hl},
    {"BIT 4, A",   0, cb_bit_4_a},
    {"BIT 5, B",   0, cb_bit_5_b},
    {"BIT 5, C",   0, cb_bit_5_c},
    {"BIT 5, D",   0, cb_bit_5_d},
    {"BIT 5, E",   0, cb_bit_5_e},
    {"BIT 5, H",   0, cb_bit_5_h},
    {"BIT 5, L",   0, cb_bit_5_l},
    {"BIT 5, (HL)",0, cb_bit_5_hl},
    {"BIT 5, A",   0, cb_bit_5_a},
    {"BIT 6, B",   0, cb_bit_6_b},  // 0x7X
    {"BIT 6, C",   0, cb_bit_6_c},
    {"BIT 6, D",   0, cb_bit_6_d},
    {"BIT 6, E",   0, cb_bit_6_e},
    {"BIT 6, H",   0, cb_bit_6_h},
    {"BIT 6, L",   0, cb_bit_6_l},
    {"BIT 6, (HL)",0, cb_bit_6_hl},
    {"BIT 6, A",   0, cb_bit_6_a},
    {"BIT 7, B",   0, cb_bit_7_b},
    {"BIT 7, C",   0, cb_bit_7_c},
    {"BIT 7, D",   0, cb_bit_7_d},
    {"BIT 7, E",   0, cb_bit_7_e},
    {"BIT 7, H",   0, cb_bit_7_h},
    {"BIT 7, L",   0, cb_bit_7_l},
    {"BIT 7, (HL)",0, cb_bit_7_hl},
    {"BIT 7, A",   0, cb_bit_7_a},
    {"RES 0, B",   0, cb_res_0_b},  // 0x8X
    {"RES 0, C",   0, cb_res_0_c},
    {"RES 0, D",   0, cb_res_0_d},
    {"RES 0, E",   0, cb_res_0_e},
    {"RES 0, H",   0, cb_res_0_h},
    {"RES 0, L",   0, cb_res_0_l},
    {"RES 0, (HL)",0, cb_res_0_hl},
    {"RES 0, A",   0, cb_res_0_a},
    {"RES 1, B",   0, cb_res_1_b},
    {"RES 1, C",   0, cb_res_1_c},
    {"RES 1, D",   0, cb_res_1_d},
    {"RES 1, E",   0, cb_res_1_e},
    {"RES 1, H",   0, cb_res_1_h},
    {"RES 1, L",   0, cb_res_1_l},
    {"RES 1, (HL)",0, cb_res_1_hl},
    {"RES 1, A",   0, cb_res_1_a},
    {"RES 2, B",   0, cb_res_2_b},  // 0x9X
    {"RES 2, C",   0, cb_res_2_c},
    {"RES 2, D",   0, cb_res_2_d},
    {"RES 2, E",   0, cb_res_2_e},
    {"RES 2, H",   0, cb_res_2_h},
    {"RES 2, L",   0, cb_res_2_l},
    {"RES 2, (HL)",0, cb_res_2_hl},
    {"RES 2, A",   0, cb_res_2_a},
    {"RES 3, B",   0, cb_res_3_b},
    {"RES 3, C",   0, cb_res_3_c},
    {"RES 3, D",   0, cb_res_3_d},
    {"RES 3, E",   0, cb_res_3_e},
    {"RES 3, H",   0, cb_res_3_h},
    {"RES 3, L",   0, cb_res_3_l},
    {"RES 3, (HL)",0, cb_res_3_hl},
    {"RES 3, A",   0, cb_res_3_a},
    {"RES 4, B",   0, cb_res_4_b},  // 0xAX
    {"RES 4, C",   0, cb_res_4_c},
    {"RES 4, D",   0, cb_res_4_d},
    {"RES 4, E",   0, cb_res_4_e},
    {"RES 4, H",   0, cb_res_4_h},
    {"RES 4, L",   0, cb_res_4_l},
    {"RES 4, (HL)",0, cb_res_4_hl},
    {"RES 4, A",   0, cb_res_4_a},
    {"RES 5, B",   0, cb_res_5_b},
    {"RES 5, C",   0, cb_res_5_c},
    {"RES 5, D",   0, cb_res_5_d},
    {"RES 5, E",   0, cb_res_5_e},
    {"RES 5, H",   0, cb_res_5_h},
    {"RES 5, L",   0, cb_res_5_l},
    {"RES 5, (HL)",0, cb_res_5_hl},
    {"RES 5, A",   0, cb_res_5_a},
    {"RES 6, B",   0, cb_res_6_b},  // 0xBX
    {"RES 6, C",   0, cb_res_6_c},
    {"RES 6, D",   0, cb_res_6_d},
    {"RES 6, E",   0, cb_res_6_e},
    {"RES 6, H",   0, cb_res_6_h},
    {"RES 6, L",   0, cb_res_6_l},
    {"RES 6, (HL)",0, cb_res_6_hl},
    {"RES 6, A",   0, cb_res_6_a},
    {"RES 7, B",   0, cb_res_7_b},
    {"RES 7, C",   0, cb_res_7_c},
    {"RES 7, D",   0, cb_res_7_d},
    {"RES 7, E",   0, cb_res_7_e},
    {"RES 7, H",   0, cb_res_7_h},
    {"RES 7, L",   0, cb_res_7_l},
    {"RES 7, (HL)",0, cb_res_7_hl},
    {"RES 7, A",   0, cb_res_7_a},
    {"SET 0, B",   0, cb_set_0_b},  // 0xCX
    {"SET 0, C",   0, cb_set_0_c},
    {"SET 0, D",   0, cb_set_0_d},
    {"SET 0, E",   0, cb_set_0_e},
    {"SET 0, H",   0, cb_set_0_h},
    {"SET 0, L",   0, cb_set_0_l},
    {"SET 0, (HL)",0, cb_set_0_hl},
    {"SET 0, A",   0, cb_set_0_a},
    {"SET 1, B",   0, cb_set_1_b},
    {"SET 1, C",   0, cb_set_1_c},
    {"SET 1, D",   0, cb_set_1_d},
    {"SET 1, E",   0, cb_set_1_e},
    {"SET 1, H",   0, cb_set_1_h},
    {"SET 1, L",   0, cb_set_1_l},
    {"SET 1, (HL)",0, cb_set_1_hl},
    {"SET 1, A",   0, cb_set_1_a},
    {"SET 2, B",   0, cb_set_2_b},  // 0xDX
    {"SET 2, C",   0, cb_set_2_c},
    {"SET 2, D",   0, cb_set_2_d},
    {"SET 2, E",   0, cb_set_2_e},
    {"SET 2, H",   0, cb_set_2_h},
    {"SET 2, L",   0, cb_set_2_l},
    {"SET 2, (HL)",0, cb_set_2_hl},
    {"SET 2, A",   0, cb_set_2_a},
    {"SET 3, B",   0, cb_set_3_b},
    {"SET 3, C",   0, cb_set_3_c},
    {"SET 3, D",   0, cb_set_3_d},
    {"SET 3, E",   0, cb_set_3_e},
    {"SET 3, H",   0, cb_set_3_h},
    {"SET 3, L",   0, cb_set_3_l},
    {"SET 3, (HL)",0, cb_set_3_hl},
    {"SET 3, A",   0, cb_set_3_a},
    {"SET 4, B",   0, cb_set_4_b},  // 0xEX
    {"SET 4, C",   0, cb_set_4_c},
    {"SET 4, D",   0, cb_set_4_d},
    {"SET 4, E",   0, cb_set_4_e},
    {"SET 4, H",   0, cb_set_4_h},
    {"SET 4, L",   0, cb_set_4_l},
    {"SET 4, (HL)",0, cb_set_4_hl},
    {"SET 4, A",   0, cb_set_4_a},
    {"SET 5, B",   0, cb_set_5_b},
    {"SET 5, C",   0, cb_set_5_c},
    {"SET 5, D",   0, cb_set_5_d},
    {"SET 5, E",   0, cb_set_5_e},
    {"SET 5, H",   0, cb_set_5_h},
    {"SET 5, L",   0, cb_set_5_l},
    {"SET 5, (HL)",0, cb_set_5_hl},
    {"SET 5, A",   0, cb_set_5_a},
    {"SET 6, B",   0, cb_set_6_b},  // 0xFX
    {"SET 6, C",   0, cb_set_6_c},
    {"SET 6, D",   0, cb_set_6_d},
    {"SET 6, E",   0, cb_set_6_e},
    {"SET 6, H",   0, cb_set_6_h},
    {"SET 6, L",   0, cb_set_6_l},
    {"SET 6, (HL)",0, cb_set_6_hl},
    {"SET 6, A",   0, cb_set_6_a},
    {"SET 7, B",   0, cb_set_7_b},
    {"SET 7, C",   0, cb_set_7_c},
    {"SET 7, D",   0, cb_set_7_d},
    {"SET 7, E",   0, cb_set_7_e},
    {"SET 7, H",   0, cb_set_7_h},
    {"SET 7, L",   0, cb_set_7_l},
    {"SET 7, (HL)",0, cb_set_7_hl},
    {"SET 7, A",   0, cb_set_7_a},
};

/*
 * cb_prefix:
 * Executes a cb instruction
 * 
 * @operation: The instruction to execute
 */
int cb_prefix(struct CPU * cpu, uint8_t operation) {
    struct Instruction instruction = cb_instructions[operation];

    if (instruction.function) {
	return ((int (*)(struct CPU *))instruction.function)(cpu);
    } else {
	log_debug("CB instruction not implemented : %s", instruction.disasm);
	sleep(5);
	return 0;
    }
}
