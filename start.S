#include "platform.hh"
.global _start

.equ STACK_SIZE, 8192

.text
_start:
  csrr t0, mhartid
  mv tp, t0
  bnez t0, park  # suspend hart if not on hart 0
  slli t0, t0, 10
  la sp, stacks + STACK_SIZE

  add sp, sp, t0

  j KernelStart

park:
  wfi
  j park

stacks:
  .skip STACK_SIZE * MAXNUM_CPU # Allocate space for the hart stacks
  .end
