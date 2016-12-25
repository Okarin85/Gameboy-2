/* instruction.h --- 
 * 
 * Filename: instruction.h
 * Author: Jules <archjules>
 * Created: Thu Dec  8 12:54:40 2016 (+0100)
 * Last-Updated: Mon Dec 26 00:11:20 2016 (+0100)
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

int cpu_ld_a_nn(struct CPU *, uint16_t);
int cpu_ld_a_bc(struct CPU *);
int cpu_ld_a_de(struct CPU *);
int cpu_ld_bc_a(struct CPU *);
int cpu_ld_de_a(struct CPU *);

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

int cpu_ldm_c_a(struct CPU *);
int cpu_ldm_a_c(struct CPU *);

int cpu_ld_bc_nn(struct CPU *, uint16_t);
int cpu_ld_de_nn(struct CPU *, uint16_t);
int cpu_ld_hl_nn(struct CPU *, uint16_t);
int cpu_ld_sp_nn(struct CPU *, uint16_t);
int cpu_ld_sp_hl(struct CPU *);
int cpu_ld_nn_sp(struct CPU *);

int cpu_pop_bc(struct CPU *);
int cpu_pop_de(struct CPU *);
int cpu_pop_hl(struct CPU *);
int cpu_pop_af(struct CPU *);

int cpu_push_bc(struct CPU *);
int cpu_push_de(struct CPU *);
int cpu_push_hl(struct CPU *);
int cpu_push_af(struct CPU *);

int cpu_rl_a(struct CPU *);
int cpu_rl_b(struct CPU *);
int cpu_rl_c(struct CPU *);
int cpu_rl_d(struct CPU *);
int cpu_rl_e(struct CPU *);
int cpu_rl_h(struct CPU *);
int cpu_rl_l(struct CPU *);

int cpu_rr_a(struct CPU *);
int cpu_rr_b(struct CPU *);
int cpu_rr_c(struct CPU *);
int cpu_rr_d(struct CPU *);
int cpu_rr_e(struct CPU *);
int cpu_rr_h(struct CPU *);
int cpu_rr_l(struct CPU *);

int cpu_rlc_a(struct CPU *);
int cpu_rlc_b(struct CPU *);
int cpu_rlc_c(struct CPU *);
int cpu_rlc_d(struct CPU *);
int cpu_rlc_e(struct CPU *);
int cpu_rlc_h(struct CPU *);
int cpu_rlc_l(struct CPU *);

int cpu_add_a(struct CPU *);
int cpu_add_b(struct CPU *);
int cpu_add_c(struct CPU *);
int cpu_add_d(struct CPU *);
int cpu_add_e(struct CPU *);
int cpu_add_h(struct CPU *);
int cpu_add_l(struct CPU *);
int cpu_add_hl(struct CPU *);
int cpu_add_n(struct CPU *, uint8_t operand);

int cpu_adc_a(struct CPU *);
int cpu_adc_b(struct CPU *);
int cpu_adc_c(struct CPU *);
int cpu_adc_d(struct CPU *);
int cpu_adc_e(struct CPU *);
int cpu_adc_h(struct CPU *);
int cpu_adc_l(struct CPU *);
int cpu_adc_hl(struct CPU *);
int cpu_adc_n(struct CPU *, uint8_t);

int cpu_sub_a(struct CPU *);
int cpu_sub_b(struct CPU *);
int cpu_sub_c(struct CPU *);
int cpu_sub_d(struct CPU *);
int cpu_sub_e(struct CPU *);
int cpu_sub_h(struct CPU *);
int cpu_sub_l(struct CPU *);
int cpu_sub_hl(struct CPU *);
int cpu_sub_n(struct CPU *, uint8_t);

int cpu_sbc_a(struct CPU *);
int cpu_sbc_b(struct CPU *);
int cpu_sbc_c(struct CPU *);
int cpu_sbc_d(struct CPU *);
int cpu_sbc_e(struct CPU *);
int cpu_sbc_h(struct CPU *);
int cpu_sbc_l(struct CPU *);
int cpu_sbc_hl(struct CPU *);
int cpu_sbc_n(struct CPU *, uint8_t);

int cpu_dec_a(struct CPU *);
int cpu_dec_b(struct CPU *);
int cpu_dec_c(struct CPU *);
int cpu_dec_d(struct CPU *);
int cpu_dec_e(struct CPU *);
int cpu_dec_h(struct CPU *);
int cpu_dec_l(struct CPU *);
int cpu_decm_hl(struct CPU *);

int cpu_inc_a(struct CPU *);
int cpu_inc_b(struct CPU *);
int cpu_inc_c(struct CPU *);
int cpu_inc_d(struct CPU *);
int cpu_inc_e(struct CPU *);
int cpu_inc_h(struct CPU *);
int cpu_inc_l(struct CPU *);
int cpu_incm_hl(struct CPU *);

int cpu_cp_a(struct CPU *);
int cpu_cp_b(struct CPU *);
int cpu_cp_c(struct CPU *);
int cpu_cp_d(struct CPU *);
int cpu_cp_e(struct CPU *);
int cpu_cp_h(struct CPU *);
int cpu_cp_l(struct CPU *);
int cpu_cp_hl(struct CPU *);
int cpu_cp_n(struct CPU *, uint8_t);

int cpu_add_hl_bc(struct CPU *);
int cpu_add_hl_de(struct CPU *);
int cpu_add_hl_hl(struct CPU *);
int cpu_add_hl_sp(struct CPU *);

int cpu_dec_bc(struct CPU *);
int cpu_dec_de(struct CPU *);
int cpu_dec_hl(struct CPU *);
int cpu_dec_sp(struct CPU *);

int cpu_inc_bc(struct CPU *);
int cpu_inc_de(struct CPU *);
int cpu_inc_hl(struct CPU *);
int cpu_inc_sp(struct CPU *);

int cpu_cpl(struct CPU *);

int cpu_and_b(struct CPU *); 
int cpu_and_c(struct CPU *); 
int cpu_and_d(struct CPU *); 
int cpu_and_e(struct CPU *); 
int cpu_and_h(struct CPU *); 
int cpu_and_l(struct CPU *); 
int cpu_and_hl(struct CPU *); 
int cpu_and_a(struct CPU *);
int cpu_and_n(struct CPU *, uint8_t);

int cpu_or_b(struct CPU *); 
int cpu_or_c(struct CPU *); 
int cpu_or_d(struct CPU *); 
int cpu_or_e(struct CPU *); 
int cpu_or_h(struct CPU *); 
int cpu_or_l(struct CPU *); 
int cpu_or_hl(struct CPU *); 
int cpu_or_a(struct CPU *);
int cpu_or_n(struct CPU *, uint8_t);

int cpu_xor_b(struct CPU *); 
int cpu_xor_c(struct CPU *); 
int cpu_xor_d(struct CPU *); 
int cpu_xor_e(struct CPU *); 
int cpu_xor_h(struct CPU *); 
int cpu_xor_l(struct CPU *); 
int cpu_xor_hl(struct CPU *); 
int cpu_xor_a(struct CPU *);
int cpu_xor_n(struct CPU *, uint8_t);

int cpu_jp(struct CPU *, uint16_t);
int cpu_jr(struct CPU *, uint8_t);
int cpu_jp_hl(struct CPU *);

int cpu_jp_z(struct CPU *, uint16_t);
int cpu_jp_c(struct CPU *, uint16_t);
int cpu_jp_nz(struct CPU *, uint16_t);
int cpu_jp_nc(struct CPU *, uint16_t);

int cpu_jr_z(struct CPU *, uint8_t);
int cpu_jr_c(struct CPU *, uint8_t);
int cpu_jr_nz(struct CPU *, uint8_t);
int cpu_jr_nc(struct CPU *, uint8_t);

int cpu_call(struct CPU *, uint16_t);
int cpu_call_z(struct CPU *, uint16_t);
int cpu_call_c(struct CPU *, uint16_t);
int cpu_call_nz(struct CPU *, uint16_t);
int cpu_call_nc(struct CPU *, uint16_t);

int cpu_ret(struct CPU *);
int cpu_ret_z(struct CPU *);
int cpu_ret_c(struct CPU *);
int cpu_ret_nz(struct CPU *);
int cpu_ret_nc(struct CPU *);
int cpu_reti(struct CPU *);

int cpu_rst_00(struct CPU *);
int cpu_rst_08(struct CPU *);
int cpu_rst_10(struct CPU *);
int cpu_rst_18(struct CPU *);
int cpu_rst_20(struct CPU *);
int cpu_rst_28(struct CPU *);
int cpu_rst_30(struct CPU *);
int cpu_rst_38(struct CPU *);

int cpu_scf(struct CPU *);
int cpu_ccf(struct CPU *);
int cpu_daa(struct CPU *);

static struct Instruction instructions[] = {
    {"NOP",             0, cpu_nop}, // 0x0X
    {"LD BC, 0x%04x",   2, cpu_ld_bc_nn},
    {"LD (BC), A",      0, cpu_ld_bc_a},
    {"INC BC",          0, cpu_inc_bc},
    {"INC B",           0, cpu_inc_b},
    {"DEC B",           0, cpu_dec_b},
    {"LD B, 0x%02x",    1, cpu_ld_b_n},
    {"RLCA",            0, cpu_rlc_a},
    {"LD (0x%04x), SP", 2, cpu_ld_nn_sp},
    {"ADD HL, BC",      0, cpu_add_hl_bc},
    {"LD A, (BC)",      0, cpu_ld_a_bc},
    {"DEC BC",          0, cpu_dec_bc},
    {"INC C",           0, cpu_inc_c},
    {"DEC C",           0, cpu_dec_c},
    {"LD C, 0x%02x",    1, cpu_ld_c_n},
    {"RRCA",            0, NULL},
    {"STOP",            0, NULL},    // 0x1X
    {"LD DE, 0x%04x",   2, cpu_ld_de_nn},
    {"LD (DE), A",      0, cpu_ld_de_a},
    {"INC DE",          0, cpu_inc_de},
    {"INC D",           0, cpu_inc_d},
    {"DEC D",           0, cpu_dec_d},
    {"LD D, 0x%02x",    1, cpu_ld_d_n},
    {"RLA",             0, cpu_rl_a},
    {"JR 0x%02x",       1, cpu_jr},
    {"ADD HL, DE",      0, cpu_add_hl_de},
    {"LD A, (DE)",      0, cpu_ld_a_de},
    {"DEC DE",          0, cpu_dec_de},
    {"INC E",           0, cpu_inc_e},
    {"DEC E",           0, cpu_dec_e},
    {"LD E, 0x%02x",    1, cpu_ld_e_n},
    {"RRA",             0, cpu_rr_a},
    {"JR NZ, 0x%02x",   1, cpu_jr_nz},    // 0x2X
    {"LD HL, 0x%04x",   2, cpu_ld_hl_nn},
    {"LD (HL+), A",     0, cpu_ldi_hl_a},
    {"INC HL",          0, cpu_inc_hl},
    {"INC H",           0, cpu_inc_h},
    {"DEC H",           0, cpu_dec_h},
    {"LD H, 0x%02x",    1, cpu_ld_h_n},
    {"DAA",             0, cpu_daa},
    {"JR Z, 0x%02x",    1, cpu_jr_z},
    {"ADD HL, HL",      0, cpu_add_hl_hl},
    {"LD A, (HL+)",     0, cpu_ldi_a_hl},
    {"DEC HL",          0, cpu_dec_hl},
    {"INC L",           0, cpu_inc_l},
    {"DEC L",           0, cpu_dec_l},
    {"LD L, 0x%02x",    1, cpu_ld_l_n},
    {"CPL",             0, cpu_cpl},
    {"JR NC, 0x%02x",   1, cpu_jr_nc},    // 0x3X
    {"LD SP, 0x%04x",   2, cpu_ld_sp_nn},
    {"LD (HL-), A",     0, cpu_ldd_hl_a},
    {"INC SP",          0, cpu_inc_sp},
    {"INC (HL)",        0, cpu_incm_hl},
    {"DEC (HL)",        0, cpu_decm_hl},
    {"LD (HL), 0x%02x", 1, cpu_ld_hl_n},
    {"SCF",             0, cpu_scf},
    {"JR C, 0x%02x",    1, cpu_jr_c},
    {"ADD HL, SP",      0, cpu_add_hl_sp},
    {"LD A, (HL-)",     0, cpu_ldd_a_hl},
    {"DEC SP",          0, cpu_dec_sp},
    {"INC A",           0, cpu_inc_a},
    {"DEC A",           0, cpu_dec_a},
    {"LD A, 0x%02x",    1, cpu_ld_a_n},
    {"CCF",             0, cpu_ccf},
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
    {"ADD A, B",        0, cpu_add_b},    // 0x8X
    {"ADD A, C",        0, cpu_add_c},
    {"ADD A, D",        0, cpu_add_d},
    {"ADD A, E",        0, cpu_add_e},
    {"ADD A, H",        0, cpu_add_h},
    {"ADD A, L",        0, cpu_add_l},
    {"ADD A, (HL)",     0, cpu_add_hl},
    {"ADD A, A",        0, cpu_add_a},
    {"ADC A, B",        0, cpu_adc_b},
    {"ADC A, C",        0, cpu_adc_c},
    {"ADC A, D",        0, cpu_adc_d},
    {"ADC A, E",        0, cpu_adc_e},
    {"ADC A, H",        0, cpu_adc_h},
    {"ADC A, L",        0, cpu_adc_l},
    {"ADC A, (HL)",     0, cpu_adc_hl},
    {"ADC A, A",        0, cpu_adc_a},
    {"SUB A, B",        0, cpu_sub_b},    // 0x9X
    {"SUB A, C",        0, cpu_sub_c},
    {"SUB A, D",        0, cpu_sub_d},
    {"SUB A, E",        0, cpu_sub_e},
    {"SUB A, H",        0, cpu_sub_h},
    {"SUB A, L",        0, cpu_sub_l},
    {"SUB A, (HL)",     0, cpu_sub_hl},
    {"SUB A, A",        0, cpu_sub_a},
    {"SBC A, B",        0, cpu_sbc_b},
    {"SBC A, C",        0, cpu_sbc_c},
    {"SBC A, D",        0, cpu_sbc_d},
    {"SBC A, E",        0, cpu_sbc_e},
    {"SBC A, H",        0, cpu_sbc_h},
    {"SBC A, L",        0, cpu_sbc_l},
    {"SBC A, (HL)",     0, cpu_sbc_hl},
    {"SBC A, A",        0, cpu_sbc_a},
    {"AND B",           0, cpu_and_b},    // 0xAX
    {"AND C",           0, cpu_and_c},
    {"AND D",           0, cpu_and_d},
    {"AND E",           0, cpu_and_e},
    {"AND H",           0, cpu_and_h},
    {"AND L",           0, cpu_and_l},
    {"AND (HL)",        0, cpu_and_hl},
    {"AND A",           0, cpu_and_a},
    {"XOR B",           0, cpu_xor_b},
    {"XOR C",           0, cpu_xor_c},
    {"XOR D",           0, cpu_xor_d},
    {"XOR E",           0, cpu_xor_e},
    {"XOR H",           0, cpu_xor_h},
    {"XOR L",           0, cpu_xor_l},
    {"XOR (HL)",        0, cpu_xor_hl},
    {"XOR A",           0, cpu_xor_a},
    {"OR B",            0, cpu_or_b},    // 0xBX
    {"OR C",            0, cpu_or_c},
    {"OR D",            0, cpu_or_d},
    {"OR E",            0, cpu_or_e},
    {"OR H",            0, cpu_or_h},
    {"OR L",            0, cpu_or_l},
    {"OR (HL)",         0, cpu_or_hl},
    {"OR A",            0, cpu_or_a},
    {"CP B",            0, cpu_cp_b},
    {"CP C",            0, cpu_cp_c},
    {"CP D",            0, cpu_cp_d},
    {"CP E",            0, cpu_cp_e},
    {"CP H",            0, cpu_cp_h},
    {"CP L",            0, cpu_cp_l},
    {"CP (HL)",         0, cpu_cp_hl},
    {"CP A",            0, cpu_cp_a},
    {"RET NZ",          0, cpu_ret_nz},    // 0xCX
    {"POP BC",          0, cpu_pop_bc},
    {"JP NZ, 0x%04x",   2, cpu_jp_nz},
    {"JP 0x%04x",       2, cpu_jp},
    {"CALL NZ, 0x%04x", 2, cpu_call_nz},
    {"PUSH BC",         0, cpu_push_bc},
    {"ADD A, 0x%02x",   1, cpu_add_n},
    {"RST 0x00",        0, cpu_rst_00},
    {"RET Z",           0, cpu_ret_z},
    {"RET",             0, cpu_ret},
    {"JP Z, 0x%04x",    2, cpu_jp_z},
    {"CB %2X",          1, cb_prefix},
    {"CALL Z, 0x%04x",  2, cpu_call_z},
    {"CALL 0x%04x",     2, cpu_call},
    {"ADC A, 0x%02x",   1, cpu_adc_n},
    {"RST 0x08",        0, cpu_rst_08},
    {"RET NC",          0, cpu_ret_nc},    // 0xDX
    {"POP DE",          0, cpu_pop_de},
    {"JP NC, 0x%04x",   2, cpu_jp_nc},
    {"NONE",            0, NULL},
    {"CALL NC, 0x%04x", 2, cpu_call_nc},
    {"PUSH DE",         0, cpu_push_de},
    {"SUB A, 0x%02x",   1, cpu_sub_n},
    {"RST 0x10",        0, cpu_rst_10},
    {"RET C",           0, cpu_ret_c},
    {"RETI",            0, cpu_reti},
    {"JP C, 0x%04x",    2, cpu_jp_c},
    {"NONE",            0, NULL},
    {"CALL C, 0x%04x",  2, cpu_call_c},
    {"NONE",            0, NULL},
    {"SBC A, 0x%02x",   1, NULL},
    {"RST 0x18",        0, cpu_rst_18},
    {"LDH (0x%02x), A", 1, cpu_ldh_n_a},    // 0xEX
    {"POP HL",          0, cpu_pop_hl},
    {"LD (C), A",       0, cpu_ldm_c_a},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"PUSH HL",         0, cpu_push_hl},
    {"AND 0x%02x",      1, cpu_and_n},
    {"RST 0x20",        0, cpu_rst_20},
    {"ADD SP, 0x%02x",  1, NULL},
    {"JP (HL)",         0, cpu_jp_hl},
    {"LD (0x%04x), A",  2, cpu_ld_n_a},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"XOR 0x%02x",      1, cpu_xor_n},
    {"RST 0x28",        0, cpu_rst_28},
    {"LDH A, (0x%02x)", 1, cpu_ldh_a_n},    // 0xFX
    {"POP AF",          0, cpu_pop_af},
    {"LD A, (C)",       0, cpu_ldm_a_c},
    {"DI",              0, cpu_di},
    {"NONE",            0, NULL},
    {"PUSH AF",         0, cpu_push_af},
    {"OR 0x%02x",       1, cpu_or_n},
    {"RST 0x30",        0, cpu_rst_30},
    {"LD HL, SP+0x%02x",1, NULL},
    {"LD SP, HL",       0, cpu_ld_sp_hl},
    {"LD A, (0x%04x)",  2, cpu_ld_a_nn},
    {"EI",              0, cpu_ei},
    {"NONE",            0, NULL},
    {"NONE",            0, NULL},
    {"CP 0x%02x",       1, cpu_cp_n},
    {"RST 0x38",        0, cpu_rst_38},
};

#endif /* INSTRUCTION_H */
