#ifndef SM83_H_
#define SM83_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef struct SM83Instruction SM83Instruction; // Forward declaration

typedef struct {
  // Registers
  union {
    struct { uint8_t f, a; };
    uint16_t af;
  };

  union {
    struct { uint8_t c, b; };
    uint16_t bc;
  };

  union {
    struct { uint8_t e, d; };
    uint16_t de;
  };

  union {
    struct { uint8_t l, h; };
    uint16_t hl;
  };

  uint16_t sp;
  uint16_t pc;

  // Read/Write functions
  uint8_t (*read)(uint16_t);
  void (*write)(uint16_t, uint8_t);

  // Internals
  uint8_t t;

  const SM83Instruction *instruction; // Debug
} SM83;

struct SM83Instruction {
  const char *mnemonic;
  void (*exec)(SM83 *);
  const uint8_t length;
  const uint8_t ticks;
};

void SM83_init(SM83 *cpu, uint8_t (*read)(uint16_t), void (*write)(uint16_t, uint8_t));

void SM83_reset(SM83 *cpu);

void SM83_tick(SM83 *cpu);

#ifdef __cplusplus
}
#endif

#endif // SM83_H_

#ifdef SM83_IMPLEMENTATION

void SM83_init(SM83 *cpu, uint8_t (*read)(uint16_t), void (*write)(uint16_t, uint8_t)) {
  cpu->read = read;
  cpu->write = write;
}

void SM83_reset(SM83 *cpu) {
  // TODO
  cpu->t = 0;
}

// Flags helpers
#define FLAG_Z 7
#define FLAG_N 6
#define FLAG_H 5
#define FLAG_C 4

static inline
void set_flag(uint8_t *flags, uint8_t flag, uint8_t value) {
  if (value) {
    *flags |= (uint8_t)(1 << flag);
  } else {
    *flags &= (uint8_t)~(1 << flag);
  }
}

static inline
uint8_t get_flag(uint8_t *flags, uint8_t flag) {
  return (*flags >> flag) & 1;
}

// Instructions
// ----------------
static void nop(SM83 *cpu) { (void)cpu; }
static void stop(SM83 *cpu) { (void)cpu; } // TODO
static void halt(SM83 *cpu) { (void)cpu; } // TODO

static void invalid(SM83 *cpu) {
  (void)cpu;
  // TODO: Decide what to do
}

static void di(SM83 *cpu) { (void)cpu; } // TODO
static void ei(SM83 *cpu) { (void)cpu; } // TODO

// ** 8-bit load instructions **
static void ld_b_b(SM83 *cpu) { cpu->b = cpu->b; }
static void ld_b_c(SM83 *cpu) { cpu->b = cpu->c; }
static void ld_b_d(SM83 *cpu) { cpu->b = cpu->d; }
static void ld_b_e(SM83 *cpu) { cpu->b = cpu->e; }
static void ld_b_h(SM83 *cpu) { cpu->b = cpu->h; }
static void ld_b_l(SM83 *cpu) { cpu->b = cpu->l; }
static void ld_b_a(SM83 *cpu) { cpu->b = cpu->a; }
static void ld_c_b(SM83 *cpu) { cpu->c = cpu->b; }
static void ld_c_c(SM83 *cpu) { cpu->c = cpu->c; }
static void ld_c_d(SM83 *cpu) { cpu->c = cpu->d; }
static void ld_c_e(SM83 *cpu) { cpu->c = cpu->e; }
static void ld_c_h(SM83 *cpu) { cpu->c = cpu->h; }
static void ld_c_l(SM83 *cpu) { cpu->c = cpu->l; }
static void ld_c_a(SM83 *cpu) { cpu->c = cpu->a; }
static void ld_d_b(SM83 *cpu) { cpu->d = cpu->b; }
static void ld_d_c(SM83 *cpu) { cpu->d = cpu->c; }
static void ld_d_d(SM83 *cpu) { cpu->d = cpu->d; }
static void ld_d_e(SM83 *cpu) { cpu->d = cpu->e; }
static void ld_d_h(SM83 *cpu) { cpu->d = cpu->h; }
static void ld_d_l(SM83 *cpu) { cpu->d = cpu->l; }
static void ld_d_a(SM83 *cpu) { cpu->d = cpu->a; }
static void ld_e_b(SM83 *cpu) { cpu->e = cpu->b; }
static void ld_e_c(SM83 *cpu) { cpu->e = cpu->c; }
static void ld_e_d(SM83 *cpu) { cpu->e = cpu->d; }
static void ld_e_e(SM83 *cpu) { cpu->e = cpu->e; }
static void ld_e_h(SM83 *cpu) { cpu->e = cpu->h; }
static void ld_e_l(SM83 *cpu) { cpu->e = cpu->l; }
static void ld_e_a(SM83 *cpu) { cpu->e = cpu->a; }
static void ld_h_b(SM83 *cpu) { cpu->h = cpu->b; }
static void ld_h_c(SM83 *cpu) { cpu->h = cpu->c; }
static void ld_h_d(SM83 *cpu) { cpu->h = cpu->d; }
static void ld_h_e(SM83 *cpu) { cpu->h = cpu->e; }
static void ld_h_h(SM83 *cpu) { cpu->h = cpu->h; }
static void ld_h_l(SM83 *cpu) { cpu->h = cpu->l; }
static void ld_h_a(SM83 *cpu) { cpu->h = cpu->a; }
static void ld_l_b(SM83 *cpu) { cpu->l = cpu->b; }
static void ld_l_c(SM83 *cpu) { cpu->l = cpu->c; }
static void ld_l_d(SM83 *cpu) { cpu->l = cpu->d; }
static void ld_l_e(SM83 *cpu) { cpu->l = cpu->e; }
static void ld_l_h(SM83 *cpu) { cpu->l = cpu->h; }
static void ld_l_l(SM83 *cpu) { cpu->l = cpu->l; }
static void ld_l_a(SM83 *cpu) { cpu->l = cpu->a; }
static void ld_a_b(SM83 *cpu) { cpu->a = cpu->b; }
static void ld_a_c(SM83 *cpu) { cpu->a = cpu->c; }
static void ld_a_d(SM83 *cpu) { cpu->a = cpu->d; }
static void ld_a_e(SM83 *cpu) { cpu->a = cpu->e; }
static void ld_a_h(SM83 *cpu) { cpu->a = cpu->h; }
static void ld_a_l(SM83 *cpu) { cpu->a = cpu->l; }
static void ld_a_a(SM83 *cpu) { cpu->a = cpu->a; }

static void ld_b_n(SM83 *cpu) { cpu->b = cpu->read(cpu->pc++); }
static void ld_c_n(SM83 *cpu) { cpu->c = cpu->read(cpu->pc++); }
static void ld_d_n(SM83 *cpu) { cpu->d = cpu->read(cpu->pc++); }
static void ld_e_n(SM83 *cpu) { cpu->e = cpu->read(cpu->pc++); }
static void ld_h_n(SM83 *cpu) { cpu->h = cpu->read(cpu->pc++); }
static void ld_l_n(SM83 *cpu) { cpu->l = cpu->read(cpu->pc++); }
static void ld_a_n(SM83 *cpu) { cpu->a = cpu->read(cpu->pc++); }

static void ld_b_hl(SM83 *cpu) { cpu->b = cpu->read(cpu->hl); }
static void ld_c_hl(SM83 *cpu) { cpu->c = cpu->read(cpu->hl); }
static void ld_d_hl(SM83 *cpu) { cpu->d = cpu->read(cpu->hl); }
static void ld_e_hl(SM83 *cpu) { cpu->e = cpu->read(cpu->hl); }
static void ld_h_hl(SM83 *cpu) { cpu->h = cpu->read(cpu->hl); }
static void ld_l_hl(SM83 *cpu) { cpu->l = cpu->read(cpu->hl); }
static void ld_a_hl(SM83 *cpu) { cpu->a = cpu->read(cpu->hl); }
static void ld_a_hlp(SM83 *cpu) { cpu->a = cpu->read(cpu->hl++); }
static void ld_a_hlm(SM83 *cpu) { cpu->a = cpu->read(cpu->hl--); }

static void ldi_bc_a(SM83 *cpu) { cpu->write(cpu->bc, cpu->a); }
static void ldi_de_a(SM83 *cpu) { cpu->write(cpu->de, cpu->a); }
static void ldi_hlp_a(SM83 *cpu) { cpu->write(cpu->hl++, cpu->a); }
static void ldi_hlm_a(SM83 *cpu) { cpu->write(cpu->hl--, cpu->a); }
static void ldi_hl_b(SM83 *cpu) { cpu->write(cpu->hl, cpu->b); }
static void ldi_hl_c(SM83 *cpu) { cpu->write(cpu->hl, cpu->c); }
static void ldi_hl_d(SM83 *cpu) { cpu->write(cpu->hl, cpu->d); }
static void ldi_hl_e(SM83 *cpu) { cpu->write(cpu->hl, cpu->e); }
static void ldi_hl_h(SM83 *cpu) { cpu->write(cpu->hl, cpu->h); }
static void ldi_hl_l(SM83 *cpu) { cpu->write(cpu->hl, cpu->l); }
static void ldi_hl_a(SM83 *cpu) { cpu->write(cpu->hl, cpu->a); }
static void ldi_hl_n(SM83 *cpu) { cpu->write(cpu->hl, cpu->read(cpu->pc++)); }
static void ldi_a_bc(SM83 *cpu) { cpu->a = cpu->read(cpu->bc); }
static void ldi_a_de(SM83 *cpu) { cpu->a = cpu->read(cpu->de); }

static void ldh_n_a(SM83 *cpu) {
  uint16_t n = cpu->read(cpu->pc++);
  cpu->write(0xFF00 | n, cpu->a);
}
static void ldh_c_a(SM83 *cpu) { cpu->write((uint16_t)(0xFF00 | cpu->c), cpu->a); }
static void ldh_a_c(SM83 *cpu) { cpu->a = cpu->read((uint16_t)(0xFF00 | cpu->c)); }
static void ldh_a_n(SM83 *cpu) {
  uint16_t n = cpu->read(cpu->pc++);
  cpu->a = cpu->read(0xFF00 | n);
}

static void ld_a_nn(SM83 *cpu) {
  uint16_t low = cpu->read(cpu->pc++);
  uint16_t high = cpu->read(cpu->pc++);
  uint16_t nn = (uint16_t)(high << 8) | low;
  cpu->a = cpu->read(nn);
}
static void ld_nn_a(SM83 *cpu) {
  uint16_t low = cpu->read(cpu->pc++);
  uint16_t high = cpu->read(cpu->pc++);
  uint16_t nn = (uint16_t)(high << 8) | low;
  cpu->write(nn, cpu->a);
}

// ** 8-bit arithmetic and logical instructions **
#define ADD(value) { \
  uint8_t result = (uint8_t)(cpu->a + value); \
  set_flag(&cpu->f, FLAG_Z, (result == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, (((cpu->a & 0x0F) + (value & 0x0F)) & 0x10) == 0x10); \
  set_flag(&cpu->f, FLAG_C, (result < cpu->a)); \
  cpu->a = result; \
}
#define ADDr(r) { \
  uint8_t value = cpu->r; \
  ADD(value); \
}

static void add_a_b(SM83 *cpu) { ADDr(b); }
static void add_a_c(SM83 *cpu) { ADDr(c); }
static void add_a_d(SM83 *cpu) { ADDr(d); }
static void add_a_e(SM83 *cpu) { ADDr(e); }
static void add_a_h(SM83 *cpu) { ADDr(h); }
static void add_a_l(SM83 *cpu) { ADDr(l); }
static void add_a_a(SM83 *cpu) { ADDr(a); }
static void add_a_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); ADD(value); }
static void add_a_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); ADD(value); }

#define ADC(value) { \
  uint8_t carry = (cpu->f >> FLAG_C) & 1; \
  uint8_t result = (uint8_t)(cpu->a + value + carry); \
  set_flag(&cpu->f, FLAG_Z, (result == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, (((cpu->a & 0x0F) + (value & 0x0F) + carry) & 0x10) == 0x10); \
  set_flag(&cpu->f, FLAG_C, (((cpu->a & 0xFF) + (value & 0xFF) + carry) & 0x100) == 0x100); \
  cpu->a = result; \
}
#define ADCr(r) { \
  uint8_t value = cpu->r; \
  ADC(value); \
}

static void adc_a_b(SM83 *cpu) { ADCr(b); }
static void adc_a_c(SM83 *cpu) { ADCr(c); }
static void adc_a_d(SM83 *cpu) { ADCr(d); }
static void adc_a_e(SM83 *cpu) { ADCr(e); }
static void adc_a_h(SM83 *cpu) { ADCr(h); }
static void adc_a_l(SM83 *cpu) { ADCr(l); }
static void adc_a_a(SM83 *cpu) { ADCr(a); }
static void adc_a_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); ADC(value); }
static void adc_a_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); ADC(value); }

#define SUB(value) { \
  uint8_t result = (uint8_t)(cpu->a - value); \
  set_flag(&cpu->f, FLAG_Z, (result == 0)); \
  set_flag(&cpu->f, FLAG_N, 1); \
  set_flag(&cpu->f, FLAG_H, ((cpu->a & 0x0F) < (value & 0x0F))); \
  set_flag(&cpu->f, FLAG_C, (result > cpu->a)); \
  cpu->a = result; \
}
#define SUBr(r) { \
  uint8_t value = cpu->r; \
  SUB(value); \
}

static void sub_b(SM83 *cpu) { SUBr(b); }
static void sub_c(SM83 *cpu) { SUBr(c); }
static void sub_d(SM83 *cpu) { SUBr(d); }
static void sub_e(SM83 *cpu) { SUBr(e); }
static void sub_h(SM83 *cpu) { SUBr(h); }
static void sub_l(SM83 *cpu) { SUBr(l); }
static void sub_a(SM83 *cpu) { SUBr(a); }
static void sub_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); SUB(value); }
static void sub_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); SUB(value); }

#define SBC(value) { \
  uint8_t carry = (cpu->f >> FLAG_C) & 1; \
  uint8_t result = (uint8_t)(cpu->a - value - carry); \
  set_flag(&cpu->f, FLAG_Z, (result == 0)); \
  set_flag(&cpu->f, FLAG_N, 1); \
  set_flag(&cpu->f, FLAG_H, ((cpu->a & 0x0F) < (value & 0x0F) + carry)); \
  set_flag(&cpu->f, FLAG_C, ((cpu->a & 0xFF) < (value & 0xFF) + carry)); \
  cpu->a = result; \
}
#define SBCr(r) { \
  uint8_t value = cpu->r; \
  SBC(value); \
}

static void sbc_a_b(SM83 *cpu) { SBCr(b); }
static void sbc_a_c(SM83 *cpu) { SBCr(c); }
static void sbc_a_d(SM83 *cpu) { SBCr(d); }
static void sbc_a_e(SM83 *cpu) { SBCr(e); }
static void sbc_a_h(SM83 *cpu) { SBCr(h); }
static void sbc_a_l(SM83 *cpu) { SBCr(l); }
static void sbc_a_a(SM83 *cpu) { SBCr(a); }
static void sbc_a_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); SBC(value); }
static void sbc_a_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); SBC(value); }

#define AND(value) { \
  cpu->a &= value; \
  set_flag(&cpu->f, FLAG_Z, (cpu->a == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 1); \
  set_flag(&cpu->f, FLAG_C, 0); \
}
#define ANDr(r) { \
  uint8_t value = cpu->r; \
  AND(value); \
}

static void and_b(SM83 *cpu) { ANDr(b); }
static void and_c(SM83 *cpu) { ANDr(c); }
static void and_d(SM83 *cpu) { ANDr(d); }
static void and_e(SM83 *cpu) { ANDr(e); }
static void and_h(SM83 *cpu) { ANDr(h); }
static void and_l(SM83 *cpu) { ANDr(l); }
static void and_a(SM83 *cpu) { ANDr(a); }
static void and_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); AND(value); }
static void and_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); AND(value); }

#define XOR(value) { \
  cpu->a ^= value; \
  set_flag(&cpu->f, FLAG_Z, (cpu->a == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
  set_flag(&cpu->f, FLAG_C, 0); \
}
#define XORr(r) { \
  uint8_t value = cpu->r; \
  XOR(value); \
}

static void xor_b(SM83 *cpu) { XORr(b); }
static void xor_c(SM83 *cpu) { XORr(c); }
static void xor_d(SM83 *cpu) { XORr(d); }
static void xor_e(SM83 *cpu) { XORr(e); }
static void xor_h(SM83 *cpu) { XORr(h); }
static void xor_l(SM83 *cpu) { XORr(l); }
static void xor_a(SM83 *cpu) { XORr(a); }
static void xor_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); XOR(value); }
static void xor_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); XOR(value); }

#define OR(value) { \
  cpu->a |= value; \
  set_flag(&cpu->f, FLAG_Z, (cpu->a == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
  set_flag(&cpu->f, FLAG_C, 0); \
}
#define ORr(r) { \
  uint8_t value = cpu->r; \
  OR(value); \
}

static void or_b(SM83 *cpu) { ORr(b); }
static void or_c(SM83 *cpu) { ORr(c); }
static void or_d(SM83 *cpu) { ORr(d); }
static void or_e(SM83 *cpu) { ORr(e); }
static void or_h(SM83 *cpu) { ORr(h); }
static void or_l(SM83 *cpu) { ORr(l); }
static void or_a(SM83 *cpu) { ORr(a); }
static void or_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); OR(value); }
static void or_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); OR(value); }

#define CP(value) { \
  uint8_t result = (uint8_t)(cpu->a - value); \
  set_flag(&cpu->f, FLAG_Z, (result == 0)); \
  set_flag(&cpu->f, FLAG_N, 1); \
  set_flag(&cpu->f, FLAG_H, ((cpu->a & 0x0F) < (value & 0x0F))); \
  set_flag(&cpu->f, FLAG_C, (result > cpu->a)); \
}
#define CPr(r) { \
  uint8_t value = cpu->r; \
  CP(value); \
}

static void cp_b(SM83 *cpu) { CPr(b); }
static void cp_c(SM83 *cpu) { CPr(c); }
static void cp_d(SM83 *cpu) { CPr(d); }
static void cp_e(SM83 *cpu) { CPr(e); }
static void cp_h(SM83 *cpu) { CPr(h); }
static void cp_l(SM83 *cpu) { CPr(l); }
static void cp_a(SM83 *cpu) { CPr(a); }
static void cp_hl(SM83 *cpu) { uint8_t value = cpu->read(cpu->hl); CP(value); }
static void cp_n(SM83 *cpu) { uint8_t value = cpu->read(cpu->pc++); CP(value); }

static void ccf(SM83 *cpu) {
  set_flag(&cpu->f, FLAG_N, 0);
  set_flag(&cpu->f, FLAG_H, 0);
  set_flag(&cpu->f, FLAG_C, !get_flag(&cpu->f, FLAG_C));
}

static void scf(SM83 *cpu) {
  set_flag(&cpu->f, FLAG_N, 0);
  set_flag(&cpu->f, FLAG_H, 0);
  set_flag(&cpu->f, FLAG_C, 1);
}

static void cpl(SM83 *cpu) {
  cpu->a = (uint8_t)~cpu->a;
  set_flag(&cpu->f, FLAG_N, 1);
  set_flag(&cpu->f, FLAG_H, 1);
}

// https://forums.nesdev.org/viewtopic.php?p=196282&sid=c64eb1685d89a431486b92c0130ee4b2#p196282
static void daa(SM83 *cpu) {
  uint8_t n_flag = get_flag(&cpu->f, FLAG_N);
  uint8_t h_flag = get_flag(&cpu->f, FLAG_H);
  uint8_t c_flag = get_flag(&cpu->f, FLAG_C);

  if (!n_flag) {
    if (c_flag || cpu->a > 0x99) {
      cpu->a = (uint8_t)(cpu->a + 0x60);
      c_flag = 1; 
    }
    if (h_flag || (cpu->a & 0xF) > 0x9)
      cpu->a = (uint8_t)(cpu->a + 0x6);
  } else {
    if (c_flag) cpu->a = (uint8_t)(cpu->a - 0x60);
    if (h_flag) cpu->a = (uint8_t)(cpu->a - 0x6);
  }

  set_flag(&cpu->f, FLAG_Z, cpu->a == 0);
  set_flag(&cpu->f, FLAG_H, 0);
  set_flag(&cpu->f, FLAG_C, c_flag);
}

#define INCr(r) { \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, ((cpu->r & 0x0F) == 0x0F)); \
  cpu->r++; \
  set_flag(&cpu->f, FLAG_Z, (cpu->r == 0)); \
}

#define DECr(r) { \
  set_flag(&cpu->f, FLAG_N, 1); \
  set_flag(&cpu->f, FLAG_H, ((cpu->r & 0x0F) == 0x00)); \
  cpu->r--; \
  set_flag(&cpu->f, FLAG_Z, (cpu->r == 0)); \
}

static void inc_b(SM83 *cpu) { INCr(b); }
static void inc_c(SM83 *cpu) { INCr(c); }
static void inc_d(SM83 *cpu) { INCr(d); }
static void inc_e(SM83 *cpu) { INCr(e); }
static void inc_h(SM83 *cpu) { INCr(h); }
static void inc_l(SM83 *cpu) { INCr(l); }
static void inc_a(SM83 *cpu) { INCr(a); }
static void inci_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  set_flag(&cpu->f, FLAG_N, 0);
  set_flag(&cpu->f, FLAG_H, ((value & 0x0F) == 0x0F));
  value++;
  set_flag(&cpu->f, FLAG_Z, (value == 0));
  cpu->write(cpu->hl, value);
}

static void dec_b(SM83 *cpu) { DECr(b); }
static void dec_c(SM83 *cpu) { DECr(c); }
static void dec_d(SM83 *cpu) { DECr(d); }
static void dec_e(SM83 *cpu) { DECr(e); }
static void dec_h(SM83 *cpu) { DECr(h); }
static void dec_l(SM83 *cpu) { DECr(l); }
static void dec_a(SM83 *cpu) { DECr(a); }
static void deci_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  set_flag(&cpu->f, FLAG_N, 1);
  set_flag(&cpu->f, FLAG_H, ((value & 0x0F) == 0x00));
  value--;
  set_flag(&cpu->f, FLAG_Z, (value == 0));
  cpu->write(cpu->hl, value);
}


// ** 16-bit load instructions **
#define LDrrnn(rr) { \
  uint16_t low = cpu->read(cpu->pc++); \
  uint16_t high = cpu->read(cpu->pc++); \
  uint16_t nn = (uint16_t)(high << 8) | low; \
  cpu->rr = nn; \
}

#define PUSH(rr) { \
  cpu->write(--cpu->sp, (uint8_t)((cpu->rr >> 8) & 0xFF)); \
  cpu->write(--cpu->sp, (uint8_t)(cpu->rr & 0xFF)); \
}

#define POP(rr) { \
  uint16_t low = cpu->read(cpu->sp++); \
  uint16_t high = cpu->read(cpu->sp++); \
  cpu->rr = (uint16_t)(high << 8) | low; \
}

static void ld_bc_nn(SM83 *cpu) { LDrrnn(bc); }
static void ld_de_nn(SM83 *cpu) { LDrrnn(de); }
static void ld_hl_nn(SM83 *cpu) { LDrrnn(hl); }
static void ld_sp_nn(SM83 *cpu) { LDrrnn(sp); }
static void ld_nn_sp(SM83 *cpu) {
  uint16_t low = cpu->read(cpu->pc++);
  uint16_t high = cpu->read(cpu->pc++);
  uint16_t nn = (uint16_t)(high << 8) | low;
  cpu->write(nn++, (uint8_t)(cpu->sp & 0xFF));
  cpu->write(nn, (uint8_t)((cpu->sp >> 8) & 0xFF));
}
static void ld_sp_hl(SM83 *cpu) { cpu->sp = cpu->hl; }
static void push_bc(SM83 *cpu) { PUSH(bc); }
static void push_de(SM83 *cpu) { PUSH(de); }
static void push_hl(SM83 *cpu) { PUSH(hl); }
static void push_af(SM83 *cpu) { PUSH(af); }
static void pop_bc(SM83 *cpu) { POP(bc); }
static void pop_de(SM83 *cpu) { POP(de); }
static void pop_hl(SM83 *cpu) { POP(hl); }
static void pop_af(SM83 *cpu) { POP(af); cpu->f &= 0xF0; }
static void ld_hl_sp_e(SM83 *cpu) {
  int8_t e = (int8_t)cpu->read(cpu->pc++);
  uint16_t result = (uint16_t)(cpu->sp + e);
  set_flag(&cpu->f, FLAG_Z, 0);
  set_flag(&cpu->f, FLAG_N, 0);
  set_flag(&cpu->f, FLAG_H, (((cpu->sp & 0x0F) + (e & 0x0F)) & 0x10) == 0x10);
  set_flag(&cpu->f, FLAG_C, (((cpu->sp & 0xFF) + (e & 0xFF)) & 0x100) == 0x100);
  cpu->hl = result;
}


// ** 16-bit arithmetic instructions **
#define ADDHLrr(rr) { \
  uint32_t result = (uint32_t)cpu->hl + (uint32_t)cpu->rr; \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, (((cpu->hl & 0x0FFF) + (cpu->rr & 0x0FFF)) & 0x1000) == 0x1000); \
  set_flag(&cpu->f, FLAG_C, (result > 0xFFFF)); \
  cpu->hl = (uint16_t)(result & 0xFFFF); \
}

static void inc_bc(SM83 *cpu) { cpu->bc++; }
static void inc_de(SM83 *cpu) { cpu->de++; }
static void inc_hl(SM83 *cpu) { cpu->hl++; }
static void inc_sp(SM83 *cpu) { cpu->sp++; }
static void dec_bc(SM83 *cpu) { cpu->bc--; }
static void dec_de(SM83 *cpu) { cpu->de--; }
static void dec_hl(SM83 *cpu) { cpu->hl--; }
static void dec_sp(SM83 *cpu) { cpu->sp--; }
static void add_hl_bc(SM83 *cpu) { ADDHLrr(bc); }
static void add_hl_de(SM83 *cpu) { ADDHLrr(de); }
static void add_hl_hl(SM83 *cpu) { ADDHLrr(hl); }
static void add_hl_sp(SM83 *cpu) { ADDHLrr(sp); }
static void add_sp_e(SM83 *cpu) {
  int8_t e = (int8_t)cpu->read(cpu->pc++);
  uint16_t result = (uint16_t)(cpu->sp + e);
  set_flag(&cpu->f, FLAG_Z, 0);
  set_flag(&cpu->f, FLAG_N, 0);
  set_flag(&cpu->f, FLAG_H, (((cpu->sp & 0x0F) + (e & 0x0F)) & 0x10) == 0x10);
  set_flag(&cpu->f, FLAG_C, (((cpu->sp & 0xFF) + (e & 0xFF)) & 0x100) == 0x100);
  cpu->sp = result;
}

// ** Control instructions **
static void jp_nn(SM83 *cpu) {
  uint16_t low = cpu->read(cpu->pc++);
  uint16_t high = cpu->read(cpu->pc++);
  cpu->pc = (uint16_t)(high << 8) | low;
}
static void jp_hl(SM83 *cpu) { cpu->pc = cpu->hl; }

#define JPccnn(cc) { \
  uint16_t low = cpu->read(cpu->pc++); \
  uint16_t high = cpu->read(cpu->pc++); \
  uint16_t nn = (uint16_t)(high << 8) | low; \
  if (cc) { \
    cpu->pc = nn; \
    cpu->t = (uint8_t)(cpu->t + 4); \
  } \
}

static void jp_nz_nn(SM83 *cpu) { JPccnn(!get_flag(&cpu->f, FLAG_Z)); }
static void jp_z_nn(SM83 *cpu) { JPccnn(get_flag(&cpu->f, FLAG_Z)); }
static void jp_nc_nn(SM83 *cpu) { JPccnn(!get_flag(&cpu->f, FLAG_C)); }
static void jp_c_nn(SM83 *cpu) { JPccnn(get_flag(&cpu->f, FLAG_C)); }

#define JRcce(cc) { \
  int8_t e = (int8_t)cpu->read(cpu->pc++); \
  if (cc) { \
    cpu->pc = (uint16_t)((int)cpu->pc + e); \
    cpu->t = (uint8_t)(cpu->t + 4); \
  } \
}

static void jr_e(SM83 *cpu) {
  int8_t e = (int8_t)cpu->read(cpu->pc++);
  cpu->pc = (uint16_t)((int)cpu->pc + e); \
}
static void jr_nz_e(SM83 *cpu) { JRcce(!get_flag(&cpu->f, FLAG_Z)); }
static void jr_z_e(SM83 *cpu) { JRcce(get_flag(&cpu->f, FLAG_Z)); }
static void jr_nc_e(SM83 *cpu) { JRcce(!get_flag(&cpu->f, FLAG_C)); }
static void jr_c_e(SM83 *cpu) { JRcce(get_flag(&cpu->f, FLAG_C)); }

#define CALL(addr) { \
  cpu->write(--cpu->sp, (uint8_t)((cpu->pc >> 8) & 0xFF)); \
  cpu->write(--cpu->sp, (uint8_t)(cpu->pc & 0xFF)); \
  cpu->pc = addr; \
}
#define CALLccnn(cc) { \
  uint16_t low = cpu->read(cpu->pc++); \
  uint16_t high = cpu->read(cpu->pc++); \
  uint16_t nn = (uint16_t)(high << 8) | low; \
  if (cc) { \
    CALL(nn); \
    cpu->t = (uint8_t)(cpu->t + 12); \
  } \
}

static void call_nn(SM83 *cpu) {
  uint16_t low = cpu->read(cpu->pc++);
  uint16_t high = cpu->read(cpu->pc++);
  uint16_t nn = (uint16_t)(high << 8) | low;
  CALL(nn);
}
static void call_nz_nn(SM83 *cpu) { CALLccnn(!get_flag(&cpu->f, FLAG_Z)); }
static void call_z_nn(SM83 *cpu) { CALLccnn(get_flag(&cpu->f, FLAG_Z)); }
static void call_nc_nn(SM83 *cpu) { CALLccnn(!get_flag(&cpu->f, FLAG_C)); }
static void call_c_nn(SM83 *cpu) { CALLccnn(get_flag(&cpu->f, FLAG_C)); }

#define RET() { \
  uint16_t low = cpu->read(cpu->sp++); \
  uint16_t high = cpu->read(cpu->sp++); \
  cpu->pc = (uint16_t)(high << 8) | low; \
}
#define RETcc(cc) { \
  if (cc) { \
    RET(); \
    cpu->t = (uint8_t)(cpu->t + 12); \
  } \
}

static void ret(SM83 *cpu) { RET(); }
static void ret_nz(SM83 *cpu) { RETcc(!get_flag(&cpu->f, FLAG_Z)); }
static void ret_z(SM83 *cpu) { RETcc(get_flag(&cpu->f, FLAG_Z)); }
static void ret_nc(SM83 *cpu) { RETcc(!get_flag(&cpu->f, FLAG_C)); }
static void ret_c(SM83 *cpu) { RETcc(get_flag(&cpu->f, FLAG_C)); }
static void reti(SM83 *cpu) {
  RET();
  // cpu->ime = 1; TODO TODO TODO
}
static void rst_00(SM83 *cpu) { CALL(0x00); }
static void rst_08(SM83 *cpu) { CALL(0x08); }
static void rst_10(SM83 *cpu) { CALL(0x10); }
static void rst_18(SM83 *cpu) { CALL(0x18); }
static void rst_20(SM83 *cpu) { CALL(0x20); }
static void rst_28(SM83 *cpu) { CALL(0x28); }
static void rst_30(SM83 *cpu) { CALL(0x30); }
static void rst_38(SM83 *cpu) { CALL(0x38); }

// ** Rotate, shift, and bit instructions **
#define RLCr(r) { \
  uint8_t carry = (r >> 7) & 1; \
  r = (uint8_t)((r << 1) | carry); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
  set_flag(&cpu->f, FLAG_C, carry); \
}

#define RRCr(r) { \
  uint8_t carry = r & 1; \
  r = (uint8_t)((r >> 1) | (carry << 7)); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
  set_flag(&cpu->f, FLAG_C, carry); \
}

#define RLr(r) { \
  uint8_t carry = (r >> 7) & 1; \
  r = (uint8_t)((r << 1) | get_flag(&cpu->f, FLAG_C)); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
  set_flag(&cpu->f, FLAG_C, carry); \
}

#define RRr(r) { \
  uint8_t carry = r & 1; \
  r = (uint8_t)((r >> 1) | (get_flag(&cpu->f, FLAG_C) << 7)); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
  set_flag(&cpu->f, FLAG_C, carry); \
}

#define SLAr(r) { \
  set_flag(&cpu->f, FLAG_C, (r >> 7) & 1); \
  r = (uint8_t)(r << 1); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
}

#define SRAr(r) { \
  set_flag(&cpu->f, FLAG_C, r & 1); \
  r = (uint8_t)((r >> 1) | (r & 0x80)); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
}

#define SWAPr(r) { \
  r = (uint8_t)((r << 4) | (r >> 4)); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
  set_flag(&cpu->f, FLAG_C, 0); \
}

#define SRLr(r) { \
  set_flag(&cpu->f, FLAG_C, r & 1); \
  r = (uint8_t)(r >> 1); \
  set_flag(&cpu->f, FLAG_Z, (r == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 0); \
}

#define BITb(b, r) { \
  set_flag(&cpu->f, FLAG_Z, ((r & (1 << b)) == 0)); \
  set_flag(&cpu->f, FLAG_N, 0); \
  set_flag(&cpu->f, FLAG_H, 1); \
}

#define RESb(b, r) { r &= (uint8_t)~(1 << b); }
#define SETb(b, r) { r |= (1 << b); }

static void rlca(SM83 *cpu) { RLCr(cpu->a); set_flag(&cpu->f, FLAG_Z, 0); }
static void rrca(SM83 *cpu) { RRCr(cpu->a); set_flag(&cpu->f, FLAG_Z, 0); }
static void rla(SM83 *cpu) { RLr(cpu->a); set_flag(&cpu->f, FLAG_Z, 0); }
static void rra(SM83 *cpu) { RRr(cpu->a); set_flag(&cpu->f, FLAG_Z, 0); }

static void rlc_b(SM83 *cpu) { RLCr(cpu->b); }
static void rlc_c(SM83 *cpu) { RLCr(cpu->c); }
static void rlc_d(SM83 *cpu) { RLCr(cpu->d); }
static void rlc_e(SM83 *cpu) { RLCr(cpu->e); }
static void rlc_h(SM83 *cpu) { RLCr(cpu->h); }
static void rlc_l(SM83 *cpu) { RLCr(cpu->l); }
static void rlc_a(SM83 *cpu) { RLCr(cpu->a); }
static void rlc_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RLCr(value);
  cpu->write(cpu->hl, value);
}

static void rrc_b(SM83 *cpu) { RRCr(cpu->b); }
static void rrc_c(SM83 *cpu) { RRCr(cpu->c); }
static void rrc_d(SM83 *cpu) { RRCr(cpu->d); }
static void rrc_e(SM83 *cpu) { RRCr(cpu->e); }
static void rrc_h(SM83 *cpu) { RRCr(cpu->h); }
static void rrc_l(SM83 *cpu) { RRCr(cpu->l); }
static void rrc_a(SM83 *cpu) { RRCr(cpu->a); }
static void rrc_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RRCr(value);
  cpu->write(cpu->hl, value);
}

static void rl_b(SM83 *cpu) { RLr(cpu->b); }
static void rl_c(SM83 *cpu) { RLr(cpu->c); }
static void rl_d(SM83 *cpu) { RLr(cpu->d); }
static void rl_e(SM83 *cpu) { RLr(cpu->e); }
static void rl_h(SM83 *cpu) { RLr(cpu->h); }
static void rl_l(SM83 *cpu) { RLr(cpu->l); }
static void rl_a(SM83 *cpu) { RLr(cpu->a); }
static void rl_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RLr(value);
  cpu->write(cpu->hl, value);
}

static void rr_b(SM83 *cpu) { RRr(cpu->b); }
static void rr_c(SM83 *cpu) { RRr(cpu->c); }
static void rr_d(SM83 *cpu) { RRr(cpu->d); }
static void rr_e(SM83 *cpu) { RRr(cpu->e); }
static void rr_h(SM83 *cpu) { RRr(cpu->h); }
static void rr_l(SM83 *cpu) { RRr(cpu->l); }
static void rr_a(SM83 *cpu) { RRr(cpu->a); }
static void rr_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RRr(value);
  cpu->write(cpu->hl, value);
}

static void sla_b(SM83 *cpu) { SLAr(cpu->b); }
static void sla_c(SM83 *cpu) { SLAr(cpu->c); }
static void sla_d(SM83 *cpu) { SLAr(cpu->d); }
static void sla_e(SM83 *cpu) { SLAr(cpu->e); }
static void sla_h(SM83 *cpu) { SLAr(cpu->h); }
static void sla_l(SM83 *cpu) { SLAr(cpu->l); }
static void sla_a(SM83 *cpu) { SLAr(cpu->a); }
static void sla_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SLAr(value);
  cpu->write(cpu->hl, value);
}

static void sra_b(SM83 *cpu) { SRAr(cpu->b); }
static void sra_c(SM83 *cpu) { SRAr(cpu->c); }
static void sra_d(SM83 *cpu) { SRAr(cpu->d); }
static void sra_e(SM83 *cpu) { SRAr(cpu->e); }
static void sra_h(SM83 *cpu) { SRAr(cpu->h); }
static void sra_l(SM83 *cpu) { SRAr(cpu->l); }
static void sra_a(SM83 *cpu) { SRAr(cpu->a); }
static void sra_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SRAr(value);
  cpu->write(cpu->hl, value);
}

static void swap_b(SM83 *cpu) { SWAPr(cpu->b); }
static void swap_c(SM83 *cpu) { SWAPr(cpu->c); }
static void swap_d(SM83 *cpu) { SWAPr(cpu->d); }
static void swap_e(SM83 *cpu) { SWAPr(cpu->e); }
static void swap_h(SM83 *cpu) { SWAPr(cpu->h); }
static void swap_l(SM83 *cpu) { SWAPr(cpu->l); }
static void swap_a(SM83 *cpu) { SWAPr(cpu->a); }
static void swap_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SWAPr(value);
  cpu->write(cpu->hl, value);
}

static void srl_b(SM83 *cpu) { SRLr(cpu->b); }
static void srl_c(SM83 *cpu) { SRLr(cpu->c); }
static void srl_d(SM83 *cpu) { SRLr(cpu->d); }
static void srl_e(SM83 *cpu) { SRLr(cpu->e); }
static void srl_h(SM83 *cpu) { SRLr(cpu->h); }
static void srl_l(SM83 *cpu) { SRLr(cpu->l); }
static void srl_a(SM83 *cpu) { SRLr(cpu->a); }
static void srl_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SRLr(value);
  cpu->write(cpu->hl, value);
}

static void bit_0_b(SM83 *cpu) { BITb(0, cpu->b); }
static void bit_0_c(SM83 *cpu) { BITb(0, cpu->c); }
static void bit_0_d(SM83 *cpu) { BITb(0, cpu->d); }
static void bit_0_e(SM83 *cpu) { BITb(0, cpu->e); }
static void bit_0_h(SM83 *cpu) { BITb(0, cpu->h); }
static void bit_0_l(SM83 *cpu) { BITb(0, cpu->l); }
static void bit_0_a(SM83 *cpu) { BITb(0, cpu->a); }
static void bit_0_hl(SM83 *cpu) { BITb(0, cpu->read(cpu->hl)); }

static void bit_1_b(SM83 *cpu) { BITb(1, cpu->b); }
static void bit_1_c(SM83 *cpu) { BITb(1, cpu->c); }
static void bit_1_d(SM83 *cpu) { BITb(1, cpu->d); }
static void bit_1_e(SM83 *cpu) { BITb(1, cpu->e); }
static void bit_1_h(SM83 *cpu) { BITb(1, cpu->h); }
static void bit_1_l(SM83 *cpu) { BITb(1, cpu->l); }
static void bit_1_a(SM83 *cpu) { BITb(1, cpu->a); }
static void bit_1_hl(SM83 *cpu) { BITb(1, cpu->read(cpu->hl)); }

static void bit_2_b(SM83 *cpu) { BITb(2, cpu->b); }
static void bit_2_c(SM83 *cpu) { BITb(2, cpu->c); }
static void bit_2_d(SM83 *cpu) { BITb(2, cpu->d); }
static void bit_2_e(SM83 *cpu) { BITb(2, cpu->e); }
static void bit_2_h(SM83 *cpu) { BITb(2, cpu->h); }
static void bit_2_l(SM83 *cpu) { BITb(2, cpu->l); }
static void bit_2_a(SM83 *cpu) { BITb(2, cpu->a); }
static void bit_2_hl(SM83 *cpu) { BITb(2, cpu->read(cpu->hl)); }

static void bit_3_b(SM83 *cpu) { BITb(3, cpu->b); }
static void bit_3_c(SM83 *cpu) { BITb(3, cpu->c); }
static void bit_3_d(SM83 *cpu) { BITb(3, cpu->d); }
static void bit_3_e(SM83 *cpu) { BITb(3, cpu->e); }
static void bit_3_h(SM83 *cpu) { BITb(3, cpu->h); }
static void bit_3_l(SM83 *cpu) { BITb(3, cpu->l); }
static void bit_3_a(SM83 *cpu) { BITb(3, cpu->a); }
static void bit_3_hl(SM83 *cpu) { BITb(3, cpu->read(cpu->hl)); }

static void bit_4_b(SM83 *cpu) { BITb(4, cpu->b); }
static void bit_4_c(SM83 *cpu) { BITb(4, cpu->c); }
static void bit_4_d(SM83 *cpu) { BITb(4, cpu->d); }
static void bit_4_e(SM83 *cpu) { BITb(4, cpu->e); }
static void bit_4_h(SM83 *cpu) { BITb(4, cpu->h); }
static void bit_4_l(SM83 *cpu) { BITb(4, cpu->l); }
static void bit_4_a(SM83 *cpu) { BITb(4, cpu->a); }
static void bit_4_hl(SM83 *cpu) { BITb(4, cpu->read(cpu->hl)); }

static void bit_5_b(SM83 *cpu) { BITb(5, cpu->b); }
static void bit_5_c(SM83 *cpu) { BITb(5, cpu->c); }
static void bit_5_d(SM83 *cpu) { BITb(5, cpu->d); }
static void bit_5_e(SM83 *cpu) { BITb(5, cpu->e); }
static void bit_5_h(SM83 *cpu) { BITb(5, cpu->h); }
static void bit_5_l(SM83 *cpu) { BITb(5, cpu->l); }
static void bit_5_a(SM83 *cpu) { BITb(5, cpu->a); }
static void bit_5_hl(SM83 *cpu) { BITb(5, cpu->read(cpu->hl)); }

static void bit_6_b(SM83 *cpu) { BITb(6, cpu->b); }
static void bit_6_c(SM83 *cpu) { BITb(6, cpu->c); }
static void bit_6_d(SM83 *cpu) { BITb(6, cpu->d); }
static void bit_6_e(SM83 *cpu) { BITb(6, cpu->e); }
static void bit_6_h(SM83 *cpu) { BITb(6, cpu->h); }
static void bit_6_l(SM83 *cpu) { BITb(6, cpu->l); }
static void bit_6_a(SM83 *cpu) { BITb(6, cpu->a); }
static void bit_6_hl(SM83 *cpu) { BITb(6, cpu->read(cpu->hl)); }

static void bit_7_b(SM83 *cpu) { BITb(7, cpu->b); }
static void bit_7_c(SM83 *cpu) { BITb(7, cpu->c); }
static void bit_7_d(SM83 *cpu) { BITb(7, cpu->d); }
static void bit_7_e(SM83 *cpu) { BITb(7, cpu->e); }
static void bit_7_h(SM83 *cpu) { BITb(7, cpu->h); }
static void bit_7_l(SM83 *cpu) { BITb(7, cpu->l); }
static void bit_7_a(SM83 *cpu) { BITb(7, cpu->a); }
static void bit_7_hl(SM83 *cpu) { BITb(7, cpu->read(cpu->hl)); }

static void res_0_b(SM83 *cpu) { RESb(0, cpu->b); }
static void res_0_c(SM83 *cpu) { RESb(0, cpu->c); }
static void res_0_d(SM83 *cpu) { RESb(0, cpu->d); }
static void res_0_e(SM83 *cpu) { RESb(0, cpu->e); }
static void res_0_h(SM83 *cpu) { RESb(0, cpu->h); }
static void res_0_l(SM83 *cpu) { RESb(0, cpu->l); }
static void res_0_a(SM83 *cpu) { RESb(0, cpu->a); }
static void res_0_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(0, value);
  cpu->write(cpu->hl, value);
}

static void res_1_b(SM83 *cpu) { RESb(1, cpu->b); }
static void res_1_c(SM83 *cpu) { RESb(1, cpu->c); }
static void res_1_d(SM83 *cpu) { RESb(1, cpu->d); }
static void res_1_e(SM83 *cpu) { RESb(1, cpu->e); }
static void res_1_h(SM83 *cpu) { RESb(1, cpu->h); }
static void res_1_l(SM83 *cpu) { RESb(1, cpu->l); }
static void res_1_a(SM83 *cpu) { RESb(1, cpu->a); }
static void res_1_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(1, value);
  cpu->write(cpu->hl, value);
}

static void res_2_b(SM83 *cpu) { RESb(2, cpu->b); }
static void res_2_c(SM83 *cpu) { RESb(2, cpu->c); }
static void res_2_d(SM83 *cpu) { RESb(2, cpu->d); }
static void res_2_e(SM83 *cpu) { RESb(2, cpu->e); }
static void res_2_h(SM83 *cpu) { RESb(2, cpu->h); }
static void res_2_l(SM83 *cpu) { RESb(2, cpu->l); }
static void res_2_a(SM83 *cpu) { RESb(2, cpu->a); }
static void res_2_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(2, value);
  cpu->write(cpu->hl, value);
}

static void res_3_b(SM83 *cpu) { RESb(3, cpu->b); }
static void res_3_c(SM83 *cpu) { RESb(3, cpu->c); }
static void res_3_d(SM83 *cpu) { RESb(3, cpu->d); }
static void res_3_e(SM83 *cpu) { RESb(3, cpu->e); }
static void res_3_h(SM83 *cpu) { RESb(3, cpu->h); }
static void res_3_l(SM83 *cpu) { RESb(3, cpu->l); }
static void res_3_a(SM83 *cpu) { RESb(3, cpu->a); }
static void res_3_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(3, value);
  cpu->write(cpu->hl, value);
}

static void res_4_b(SM83 *cpu) { RESb(4, cpu->b); }
static void res_4_c(SM83 *cpu) { RESb(4, cpu->c); }
static void res_4_d(SM83 *cpu) { RESb(4, cpu->d); }
static void res_4_e(SM83 *cpu) { RESb(4, cpu->e); }
static void res_4_h(SM83 *cpu) { RESb(4, cpu->h); }
static void res_4_l(SM83 *cpu) { RESb(4, cpu->l); }
static void res_4_a(SM83 *cpu) { RESb(4, cpu->a); }
static void res_4_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(4, value);
  cpu->write(cpu->hl, value);
}

static void res_5_b(SM83 *cpu) { RESb(5, cpu->b); }
static void res_5_c(SM83 *cpu) { RESb(5, cpu->c); }
static void res_5_d(SM83 *cpu) { RESb(5, cpu->d); }
static void res_5_e(SM83 *cpu) { RESb(5, cpu->e); }
static void res_5_h(SM83 *cpu) { RESb(5, cpu->h); }
static void res_5_l(SM83 *cpu) { RESb(5, cpu->l); }
static void res_5_a(SM83 *cpu) { RESb(5, cpu->a); }
static void res_5_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(5, value);
  cpu->write(cpu->hl, value);
}

static void res_6_b(SM83 *cpu) { RESb(6, cpu->b); }
static void res_6_c(SM83 *cpu) { RESb(6, cpu->c); }
static void res_6_d(SM83 *cpu) { RESb(6, cpu->d); }
static void res_6_e(SM83 *cpu) { RESb(6, cpu->e); }
static void res_6_h(SM83 *cpu) { RESb(6, cpu->h); }
static void res_6_l(SM83 *cpu) { RESb(6, cpu->l); }
static void res_6_a(SM83 *cpu) { RESb(6, cpu->a); }
static void res_6_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(6, value);
  cpu->write(cpu->hl, value);
}

static void res_7_b(SM83 *cpu) { RESb(7, cpu->b); }
static void res_7_c(SM83 *cpu) { RESb(7, cpu->c); }
static void res_7_d(SM83 *cpu) { RESb(7, cpu->d); }
static void res_7_e(SM83 *cpu) { RESb(7, cpu->e); }
static void res_7_h(SM83 *cpu) { RESb(7, cpu->h); }
static void res_7_l(SM83 *cpu) { RESb(7, cpu->l); }
static void res_7_a(SM83 *cpu) { RESb(7, cpu->a); }
static void res_7_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  RESb(7, value);
  cpu->write(cpu->hl, value);
}

static void set_0_b(SM83 *cpu) { SETb(0, cpu->b); }
static void set_0_c(SM83 *cpu) { SETb(0, cpu->c); }
static void set_0_d(SM83 *cpu) { SETb(0, cpu->d); }
static void set_0_e(SM83 *cpu) { SETb(0, cpu->e); }
static void set_0_h(SM83 *cpu) { SETb(0, cpu->h); }
static void set_0_l(SM83 *cpu) { SETb(0, cpu->l); }
static void set_0_a(SM83 *cpu) { SETb(0, cpu->a); }
static void set_0_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(0, value);
  cpu->write(cpu->hl, value);
}

static void set_1_b(SM83 *cpu) { SETb(1, cpu->b); }
static void set_1_c(SM83 *cpu) { SETb(1, cpu->c); }
static void set_1_d(SM83 *cpu) { SETb(1, cpu->d); }
static void set_1_e(SM83 *cpu) { SETb(1, cpu->e); }
static void set_1_h(SM83 *cpu) { SETb(1, cpu->h); }
static void set_1_l(SM83 *cpu) { SETb(1, cpu->l); }
static void set_1_a(SM83 *cpu) { SETb(1, cpu->a); }
static void set_1_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(1, value);
  cpu->write(cpu->hl, value);
}

static void set_2_b(SM83 *cpu) { SETb(2, cpu->b); }
static void set_2_c(SM83 *cpu) { SETb(2, cpu->c); }
static void set_2_d(SM83 *cpu) { SETb(2, cpu->d); }
static void set_2_e(SM83 *cpu) { SETb(2, cpu->e); }
static void set_2_h(SM83 *cpu) { SETb(2, cpu->h); }
static void set_2_l(SM83 *cpu) { SETb(2, cpu->l); }
static void set_2_a(SM83 *cpu) { SETb(2, cpu->a); }
static void set_2_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(2, value);
  cpu->write(cpu->hl, value);
}

static void set_3_b(SM83 *cpu) { SETb(3, cpu->b); }
static void set_3_c(SM83 *cpu) { SETb(3, cpu->c); }
static void set_3_d(SM83 *cpu) { SETb(3, cpu->d); }
static void set_3_e(SM83 *cpu) { SETb(3, cpu->e); }
static void set_3_h(SM83 *cpu) { SETb(3, cpu->h); }
static void set_3_l(SM83 *cpu) { SETb(3, cpu->l); }
static void set_3_a(SM83 *cpu) { SETb(3, cpu->a); }
static void set_3_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(3, value);
  cpu->write(cpu->hl, value);
}

static void set_4_b(SM83 *cpu) { SETb(4, cpu->b); }
static void set_4_c(SM83 *cpu) { SETb(4, cpu->c); }
static void set_4_d(SM83 *cpu) { SETb(4, cpu->d); }
static void set_4_e(SM83 *cpu) { SETb(4, cpu->e); }
static void set_4_h(SM83 *cpu) { SETb(4, cpu->h); }
static void set_4_l(SM83 *cpu) { SETb(4, cpu->l); }
static void set_4_a(SM83 *cpu) { SETb(4, cpu->a); }
static void set_4_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(4, value);
  cpu->write(cpu->hl, value);
}

static void set_5_b(SM83 *cpu) { SETb(5, cpu->b); }
static void set_5_c(SM83 *cpu) { SETb(5, cpu->c); }
static void set_5_d(SM83 *cpu) { SETb(5, cpu->d); }
static void set_5_e(SM83 *cpu) { SETb(5, cpu->e); }
static void set_5_h(SM83 *cpu) { SETb(5, cpu->h); }
static void set_5_l(SM83 *cpu) { SETb(5, cpu->l); }
static void set_5_a(SM83 *cpu) { SETb(5, cpu->a); }
static void set_5_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(5, value);
  cpu->write(cpu->hl, value);
}

static void set_6_b(SM83 *cpu) { SETb(6, cpu->b); }
static void set_6_c(SM83 *cpu) { SETb(6, cpu->c); }
static void set_6_d(SM83 *cpu) { SETb(6, cpu->d); }
static void set_6_e(SM83 *cpu) { SETb(6, cpu->e); }
static void set_6_h(SM83 *cpu) { SETb(6, cpu->h); }
static void set_6_l(SM83 *cpu) { SETb(6, cpu->l); }
static void set_6_a(SM83 *cpu) { SETb(6, cpu->a); }
static void set_6_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(6, value);
  cpu->write(cpu->hl, value);
}

static void set_7_b(SM83 *cpu) { SETb(7, cpu->b); }
static void set_7_c(SM83 *cpu) { SETb(7, cpu->c); }
static void set_7_d(SM83 *cpu) { SETb(7, cpu->d); }
static void set_7_e(SM83 *cpu) { SETb(7, cpu->e); }
static void set_7_h(SM83 *cpu) { SETb(7, cpu->h); }
static void set_7_l(SM83 *cpu) { SETb(7, cpu->l); }
static void set_7_a(SM83 *cpu) { SETb(7, cpu->a); }
static void set_7_hl(SM83 *cpu) {
  uint8_t value = cpu->read(cpu->hl);
  SETb(7, value);
  cpu->write(cpu->hl, value);
}

// ** Prefix CB **
static void cb(SM83 *cpu) { (void)(cpu); }

// ** Instruction tables **
static const SM83Instruction instructions[0x100] = {
  { "NOP", nop, 1, 4 },
  { "LD BC, 0x%04X", ld_bc_nn, 3, 12 },
  { "LD [BC], A", ldi_bc_a, 1, 8 },
  { "INC BC", inc_bc, 1, 8 },
  { "INC B", inc_b, 1, 4 },
  { "DEC B", dec_b, 1, 4 },
  { "LD B, 0x%02X", ld_b_n, 2, 8 },
  { "RLCA", rlca, 1, 4 },
  { "LD [0x%04X], SP", ld_nn_sp, 3, 20 },
  { "ADD HL, BC", add_hl_bc, 1, 8 },
  { "LD A, [BC]", ldi_a_bc, 1, 8 },
  { "DEC BC", dec_bc, 1, 8 },
  { "INC C", inc_c, 1, 4 },
  { "DEC C", dec_c, 1, 4 },
  { "LD C, 0x%02X", ld_c_n, 2, 8 },
  { "RRCA", rrca, 1, 4 },
  { "STOP", stop, 2, 4 },
  { "LD DE, 0x%04X", ld_de_nn, 3, 12 },
  { "LD [DE], A", ldi_de_a, 1, 8 },
  { "INC DE", inc_de, 1, 8 },
  { "INC D", inc_d, 1, 4 },
  { "DEC D", dec_d, 1, 4 },
  { "LD D, 0x%02X", ld_d_n, 2, 8 },
  { "RLA", rla, 1, 4 },
  { "JR 0x%02X", jr_e, 2, 12 },
  { "ADD HL, DE", add_hl_de, 1, 8 },
  { "LD A, [DE]", ldi_a_de, 1, 8 },
  { "DEC DE", dec_de, 1, 8 },
  { "INC E", inc_e, 1, 4 },
  { "DEC E", dec_e, 1, 4 },
  { "LD E, 0x%02X", ld_e_n, 2, 8 },
  { "RRA", rra, 1, 4 },
  { "JR NZ, 0x%02X", jr_nz_e, 1, 8 }, // Note that it will add 1 more cycle if condition
  { "LD HL, 0x%04X", ld_hl_nn, 3, 12 },
  { "LD [HL+], A", ldi_hlp_a, 1, 8 },
  { "INC HL", inc_hl, 1, 8 },
  { "INC H", inc_h, 1, 4 },
  { "DEC H", dec_h, 1, 4 },
  { "LD H, 0x%02X", ld_h_n, 2, 8 },
  { "DAA", daa, 1, 4 },
  { "JR Z, 0x%02X", jr_z_e, 1, 8 },
  { "ADD HL, HL", add_hl_hl, 1, 8 },
  { "LD A, [HL+]", ld_a_hlp, 1, 8 },
  { "DEC HL", dec_hl, 1, 8 },
  { "INC L", inc_l, 1, 4 },
  { "DEC L", dec_l, 1, 4 },
  { "LD L, 0x%02X", ld_l_n, 2, 8 },
  { "CPL", cpl, 1, 4 },
  { "JR NC, 0x%02X", jr_nc_e, 1, 8 },
  { "LD SP, 0x%04X", ld_sp_nn, 3, 12 },
  { "LD [HL-], A", ldi_hlm_a, 1, 8 },
  { "INC SP", inc_sp, 1, 8 },
  { "INC [HL]", inci_hl, 1, 12 },
  { "DEC [HL]", deci_hl, 1, 12 },
  { "LD [HL], 0x%02X", ldi_hl_n, 2, 12 },
  { "SCF", scf, 1, 4 },
  { "JR C, 0x%02X", jr_c_e, 1, 8 },
  { "ADD HL, SP", add_hl_sp, 1, 8 },
  { "LD A, [HL-]", ld_a_hlm, 1, 8 },
  { "DEC SP", dec_sp, 1, 8 },
  { "INC A", inc_a, 1, 4 },
  { "DEC A", dec_a, 1, 4 },
  { "LD A, 0x%02X", ld_a_n, 2, 8 },
  { "CCF", ccf, 1, 4 },
  { "LD B, B", ld_b_b, 1, 4 },
  { "LD B, C", ld_b_c, 1, 4 },
  { "LD B, D", ld_b_d, 1, 4 },
  { "LD B, E", ld_b_e, 1, 4 },
  { "LD B, H", ld_b_h, 1, 4 },
  { "LD B, L", ld_b_l, 1, 4 },
  { "LD B, [HL]", ld_b_hl, 1, 8 },
  { "LD B, A", ld_b_a, 1, 4 },
  { "LD C, B", ld_c_b, 1, 4 },
  { "LD C, C", ld_c_c, 1, 4 },
  { "LD C, D", ld_c_d, 1, 4 },
  { "LD C, E", ld_c_e, 1, 4 },
  { "LD C, H", ld_c_h, 1, 4 },
  { "LD C, L", ld_c_l, 1, 4 },
  { "LD C, [HL]", ld_c_hl, 1, 8 },
  { "LD C, A", ld_c_a, 1, 4 },
  { "LD D, B", ld_d_b, 1, 4 },
  { "LD D, C", ld_d_c, 1, 4 },
  { "LD D, D", ld_d_d, 1, 4 },
  { "LD D, E", ld_d_e, 1, 4 },
  { "LD D, H", ld_d_h, 1, 4 },
  { "LD D, L", ld_d_l, 1, 4 },
  { "LD D, [HL]", ld_d_hl, 1, 8 },
  { "LD D, A", ld_d_a, 1, 4 },
  { "LD E, B", ld_e_b, 1, 4 },
  { "LD E, C", ld_e_c, 1, 4 },
  { "LD E, D", ld_e_d, 1, 4 },
  { "LD E, E", ld_e_e, 1, 4 },
  { "LD E, H", ld_e_h, 1, 4 },
  { "LD E, L", ld_e_l, 1, 4 },
  { "LD E, [HL]", ld_e_hl, 1, 8 },
  { "LD E, A", ld_e_a, 1, 4 },
  { "LD H, B", ld_h_b, 1, 4 },
  { "LD H, C", ld_h_c, 1, 4 },
  { "LD H, D", ld_h_d, 1, 4 },
  { "LD H, E", ld_h_e, 1, 4 },
  { "LD H, H", ld_h_h, 1, 4 },
  { "LD H, L", ld_h_l, 1, 4 },
  { "LD H, [HL]", ld_h_hl, 1, 8 },
  { "LD H, A", ld_h_a, 1, 4 },
  { "LD L, B", ld_l_b, 1, 4 },
  { "LD L, C", ld_l_c, 1, 4 },
  { "LD L, D", ld_l_d, 1, 4 },
  { "LD L, E", ld_l_e, 1, 4 },
  { "LD L, H", ld_l_h, 1, 4 },
  { "LD L, L", ld_l_l, 1, 4 },
  { "LD L, [HL]", ld_l_hl, 1, 8 },
  { "LD L, A", ld_l_a, 1, 4 },
  { "LD [HL], B", ldi_hl_b, 1, 8 },
  { "LD [HL], C", ldi_hl_c, 1, 8 },
  { "LD [HL], D", ldi_hl_d, 1, 8 },
  { "LD [HL], E", ldi_hl_e, 1, 8 },
  { "LD [HL], H", ldi_hl_h, 1, 8 },
  { "LD [HL], L", ldi_hl_l, 1, 8 },
  { "HALT", halt, 1, 4 },
  { "LD [HL], A", ldi_hl_a, 1, 8 },
  { "LD A, B", ld_a_b, 1, 4 },
  { "LD A, C", ld_a_c, 1, 4 },
  { "LD A, D", ld_a_d, 1, 4 },
  { "LD A, E", ld_a_e, 1, 4 },
  { "LD A, H", ld_a_h, 1, 4 },
  { "LD A, L", ld_a_l, 1, 4 },
  { "LD A, [HL]", ld_a_hl, 1, 8 },
  { "LD A, A", ld_a_a, 1, 4 },
  { "ADD A, B", add_a_b, 1, 4 },
  { "ADD A, C", add_a_c, 1, 4 },
  { "ADD A, D", add_a_d, 1, 4 },
  { "ADD A, E", add_a_e, 1, 4 },
  { "ADD A, H", add_a_h, 1, 4 },
  { "ADD A, L", add_a_l, 1, 4 },
  { "ADD A, [HL]", add_a_hl, 1, 8 },
  { "ADD A, A", add_a_a, 1, 4 },
  { "ADC A, B", adc_a_b, 1, 4 },
  { "ADC A, C", adc_a_c, 1, 4 },
  { "ADC A, D", adc_a_d, 1, 4 },
  { "ADC A, E", adc_a_e, 1, 4 },
  { "ADC A, H", adc_a_h, 1, 4 },
  { "ADC A, L", adc_a_l, 1, 4 },
  { "ADC A, [HL]", adc_a_hl, 1, 8 },
  { "ADC A, A", adc_a_a, 1, 4 },
  { "SUB B", sub_b, 1, 4 },
  { "SUB C", sub_c, 1, 4 },
  { "SUB D", sub_d, 1, 4 },
  { "SUB E", sub_e, 1, 4 },
  { "SUB H", sub_h, 1, 4 },
  { "SUB L", sub_l, 1, 4 },
  { "SUB [HL]", sub_hl, 1, 8 },
  { "SUB A", sub_a, 1, 4 },
  { "SBC A, B", sbc_a_b, 1, 4 },
  { "SBC A, C", sbc_a_c, 1, 4 },
  { "SBC A, D", sbc_a_d, 1, 4 },
  { "SBC A, E", sbc_a_e, 1, 4 },
  { "SBC A, H", sbc_a_h, 1, 4 },
  { "SBC A, L", sbc_a_l, 1, 4 },
  { "SBC A, [HL]", sbc_a_hl, 1, 8 },
  { "SBC A, A", sbc_a_a, 1, 4 },
  { "AND A, B", and_b, 1, 4 },
  { "AND A, C", and_c, 1, 4 },
  { "AND A, D", and_d, 1, 4 },
  { "AND A, E", and_e, 1, 4 },
  { "AND A, H", and_h, 1, 4 },
  { "AND A, L", and_l, 1, 4 },
  { "AND A, [HL]", and_hl, 1, 8 },
  { "AND A, A", and_a, 1, 4 },
  { "XOR A, B", xor_b, 1, 4 },
  { "XOR A, C", xor_c, 1, 4 },
  { "XOR A, D", xor_d, 1, 4 },
  { "XOR A, E", xor_e, 1, 4 },
  { "XOR A, H", xor_h, 1, 4 },
  { "XOR A, L", xor_l, 1, 4 },
  { "XOR A, [HL]", xor_hl, 1, 8 },
  { "XOR A, A", xor_a, 1, 4 },
  { "OR A, B", or_b, 1, 4 },
  { "OR A, C", or_c, 1, 4 },
  { "OR A, D", or_d, 1, 4 },
  { "OR A, E", or_e, 1, 4 },
  { "OR A, H", or_h, 1, 4 },
  { "OR A, L", or_l, 1, 4 },
  { "OR A, [HL]", or_hl, 1, 8 },
  { "OR A, A", or_a, 1, 4 },
  { "CP A, B", cp_b, 1, 4 },
  { "CP A, C", cp_c, 1, 4 },
  { "CP A, D", cp_d, 1, 4 },
  { "CP A, E", cp_e, 1, 4 },
  { "CP A, H", cp_h, 1, 4 },
  { "CP A, L", cp_l, 1, 4 },
  { "CP A, [HL]", cp_hl, 1, 8 },
  { "CP A, A", cp_a, 1, 4 },
  { "RET NZ", ret_nz, 1, 8 },
  { "POP BC", pop_bc, 1, 12 },
  { "JP NZ, 0x%04X", jp_nz_nn, 3, 12 },
  { "JP 0x%04X", jp_nn, 3, 16 },
  { "CALL NZ, 0x%04X", call_nz_nn, 3, 12 },
  { "PUSH BC", push_bc, 1, 16 },
  { "ADD A, 0x%02X", add_a_n, 2, 8 },
  { "RST 0x00", rst_00, 1, 16 },
  { "RET Z", ret_z, 1, 8 },
  { "RET", ret, 1, 16 },
  { "JP Z, 0x%04X", jp_z_nn, 3, 12 },
  { "CB", cb, 1, 4 },
  { "CALL Z, 0x%04X", call_z_nn, 3, 12 },
  { "CALL 0x%04X", call_nn, 3, 24 },
  { "ADC A, 0x%02X", adc_a_n, 2, 8 },
  { "RST 0x08", rst_08, 1, 16 },
  { "RET NC", ret_nc, 1, 8 },
  { "POP DE", pop_de, 1, 12 },
  { "JP NC, 0x%04X", jp_nc_nn, 3, 12 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "CALL NC, 0x%04X", call_nc_nn, 3, 12 },
  { "PUSH DE", push_de, 1, 16 },
  { "SUB A, 0x%02X", sub_n, 2, 8 },
  { "RST 0x10", rst_10, 1, 16 },
  { "RET C", ret_c, 1, 8 },
  { "RETI", reti, 1, 16 },
  { "JP C, 0x%04X", jp_c_nn, 1, 12 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "CALL C, 0x%04X", call_c_nn, 1, 12 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "SBC A, 0x%02X", sbc_a_n, 2, 8 },
  { "RST 0x18", rst_18, 1, 16 },
  { "LDH [0x%02X], A", ldh_n_a, 2, 12 },
  { "POP HL", pop_hl, 1, 12 },
  { "LD [C], A", ldh_c_a, 1, 8 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "PUSH HL", push_hl, 1, 16 },
  { "AND A, 0x%02X", and_n, 2, 8 },
  { "RST 0x20", rst_20, 1, 16 },
  { "ADD SP, 0x%02X", add_sp_e, 2, 16 },
  { "JP HL", jp_hl, 1, 4 },
  { "LD [0x%04X], A", ld_nn_a, 3, 16 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "XOR A, 0x%02X", xor_n, 2, 8 },
  { "RST 0x28", rst_28, 1, 16 },
  { "LDH A, [0x%02X]", ldh_a_n, 2, 12 },
  { "POP AF", pop_af, 1, 12 },
  { "LD A, [C]", ldh_a_c, 1, 8 },
  { "DI", di, 1, 4 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "PUSH AF", push_af, 1, 16 },
  { "OR A, 0x%02X", or_n, 2, 8 },
  { "RST 0x30", rst_30, 1, 16 },
  { "LD HL, SP+0x%02X", ld_hl_sp_e, 2, 12 },
  { "LD SP, HL", ld_sp_hl, 1, 8 },
  { "LD A, [0x%04X]", ld_a_nn, 3, 16 },
  { "EI", ei, 1, 4 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "INVALID", invalid, (uint8_t)-1, (uint8_t)-1 },
  { "CP 0x%02X", cp_n, 2, 8 },
  { "RST 0x38", rst_38, 1, 16 },
};

static const SM83Instruction cb_instructions[0x100] = {
  { "RLC B", rlc_b, 2, 8 },
  { "RLC C", rlc_c, 2, 8 },
  { "RLC D", rlc_d, 2, 8 },
  { "RLC E", rlc_e, 2, 8 },
  { "RLC H", rlc_h, 2, 8 },
  { "RLC L", rlc_l, 2, 8 },
  { "RLC [HL]", rlc_hl, 2, 16 },
  { "RLC A", rlc_a, 2, 8 },
  { "RRC B", rrc_b, 2, 8 },
  { "RRC C", rrc_c, 2, 8 },
  { "RRC D", rrc_d, 2, 8 },
  { "RRC E", rrc_e, 2, 8 },
  { "RRC H", rrc_h, 2, 8 },
  { "RRC L", rrc_l, 2, 8 },
  { "RRC [HL]", rrc_hl, 2, 16 },
  { "RRC A", rrc_a, 2, 8 },
  { "RL B", rl_b, 2, 8 },
  { "RL C", rl_c, 2, 8 },
  { "RL D", rl_d, 2, 8 },
  { "RL E", rl_e, 2, 8 },
  { "RL H", rl_h, 2, 8 },
  { "RL L", rl_l, 2, 8 },
  { "RL [HL]", rl_hl, 2, 16 },
  { "RL A", rl_a, 2, 8 },
  { "RR B", rr_b, 2, 8 },
  { "RR C", rr_c, 2, 8 },
  { "RR D", rr_d, 2, 8 },
  { "RR E", rr_e, 2, 8 },
  { "RR H", rr_h, 2, 8 },
  { "RR L", rr_l, 2, 8 },
  { "RR [HL]", rr_hl, 2, 16 },
  { "RR A", rr_a, 2, 8 },
  { "SLA B", sla_b, 2, 8 },
  { "SLA C", sla_c, 2, 8 },
  { "SLA D", sla_d, 2, 8 },
  { "SLA E", sla_e, 2, 8 },
  { "SLA H", sla_h, 2, 8 },
  { "SLA L", sla_l, 2, 8 },
  { "SLA [HL]", sla_hl, 2, 16 },
  { "SLA A", sla_a, 2, 8 },
  { "SRA B", sra_b, 2, 8 },
  { "SRA C", sra_c, 2, 8 },
  { "SRA D", sra_d, 2, 8 },
  { "SRA E", sra_e, 2, 8 },
  { "SRA H", sra_h, 2, 8 },
  { "SRA L", sra_l, 2, 8 },
  { "SRA [HL]", sra_hl, 2, 16 },
  { "SRA A", sra_a, 2, 8 },
  { "SWAP B", swap_b, 2, 8 },
  { "SWAP C", swap_c, 2, 8 },
  { "SWAP D", swap_d, 2, 8 },
  { "SWAP E", swap_e, 2, 8 },
  { "SWAP H", swap_h, 2, 8 },
  { "SWAP L", swap_l, 2, 8 },
  { "SWAP [HL]", swap_hl, 2, 16 },
  { "SWAP A", swap_a, 2, 8 },
  { "SRL B", srl_b, 2, 8 },
  { "SRL C", srl_c, 2, 8 },
  { "SRL D", srl_d, 2, 8 },
  { "SRL E", srl_e, 2, 8 },
  { "SRL H", srl_h, 2, 8 },
  { "SRL L", srl_l, 2, 8 },
  { "SRL [HL]", srl_hl, 2, 16 },
  { "SRL A", srl_a, 2, 8 },
  { "BIT 0, B", bit_0_b, 2, 8 },
  { "BIT 0, C", bit_0_c, 2, 8 },
  { "BIT 0, D", bit_0_d, 2, 8 },
  { "BIT 0, E", bit_0_e, 2, 8 },
  { "BIT 0, H", bit_0_h, 2, 8 },
  { "BIT 0, L", bit_0_l, 2, 8 },
  { "BIT 0, [HL]", bit_0_hl, 2, 12 },
  { "BIT 0, A", bit_0_a, 2, 8 },
  { "BIT 1, B", bit_1_b, 2, 8 },
  { "BIT 1, C", bit_1_c, 2, 8 },
  { "BIT 1, D", bit_1_d, 2, 8 },
  { "BIT 1, E", bit_1_e, 2, 8 },
  { "BIT 1, H", bit_1_h, 2, 8 },
  { "BIT 1, L", bit_1_l, 2, 8 },
  { "BIT 1, [HL]", bit_1_hl, 2, 12 },
  { "BIT 1, A", bit_1_a, 2, 8 },
  { "BIT 2, B", bit_2_b, 2, 8 },
  { "BIT 2, C", bit_2_c, 2, 8 },
  { "BIT 2, D", bit_2_d, 2, 8 },
  { "BIT 2, E", bit_2_e, 2, 8 },
  { "BIT 2, H", bit_2_h, 2, 8 },
  { "BIT 2, L", bit_2_l, 2, 8 },
  { "BIT 2, [HL]", bit_2_hl, 2, 12 },
  { "BIT 2, A", bit_2_a, 2, 8 },
  { "BIT 3, B", bit_3_b, 2, 8 },
  { "BIT 3, C", bit_3_c, 2, 8 },
  { "BIT 3, D", bit_3_d, 2, 8 },
  { "BIT 3, E", bit_3_e, 2, 8 },
  { "BIT 3, H", bit_3_h, 2, 8 },
  { "BIT 3, L", bit_3_l, 2, 8 },
  { "BIT 3, [HL]", bit_3_hl, 2, 12 },
  { "BIT 3, A", bit_3_a, 2, 8 },
  { "BIT 4, B", bit_4_b, 2, 8 },
  { "BIT 4, C", bit_4_c, 2, 8 },
  { "BIT 4, D", bit_4_d, 2, 8 },
  { "BIT 4, E", bit_4_e, 2, 8 },
  { "BIT 4, H", bit_4_h, 2, 8 },
  { "BIT 4, L", bit_4_l, 2, 8 },
  { "BIT 4, [HL]", bit_4_hl, 2, 12 },
  { "BIT 4, A", bit_4_a, 2, 8 },
  { "BIT 5, B", bit_5_b, 2, 8 },
  { "BIT 5, C", bit_5_c, 2, 8 },
  { "BIT 5, D", bit_5_d, 2, 8 },
  { "BIT 5, E", bit_5_e, 2, 8 },
  { "BIT 5, H", bit_5_h, 2, 8 },
  { "BIT 5, L", bit_5_l, 2, 8 },
  { "BIT 5, [HL]", bit_5_hl, 2, 12 },
  { "BIT 5, A", bit_5_a, 2, 8 },
  { "BIT 6, B", bit_6_b, 2, 8 },
  { "BIT 6, C", bit_6_c, 2, 8 },
  { "BIT 6, D", bit_6_d, 2, 8 },
  { "BIT 6, E", bit_6_e, 2, 8 },
  { "BIT 6, H", bit_6_h, 2, 8 },
  { "BIT 6, L", bit_6_l, 2, 8 },
  { "BIT 6, [HL]", bit_6_hl, 2, 12 },
  { "BIT 6, A", bit_6_a, 2, 8 },
  { "BIT 7, B", bit_7_b, 2, 8 },
  { "BIT 7, C", bit_7_c, 2, 8 },
  { "BIT 7, D", bit_7_d, 2, 8 },
  { "BIT 7, E", bit_7_e, 2, 8 },
  { "BIT 7, H", bit_7_h, 2, 8 },
  { "BIT 7, L", bit_7_l, 2, 8 },
  { "BIT 7, [HL]", bit_7_hl, 2, 12 },
  { "BIT 7, A", bit_7_a, 2, 8 },
  { "RES 0, B", res_0_b, 2, 8 },
  { "RES 0, C", res_0_c, 2, 8 },
  { "RES 0, D", res_0_d, 2, 8 },
  { "RES 0, E", res_0_e, 2, 8 },
  { "RES 0, H", res_0_h, 2, 8 },
  { "RES 0, L", res_0_l, 2, 8 },
  { "RES 0, [HL]", res_0_hl, 2, 16 },
  { "RES 0, A", res_0_a, 2, 8 },
  { "RES 1, B", res_1_b, 2, 8 },
  { "RES 1, C", res_1_c, 2, 8 },
  { "RES 1, D", res_1_d, 2, 8 },
  { "RES 1, E", res_1_e, 2, 8 },
  { "RES 1, H", res_1_h, 2, 8 },
  { "RES 1, L", res_1_l, 2, 8 },
  { "RES 1, [HL]", res_1_hl, 2, 16 },
  { "RES 1, A", res_1_a, 2, 8 },
  { "RES 2, B", res_2_b, 2, 8 },
  { "RES 2, C", res_2_c, 2, 8 },
  { "RES 2, D", res_2_d, 2, 8 },
  { "RES 2, E", res_2_e, 2, 8 },
  { "RES 2, H", res_2_h, 2, 8 },
  { "RES 2, L", res_2_l, 2, 8 },
  { "RES 2, [HL]", res_2_hl, 2, 16 },
  { "RES 2, A", res_2_a, 2, 8 },
  { "RES 3, B", res_3_b, 2, 8 },
  { "RES 3, C", res_3_c, 2, 8 },
  { "RES 3, D", res_3_d, 2, 8 },
  { "RES 3, E", res_3_e, 2, 8 },
  { "RES 3, H", res_3_h, 2, 8 },
  { "RES 3, L", res_3_l, 2, 8 },
  { "RES 3, [HL]", res_3_hl, 2, 16 },
  { "RES 3, A", res_3_a, 2, 8 },
  { "RES 4, B", res_4_b, 2, 8 },
  { "RES 4, C", res_4_c, 2, 8 },
  { "RES 4, D", res_4_d, 2, 8 },
  { "RES 4, E", res_4_e, 2, 8 },
  { "RES 4, H", res_4_h, 2, 8 },
  { "RES 4, L", res_4_l, 2, 8 },
  { "RES 4, [HL]", res_4_hl, 2, 16 },
  { "RES 4, A", res_4_a, 2, 8 },
  { "RES 5, B", res_5_b, 2, 8 },
  { "RES 5, C", res_5_c, 2, 8 },
  { "RES 5, D", res_5_d, 2, 8 },
  { "RES 5, E", res_5_e, 2, 8 },
  { "RES 5, H", res_5_h, 2, 8 },
  { "RES 5, L", res_5_l, 2, 8 },
  { "RES 5, [HL]", res_5_hl, 2, 16 },
  { "RES 5, A", res_5_a, 2, 8 },
  { "RES 6, B", res_6_b, 2, 8 },
  { "RES 6, C", res_6_c, 2, 8 },
  { "RES 6, D", res_6_d, 2, 8 },
  { "RES 6, E", res_6_e, 2, 8 },
  { "RES 6, H", res_6_h, 2, 8 },
  { "RES 6, L", res_6_l, 2, 8 },
  { "RES 6, [HL]", res_6_hl, 2, 16 },
  { "RES 6, A", res_6_a, 2, 8 },
  { "RES 7, B", res_7_b, 2, 8 },
  { "RES 7, C", res_7_c, 2, 8 },
  { "RES 7, D", res_7_d, 2, 8 },
  { "RES 7, E", res_7_e, 2, 8 },
  { "RES 7, H", res_7_h, 2, 8 },
  { "RES 7, L", res_7_l, 2, 8 },
  { "RES 7, [HL]", res_7_hl, 2, 16 },
  { "RES 7, A", res_7_a, 2, 8 },
  { "SET 0, B", set_0_b, 2, 8 },
  { "SET 0, C", set_0_c, 2, 8 },
  { "SET 0, D", set_0_d, 2, 8 },
  { "SET 0, E", set_0_e, 2, 8 },
  { "SET 0, H", set_0_h, 2, 8 },
  { "SET 0, L", set_0_l, 2, 8 },
  { "SET 0, [HL]", set_0_hl, 2, 16 },
  { "SET 0, A", set_0_a, 2, 8 },
  { "SET 1, B", set_1_b, 2, 8 },
  { "SET 1, C", set_1_c, 2, 8 },
  { "SET 1, D", set_1_d, 2, 8 },
  { "SET 1, E", set_1_e, 2, 8 },
  { "SET 1, H", set_1_h, 2, 8 },
  { "SET 1, L", set_1_l, 2, 8 },
  { "SET 1, [HL]", set_1_hl, 2, 16 },
  { "SET 1, A", set_1_a, 2, 8 },
  { "SET 2, B", set_2_b, 2, 8 },
  { "SET 2, C", set_2_c, 2, 8 },
  { "SET 2, D", set_2_d, 2, 8 },
  { "SET 2, E", set_2_e, 2, 8 },
  { "SET 2, H", set_2_h, 2, 8 },
  { "SET 2, L", set_2_l, 2, 8 },
  { "SET 2, [HL]", set_2_hl, 2, 16 },
  { "SET 2, A", set_2_a, 2, 8 },
  { "SET 3, B", set_3_b, 2, 8 },
  { "SET 3, C", set_3_c, 2, 8 },
  { "SET 3, D", set_3_d, 2, 8 },
  { "SET 3, E", set_3_e, 2, 8 },
  { "SET 3, H", set_3_h, 2, 8 },
  { "SET 3, L", set_3_l, 2, 8 },
  { "SET 3, [HL]", set_3_hl, 2, 16 },
  { "SET 3, A", set_3_a, 2, 8 },
  { "SET 4, B", set_4_b, 2, 8 },
  { "SET 4, C", set_4_c, 2, 8 },
  { "SET 4, D", set_4_d, 2, 8 },
  { "SET 4, E", set_4_e, 2, 8 },
  { "SET 4, H", set_4_h, 2, 8 },
  { "SET 4, L", set_4_l, 2, 8 },
  { "SET 4, [HL]", set_4_hl, 2, 16 },
  { "SET 4, A", set_4_a, 2, 8 },
  { "SET 5, B", set_5_b, 2, 8 },
  { "SET 5, C", set_5_c, 2, 8 },
  { "SET 5, D", set_5_d, 2, 8 },
  { "SET 5, E", set_5_e, 2, 8 },
  { "SET 5, H", set_5_h, 2, 8 },
  { "SET 5, L", set_5_l, 2, 8 },
  { "SET 5, [HL]", set_5_hl, 2, 16 },
  { "SET 5, A", set_5_a, 2, 8 },
  { "SET 6, B", set_6_b, 2, 8 },
  { "SET 6, C", set_6_c, 2, 8 },
  { "SET 6, D", set_6_d, 2, 8 },
  { "SET 6, E", set_6_e, 2, 8 },
  { "SET 6, H", set_6_h, 2, 8 },
  { "SET 6, L", set_6_l, 2, 8 },
  { "SET 6, [HL]", set_6_hl, 2, 16 },
  { "SET 6, A", set_6_a, 2, 8 },
  { "SET 7, B", set_7_b, 2, 8 },
  { "SET 7, C", set_7_c, 2, 8 },
  { "SET 7, D", set_7_d, 2, 8 },
  { "SET 7, E", set_7_e, 2, 8 },
  { "SET 7, H", set_7_h, 2, 8 },
  { "SET 7, L", set_7_l, 2, 8 },
  { "SET 7, [HL]", set_7_hl, 2, 16 },
  { "SET 7, A", set_7_a, 2, 8 },
};

void SM83_tick(SM83 *cpu) {
  if (cpu->t > 0) { cpu->t--; return; }

  const uint8_t opcode = cpu->read(cpu->pc++);
  const SM83Instruction *instruction = &instructions[opcode];

  if (opcode == 0xCB) {
    const uint8_t cb_opcode = cpu->read(cpu->pc++);
    instruction = &cb_instructions[cb_opcode];
  }

  instruction->exec(cpu);

  cpu->t = (uint8_t)(cpu->t + instruction->ticks);
  cpu->instruction = instruction;
}

#endif // SM83_IMPLEMENTATION