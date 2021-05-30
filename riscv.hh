#ifndef __RISCV_HH__
#define __RISCV_HH__

#include "types.hh"

/* Machine Status Register, mstatus */
#define MSTATUS_MPP (3 << 11)
#define MSTATUS_SPP (1 << 8)

#define MSTATUS_MPIE (1 << 7)
#define MSTATUS_SPIE (1 << 5)
#define MSTATUS_UPIE (1 << 4)

#define MSTATUS_MIE (1 << 3)
#define MSTATUS_SIE (1 << 1)
#define MSTATUS_UIE (1 << 0)

/* Machine-mode Interrupt Enable */
#define MIE_MEIE (1 << 11)  // external
#define MIE_MTIE (1 << 7)   // timer
#define MIE_MSIE (1 << 3)   // software

// Provide a general function to read/write riscv CSR
#define read_csr(csr) ({\
  reg_t x; \
  asm volatile("csrr %0, " #csr : "=r"(x)); \
  (x); \
})

#define write_csr(csr, value) \
  asm volatile("csrw " #csr ", %0" : : "r"(value));

/**
 * Read thread pointer
 */
inline reg_t r_tp()
{
	reg_t x;
	asm volatile("mv %0, tp" : "=r" (x) );
	return x;
}
#endif