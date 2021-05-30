#include "platform.hh"
.global _start

.equ STACK_SIZE, 8192

.text
_start:
  csrr t0, mhartid
  mv tp, t0
  bnez t0, park  # suspend hart if not on hart 0

	# Set all bytes in the BSS section to zero.
	la	a0, _bss_start
	la	a1, _bss_end
	bgeu	a0, a1, 2f
1:
	sw	zero, (a0)
	addi	a0, a0, 4
	bltu	a0, a1, 1b
2:
	# Setup stacks, the stack grows from bottom to top, so we put the
	# stack pointer to the very end of the stack range.
	slli	t0, t0, 10		# shift left the hart id by 1024
	la	sp, stacks + STACK_SIZE	# set the initial stack pointer
					# to the end of the stack space
	add	sp, sp, t0		# move the current hart stack pointer
					# to its place in the stack space

  j KernelStart

park:
  wfi
  j park

stacks:
  .skip STACK_SIZE * MAXNUM_CPU # Allocate space for the hart stacks
  .end
