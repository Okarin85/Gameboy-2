/* instruction.h --- 
 * 
 * Filename: instruction.h
 * Author: Jules <archjules>
 * Created: Thu Dec  8 12:54:40 2016 (+0100)
 * Last-Updated: Sat Dec 10 23:51:38 2016 (+0100)
 *           By: Jules <archjules>
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct Instruction {
    char * disasm;
    int    operand;
    void * function;
};

int cb_prefix(struct CPU *, uint8_t);
int cpu_nop(struct CPU *);
int cpu_ei(struct CPU *);
int cpu_di(struct CPU *);

int cpu_ld_a_a(struct CPU *);
int cpu_ld_a_b(struct CPU *);
int cpu_ld_a_c(struct CPU *);
int cpu_ld_a_d(struct CPU *);
int cpu_ld_a_e(struct CPU *);
int cpu_ld_a_h(struct CPU *);
int cpu_ld_a_l(struct CPU *);
int cpu_ld_a_hl(struct CPU *);
int cpu_ld_b_a(struct CPU *);
int cpu_ld_b_b(struct CPU *);
int cpu_ld_b_c(struct CPU *);
int cpu_ld_b_d(struct CPU *);
int cpu_ld_b_e(struct CPU *);
int cpu_ld_b_h(struct CPU *);
int cpu_ld_b_l(struct CPU *);
int cpu_ld_b_hl(struct CPU *);
int cpu_ld_c_a(struct CPU *);
int cpu_ld_c_b(struct CPU *);
int cpu_ld_c_c(struct CPU *);
int cpu_ld_c_d(struct CPU *);
int cpu_ld_c_e(struct CPU *);
int cpu_ld_c_h(struct CPU *);
int cpu_ld_c_l(struct CPU *);
int cpu_ld_c_hl(struct CPU *);
int cpu_ld_d_a(struct CPU *);
int cpu_ld_d_b(struct CPU *);
int cpu_ld_d_c(struct CPU *);
int cpu_ld_d_d(struct CPU *);
int cpu_ld_d_e(struct CPU *);
int cpu_ld_d_h(struct CPU *);
int cpu_ld_d_l(struct CPU *);
int cpu_ld_d_hl(struct CPU *);
int cpu_ld_e_a(struct CPU *);
int cpu_ld_e_b(struct CPU *);
int cpu_ld_e_c(struct CPU *);
int cpu_ld_e_d(struct CPU *);
int cpu_ld_e_e(struct CPU *);
int cpu_ld_e_h(struct CPU *);
int cpu_ld_e_l(struct CPU *);
int cpu_ld_e_hl(struct CPU *);
int cpu_ld_h_a(struct CPU *);
int cpu_ld_h_b(struct CPU *);
int cpu_ld_h_c(struct CPU *);
int cpu_ld_h_d(struct CPU *);
int cpu_ld_h_e(struct CPU *);
int cpu_ld_h_h(struct CPU *);
int cpu_ld_h_l(struct CPU *);
int cpu_ld_h_hl(struct CPU *);
int cpu_ld_l_a(struct CPU *);
int cpu_ld_l_b(struct CPU *);
int cpu_ld_l_c(struct CPU *);
int cpu_ld_l_d(struct CPU *);
int cpu_ld_l_e(struct CPU *);
int cpu_ld_l_h(struct CPU *);
int cpu_ld_l_l(struct CPU *);
int cpu_ld_l_hl(struct CPU *);
int cpu_ld_d_a(struct CPU *);
int cpu_ld_d_b(struct CPU *);
int cpu_ld_d_c(struct CPU *);
int cpu_ld_d_d(struct CPU *);
int cpu_ld_d_e(struct CPU *);
int cpu_ld_d_h(struct CPU *);
int cpu_ld_d_l(struct CPU *);
int cpu_ld_d_hl(struct CPU *);
int cpu_ld_hl_a(struct CPU *);
int cpu_ld_hl_b(struct CPU *);
int cpu_ld_hl_c(struct CPU *);
int cpu_ld_hl_d(struct CPU *);
int cpu_ld_hl_e(struct CPU *);
int cpu_ld_hl_h(struct CPU *);
int cpu_ld_hl_l(struct CPU *);

int cpu_ld_n_a(struct CPU *, uint16_t);

int cpu_ldd_hl_a(struct CPU *);
int cpu_ldi_hl_a(struct CPU *);
int cpu_ldd_a_hl(struct CPU *);
int cpu_ldi_a_hl(struct CPU *);
int cpu_ldh_n_a(struct CPU *, uint8_t);
int cpu_ldh_a_n(struct CPU *, uint8_t);

int cpu_ld_a_n(struct CPU *, uint8_t);
int cpu_ld_b_n(struct CPU *, uint8_t);
int cpu_ld_c_n(struct CPU *, uint8_t);
int cpu_ld_d_n(struct CPU *, uint8_t);
int cpu_ld_e_n(struct CPU *, uint8_t);
int cpu_ld_h_n(struct CPU *, uint8_t);
int cpu_ld_l_n(struct CPU *, uint8_t);
int cpu_ld_hl_n(struct CPU *, uint8_t);

int cpu_ld_bc_nn(struct CPU *, uint16_t);
int cpu_ld_de_nn(struct CPU *, uint16_t);
int cpu_ld_hl_nn(struct CPU *, uint16_t);
int cpu_ld_sp_nn(struct CPU *, uint16_t);

int cpu_push_bc(struct CPU *);
int cpu_push_de(struct CPU *);
int cpu_push_hl(struct CPU *);
int cpu_push_af(struct CPU *);

int cpu_dec_a(struct CPU *);
int cpu_dec_b(struct CPU *);
int cpu_dec_c(struct CPU *);
int cpu_dec_d(struct CPU *);
int cpu_dec_e(struct CPU *);
int cpu_dec_h(struct CPU *);
int cpu_dec_l(struct CPU *);

int cpu_cp_a(struct CPU *);
int cpu_cp_b(struct CPU *);
int cpu_cp_c(struct CPU *);
int cpu_cp_d(struct CPU *);
int cpu_cp_e(struct CPU *);
int cpu_cp_h(struct CPU *);
int cpu_cp_l(struct CPU *);
int cpu_cp_hl(struct CPU *);
int cpu_cp_n(struct CPU *, uint8_t);

int cpu_xor_b(struct CPU *); 
int cpu_xor_c(struct CPU *); 
int cpu_xor_d(struct CPU *); 
int cpu_xor_e(struct CPU *); 
int cpu_xor_h(struct CPU *); 
int cpu_xor_l(struct CPU *); 
int cpu_xor_hl(struct CPU *); 
int cpu_xor_a(struct CPU *);

int cpu_jp(struct CPU *, uint16_t);
int cpu_jr(struct CPU *, uint8_t);

int cpu_jr_z(struct CPU *, uint8_t);
int cpu_jr_c(struct CPU *, uint8_t);
int cpu_jr_nz(struct CPU *, uint8_t);
int cpu_jr_nc(struct CPU *, uint8_t);

int cpu_call(struct CPU *, uint16_t);

static struct Instruction instructions[] = {
    {"NOP",             0, cpu_nop}, // 0x0X
    {"LD BC, 0x%04x",   2, cpu_ld_bc_nn},
    {"LD (BC), A",      0, NULL},
    {"INC BC",          0, NULL},
    {"INC B",           0, NULL},
    {"DEC B",           0, cpu_dec_b},
    {"LD B, 0x%02x",    1, cpu_ld_b_n},
    {"RLCA",            0, NULL},
    {"LD (0x%04x), SP", 2, NULL},
    {"ADD HL, BC",      0, NULL},
    {"LD A, (BC)",      0, NULL},
    {"DEC BC",          0, NULL},
    {"INC C",           0, NULL},
    {"DEC C",           0, cpu_dec_c},
    {"LD C, 0x%02x",    1, cpu_ld_c_n},
    {"RRCA",            0, NULL},
    {"STOP",            0, NULL},    // 0x1X
    {"LD DE, 0x%04x",   2, cpu_ld_de_nn},
    {"LD (DE), A",      0, NULL},
    {"INC DE",          0, NULL},
    {"INC D",           0, NULL},
    {"DEC D",           0, cpu_dec_d},
    {"LD D, 0x%02x",    1, cpu_ld_d_n},
    {"RLA",             0, NULL},
    {"JR 0x%02x",       1, cpu_jr},
    {"ADD HL, DE",      0, NULL},
    {"LD A, (DE)",      0, NULL},
    {"DEC DE",          0, NULL},
    {"INC E",           0, NULL},
    {"DEC E",           0, cpu_dec_e},
    {"LD E, 0x%02x",    1, cpu_ld_e_n},
    {"RRA",             0, NULL},
    {"JR NZ, 0x%02x",   1, cpu_jr_nz},    // 0x2X
    {"LD HL, 0x%04x",   2, cpu_ld_hl_nn},
    {"LD (HL+), A",     0, cpu_ldi_hl_a},
    {"INC HL",          0, NULL},
    {"INC H",           0, NULL},
    {"DEC H",           0, cpu_dec_h},
    {"LD H, 0x%02x",    1, cpu_ld_h_n},
    {"DAA",             0, NULL},
    {"JR Z, 0x%02x",    1, cpu_jr_z},
    {"ADD HL, HL",      0, NULL},
    {"LD A, (HL+)",     0, cpu_ldi_a_hl},
    {"DEC HL",          0, NULL},
    {"INC L",           0, NULL},
    {"DEC L",           0, cpu_dec_l},
    {"LD L, 0x%02x",    1, cpu_ld_l_n},
    {"CPL",             0, cpu_cp_a},
    {"JR NC, 0x%02x",   1, cpu_jr_nc},    // 0x3X
    {"LD SP, 0x%04x",   2, cpu_ld_sp_nn},
    {"LD (HL-), A",     0, cpu_ldd_hl_a},
    {"INC SP",          0, NULL},
    {"INC (HL)",        0, NULL},
    {"DEC (HL)",        0, NULL},
    {"LD (HL), 0x%02x", 1, cpu_ld_hl_n},
    {"SCF",             0, NULL},
    {"JR C, 0x%02x",    1, cpu_jr_c},
    {"ADD HL, SP",      0, NULL},
    {"LD A, (HL-)",     0, cpu_ldd_a_hl},
    {"DEC SP",          0, NULL},
    {"INC A",           0, NULL},
    {"DEC A",           0, cpu_dec_a},
    {"LD A, 0x%02x",    1, cpu_ld_a_n},
    {"CCF",             0, NULL},
    {"LD B, B",         0, cpu_ld_b_b},    // 0x4X
    {"LD B, C",         0, cpu_ld_b_c},
    {"LD B, D",         0, cpu_ld_b_d},
    {"LD B, E",         0, cpu_ld_b_e},
    {"LD B, H",         0, cpu_ld_b_h},
    {"LD B, L",         0, cpu_ld_b_l},
    {"LD B, (HL)",      0, cpu_ld_b_hl},
    {"LD B, A",         0, cpu_ld_b_a},
    {"LD C, B",         0, cpu_ld_c_b},
    {"LD C, C",         0, cpu_ld_c_c},
    {"LD C, D",         0, cpu_ld_c_d},
    {"LD C, E",         0, cpu_ld_c_e},
    {"LD C, H",         0, cpu_ld_c_h},
    {"LD C, L",         0, cpu_ld_c_l},
    {"LD C, (HL)",      0, cpu_ld_c_hl},
    {"LD C, A",         0, cpu_ld_c_a},
    {"LD D, B",         0, cpu_ld_d_b},    // 0x5X
    {"LD D, C",         0, cpu_ld_d_c},
    {"LD D, D",         0, cpu_ld_d_d},
    {"LD D, E",         0, cpu_ld_d_e},
    {"LD D, H",         0, cpu_ld_d_h},
    {"LD D, L",         0, cpu_ld_d_l},
    {"LD D, (HL)",      0, cpu_ld_d_hl},
    {"LD D, A",         0, cpu_ld_d_a},
    {"LD E, B",         0, cpu_ld_e_b},
    {"LD E, C",         0, cpu_ld_e_c},
    {"LD E, D",         0, cpu_ld_e_d},
    {"LD E, E",         0, cpu_ld_e_e},
    {"LD E, H",         0, cpu_ld_e_h},
    {"LD E, L",         0, cpu_ld_e_l},
    {"LD E, (HL)",      0, cpu_ld_e_hl},
    {"LD E, A",         0, cpu_ld_e_a},
    {"LD H, B",         0, cpu_ld_h_b},    // 0x6X
    {"LD H, C",         0, cpu_ld_h_c},
    {"LD H, D",         0, cpu_ld_h_d},
    {"LD H, E",         0, cpu_ld_h_e},
    {"LD H, H",         0, cpu_ld_h_h},
    {"LD H, L",         0, cpu_ld_h_l},
    {"LD H, (HL)",      0, cpu_ld_h_hl},
    {"LD H, A",         0, cpu_ld_h_a},
    {"LD L, B",         0, cpu_ld_l_b},
    {"LD L, C",         0, cpu_ld_l_c},
    {"LD L, D",         0, cpu_ld_l_d},
    {"LD L, E",         0, cpu_ld_l_e},
    {"LD L, H",         0, cpu_ld_l_h},
    {"LD L, L",         0, cpu_ld_l_l},
    {"LD L, (HL)",      0, cpu_ld_l_hl},
    {"LD L, A",         0, cpu_ld_l_a},
    {"LD (HL), B",      0, cpu_ld_hl_b},    // 0x7X
    {"LD (HL), C",      0, cpu_ld_hl_c},
    {"LD (HL), D",      0, cpu_ld_hl_d},
    {"LD (HL), E",      0, cpu_ld_hl_e},
    {"LD (HL), H",      0, cpu_ld_hl_h},
    {"LD (HL), L",      0, cpu_ld_hl_l},
    {"HALT",            0, NULL},
    {"LD (HL), A",      0, cpu_ld_hl_a},
    {"LD A, B",         0, cpu_ld_a_b},
    {"LD A, C",         0, cpu_ld_a_c},
    {"LD A, D",         0, cpu_ld_a_d},
    {"LD A, E",         0, cpu_ld_a_e},
    {"LD A, H",         0, cpu_ld_a_h},
    {"LD A, L",         0, cpu_ld_a_l},
    {"LD A, (HL)",      0, cpu_ld_a_hl},
    {"LD A, A",         0, cpu_ld_a_a},
    {"ADD A, B",        0, NULL},    // 0x8X
    {"ADD A, C",        0, NULL},
    {"ADD A, D",        0, NULL},
    {"ADD A, E",        0, NULL},
    {"ADD A, H",        0, NULL},
    {"ADD A, L",        0, NULL},
    {"ADD A, (HL)",     0, NULL},
    {"ADD A, A",        0, NULL},
    {"ADC A, B",        0, NULL},
    {"ADC A, C",        0, NULL},
    {"ADC A, D",        0, NULL},
    {"ADC A, E",        0, NULL},
    {"ADC A, H",        0, NULL},
    {"ADC A, L",        0, NULL},
    {"ADC A, (HL)",     0, NULL},
    {"ADC A, A",        0, NULL},
    {"SUB A, B",        0, NULL},    // 0x9X
    {"SUB A, C",        0, NULL},
    {"SUB A, D",        0, NULL},
    {"SUB A, E",        0, NULL},
    {"SUB A, H",        0, NULL},
    {"SUB A, L",        0, NULL},
    {"SUB A, (HL)",     0, NULL},
    {"SUB A, A",        0, NULL},
    {"SBC A, B",        0, NULL},
    {"SBC A, C",        0, NULL},
    {"SBC A, D",        0, NULL},
    {"SBC A, E",        0, NULL},
    {"SBC A, H",        0, NULL},
    {"SBC A, L",        0, NULL},
    {"SBC A, (HL)",     0, NULL},
    {"SBC A, A",        0, NULL},
    {"AND B",           0, NULL},    // 0xAX
    {"AND C",           0, NULL},
    {"AND D",           0, NULL},
    {"AND E",           0, NULL},
    {"AND H",           0, NULL},
    {"AND L",           0, NULL},
    {"AND (HL)",        0, NULL},
    {"AND A",           0, NULL},
    {"XOR B",           0, cpu_xor_b},
    {"XOR C",           0, cpu_xor_c},
    {"XOR D",           0, cpu_xor_d},
    {"XOR E",           0, cpu_xor_e},
    {"XOR H",           0, cpu_xor_h},
    {"XOR L",           0, cpu_xor_l},
    {"XOR (HL)",        0, cpu_xor_hl},
    {"XOR A",           0, cpu_xor_a},
    {"OR B",            0, NULL},    // 0xBX
    {"OR C",            0, NULL},
    {"OR D",            0, NULL},
    {"OR E",            0, NULL},
    {"OR H",            0, NULL},
    {"OR L",            0, NULL},
    {"OR (HL)",         0, NULL},
    {"OR A",            0, NULL},
    {"CP B",            0, cpu_cp_a},
    {"CP C",            0, cpu_cp_b},
    {"CP D",            0, cpu_cp_c},
    {"CP E",            0, cpu_cp_d},
    {"CP H",            0, cpu_cp_e},
    {"CP L",            0, cpu_cp_h},
    {"CP (HL)",         0, cpu_cp_l},
    {"CP A",            0, cpu_cp_hl},
    {"RET NZ",          0, NULL},    // 0xCX
    {"POP BC",          0, NULL},
    {"JP NZ, 0x%04x",   2, NULL},
    {"JP 0x%04x",       2, cpu_jp},
    {"CALL NZ, 0x%04x", 2, NULL},
    {"PUSH BC",         0, cpu_push_bc},
    {"ADD A, 0x%02x",   1, NULL},
    {"RST 0x00",        0, NULL},
    {"RET Z",           0, NULL},
    {"RET",             0, NULL},
    {"JP Z, 0x%04x",    2, NULL},
    {"CB %2X",          1, cb_prefix},
    {"CALL Z, 0x%04x",  2, NULL},
    {"CALL 0x%04x",     2, cpu_call},
    {"ADC A, 0x%02x",   1, NULL},
    {"RST 0x08",        0, NULL},
    {"RET NC",          0, NULL},    // 0xDX
    {"POP DE",          0, NULL},
    {"JP NC, 0x%04x",   2, NULL},
    {"NONE",            0, NULL},
    {"CALL NC, 0x%04x", 2, NULL},
    {"PUSH DE",         0, cpu_push_de},
    {"SUB A, 0x%02x",   1, NULL},
    {"RST 0x10",        0, NULL},
    {"RET C",           0, NULL},
    {"RETI",            0, NULL},
    {"JP C, 0x%04x",    2, NULL},
    {"NONE",            0, NULL},
    {"CALL C, 0x%04x",  2, NULL},
    {"NONE",            0, NULL},
    {"SBC A, 0x%02x",   1, NULL},
    {"RST 0x18",        0, NULL},
    {"LDH (0x%02x), A", 1, cpu_ldh_n_a},    // 0xEX
    {"POP HL",          0, NULL},
    {"LD (C), A",       0, NULL},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"PUSH HL",         0, cpu_push_hl},
    {"AND 0x%02x",      1, NULL},
    {"RST 0x20",        0, NULL},
    {"ADD SP, 0x%02x",  1, NULL},
    {"JP (HL)",         0, NULL},
    {"LD (0x%04x), A",  2, cpu_ld_n_a},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"XOR 0x%02x",      1, NULL},
    {"RST 0x28",        0, NULL},
    {"LDH A, (0x%02x)", 1, cpu_ldh_a_n},    // 0xFX
    {"POP AF",          0, NULL},
    {"LD A, (C)",       0, NULL},
    {"DI",              0, cpu_di},
    {"NONE",            0, NULL},
    {"PUSH AF",         0, cpu_push_af},
    {"OR 0x%02x",       1, NULL},
    {"RST 0x30",        0, NULL},
    {"LD HL, SP+0x%02x",1, NULL},
    {"LD SP, HL",       0, NULL},
    {"LD A, (0x%04x)",  2, NULL},
    {"EI",              0, cpu_ei},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"CP 0x%02x",       1, cpu_cp_n},
    {"RST 0x38",        0, NULL},
};

#endif /* INSTRUCTION_H */
