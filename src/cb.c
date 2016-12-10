/* cb.c --- 
 * 
 * Filename: cb.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 22:40:29 2016 (+0100)
 * Last-Updated: Sat Dec 10 23:35:27 2016 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "cpu.h"
#include "logger.h"
#include "instruction.h"
#include "memory.h"

/* RESs */
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

static struct Instruction cb_instructions[] = {
    {"RLC B",      0, NULL},  // 0x0X
    {"RLC C",      0, NULL},
    {"RLC D",      0, NULL},
    {"RLC E",      0, NULL},
    {"RLC H",      0, NULL},
    {"RLC L",      0, NULL},
    {"RLC (HL)",   0, NULL},
    {"RLC A",      0, NULL},
    {"RRC B",      0, NULL},
    {"RRC C",      0, NULL},
    {"RRC D",      0, NULL},
    {"RRC E",      0, NULL},
    {"RRC H",      0, NULL},
    {"RRC L",      0, NULL},
    {"RRC (HL)",   0, NULL},
    {"RRC A",      0, NULL},
    {"RL B",       0, NULL},  // 0x1X
    {"RL C",       0, NULL},
    {"RL D",       0, NULL},
    {"RL E",       0, NULL},
    {"RL H",       0, NULL},
    {"RL L",       0, NULL},
    {"RL (HL) ",   0, NULL},
    {"RL A",       0, NULL},
    {"RR B",       0, NULL},
    {"RR C",       0, NULL},
    {"RR D",       0, NULL},
    {"RR E",       0, NULL},
    {"RR H",       0, NULL},
    {"RR L",       0, NULL},
    {"RR (HL) ",   0, NULL},
    {"RR A",       0, NULL},
    {"SLA B",      0, NULL},  // 0x2X
    {"SLA C",      0, NULL},
    {"SLA D",      0, NULL},
    {"SLA E",      0, NULL},
    {"SLA H",      0, NULL},
    {"SLA L",      0, NULL},
    {"SLA (HL)",   0, NULL},
    {"SLA A",      0, NULL},
    {"SRA B",      0, NULL},
    {"SRA C",      0, NULL},
    {"SRA D",      0, NULL},
    {"SRA E",      0, NULL},
    {"SRA H",      0, NULL},
    {"SRA L",      0, NULL},
    {"SRA (HL)",   0, NULL},
    {"SRA A",      0, NULL},
    {"SWAP B",     0, NULL},  // 0x3X
    {"SWAP C",     0, NULL},
    {"SWAP D",     0, NULL},
    {"SWAP E",     0, NULL},
    {"SWAP H",     0, NULL},
    {"SWAP L",     0, NULL},
    {"SWAP (HL)",  0, NULL},
    {"SWAP A",     0, NULL},
    {"SRL B",      0, NULL},
    {"SRL C",      0, NULL},
    {"SRL D",      0, NULL},
    {"SRL E",      0, NULL},
    {"SRL H",      0, NULL},
    {"SRL L",      0, NULL},
    {"SRL (HL)",   0, NULL},
    {"SRL A",      0, NULL},
    {"BIT 0, B",   0, NULL},  // 0x4X
    {"BIT 0, C",   0, NULL},
    {"BIT 0, D",   0, NULL},
    {"BIT 0, E",   0, NULL},
    {"BIT 0, H",   0, NULL},
    {"BIT 0, L",   0, NULL},
    {"BIT 0, (HL)",0, NULL},
    {"BIT 0, A",   0, NULL},
    {"BIT 1, B",   0, NULL},
    {"BIT 1, C",   0, NULL},
    {"BIT 1, D",   0, NULL},
    {"BIT 1, E",   0, NULL},
    {"BIT 1, H",   0, NULL},
    {"BIT 1, L",   0, NULL},
    {"BIT 1, (HL)",0, NULL},
    {"BIT 1, A",   0, NULL},
    {"BIT 2, B",   0, NULL},  // 0x5X
    {"BIT 2, C",   0, NULL},
    {"BIT 2, D",   0, NULL},
    {"BIT 2, E",   0, NULL},
    {"BIT 2, H",   0, NULL},
    {"BIT 2, L",   0, NULL},
    {"BIT 2, (HL)",0, NULL},
    {"BIT 2, A",   0, NULL},
    {"BIT 3, B",   0, NULL},
    {"BIT 3, C",   0, NULL},
    {"BIT 3, D",   0, NULL},
    {"BIT 3, E",   0, NULL},
    {"BIT 3, H",   0, NULL},
    {"BIT 3, L",   0, NULL},
    {"BIT 3, (HL)",0, NULL},
    {"BIT 3, A",   0, NULL},
    {"BIT 4, B",   0, NULL},  // 0x6X
    {"BIT 4, C",   0, NULL},
    {"BIT 4, D",   0, NULL},
    {"BIT 4, E",   0, NULL},
    {"BIT 4, H",   0, NULL},
    {"BIT 4, L",   0, NULL},
    {"BIT 4, (HL)",0, NULL},
    {"BIT 4, A",   0, NULL},
    {"BIT 5, B",   0, NULL},
    {"BIT 5, C",   0, NULL},
    {"BIT 5, D",   0, NULL},
    {"BIT 5, E",   0, NULL},
    {"BIT 5, H",   0, NULL},
    {"BIT 5, L",   0, NULL},
    {"BIT 5, (HL)",0, NULL},
    {"BIT 5, A",   0, NULL},
    {"BIT 6, B",   0, NULL},  // 0x7X
    {"BIT 6, C",   0, NULL},
    {"BIT 6, D",   0, NULL},
    {"BIT 6, E",   0, NULL},
    {"BIT 6, H",   0, NULL},
    {"BIT 6, L",   0, NULL},
    {"BIT 6, (HL)",0, NULL},
    {"BIT 6, A",   0, NULL},
    {"BIT 7, B",   0, NULL},
    {"BIT 7, C",   0, NULL},
    {"BIT 7, D",   0, NULL},
    {"BIT 7, E",   0, NULL},
    {"BIT 7, H",   0, NULL},
    {"BIT 7, L",   0, NULL},
    {"BIT 7, (HL)",0, NULL},
    {"BIT 7, A",   0, NULL},
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
    {"SET 0, B",   0, NULL},  // 0xCX
    {"SET 0, C",   0, NULL},
    {"SET 0, D",   0, NULL},
    {"SET 0, E",   0, NULL},
    {"SET 0, H",   0, NULL},
    {"SET 0, L",   0, NULL},
    {"SET 0, (HL)",0, NULL},
    {"SET 0, A",   0, NULL},
    {"SET 1, B",   0, NULL},
    {"SET 1, C",   0, NULL},
    {"SET 1, D",   0, NULL},
    {"SET 1, E",   0, NULL},
    {"SET 1, H",   0, NULL},
    {"SET 1, L",   0, NULL},
    {"SET 1, (HL)",0, NULL},
    {"SET 1, A",   0, NULL},
    {"SET 2, B",   0, NULL},  // 0xDX
    {"SET 2, C",   0, NULL},
    {"SET 2, D",   0, NULL},
    {"SET 2, E",   0, NULL},
    {"SET 2, H",   0, NULL},
    {"SET 2, L",   0, NULL},
    {"SET 2, (HL)",0, NULL},
    {"SET 2, A",   0, NULL},
    {"SET 3, B",   0, NULL},
    {"SET 3, C",   0, NULL},
    {"SET 3, D",   0, NULL},
    {"SET 3, E",   0, NULL},
    {"SET 3, H",   0, NULL},
    {"SET 3, L",   0, NULL},
    {"SET 3, (HL)",0, NULL},
    {"SET 3, A",   0, NULL},
    {"SET 4, B",   0, NULL},  // 0xEX
    {"SET 4, C",   0, NULL},
    {"SET 4, D",   0, NULL},
    {"SET 4, E",   0, NULL},
    {"SET 4, H",   0, NULL},
    {"SET 4, L",   0, NULL},
    {"SET 4, (HL)",0, NULL},
    {"SET 4, A",   0, NULL},
    {"SET 5, B",   0, NULL},
    {"SET 5, C",   0, NULL},
    {"SET 5, D",   0, NULL},
    {"SET 5, E",   0, NULL},
    {"SET 5, H",   0, NULL},
    {"SET 5, L",   0, NULL},
    {"SET 5, (HL)",0, NULL},
    {"SET 5, A",   0, NULL},
    {"SET 6, B",   0, NULL},  // 0xFX
    {"SET 6, C",   0, NULL},
    {"SET 6, D",   0, NULL},
    {"SET 6, E",   0, NULL},
    {"SET 6, H",   0, NULL},
    {"SET 6, L",   0, NULL},
    {"SET 6, (HL)",0, NULL},
    {"SET 6, A",   0, NULL},
    {"SET 7, B",   0, NULL},
    {"SET 7, C",   0, NULL},
    {"SET 7, D",   0, NULL},
    {"SET 7, E",   0, NULL},
    {"SET 7, H",   0, NULL},
    {"SET 7, L",   0, NULL},
    {"SET 7, (HL)",0, NULL},
    {"SET 7, A",   0, NULL},
};

int cb_prefix(struct CPU * cpu, uint8_t operation) {
    struct Instruction instruction = cb_instructions[operation];

    if (instruction.function) {
	log_debug("%s", instruction.disasm);
	return ((int (*)(struct CPU *))instruction.function)(cpu);
    } else {
	log_debug("CB instruction not implemented : %s", instruction.disasm);
	sleep(5);
	return 0;
    }
}
