# Save all register to context
.macro reg_save base
	sd ra, 0(\base)
	sd sp, 8(\base)
	sd gp, 16(\base)
	sd tp, 24(\base)
	sd t0, 32(\base)
	sd t1, 40(\base)
	sd t2, 48(\base)
	sd s0, 56(\base)
	sd s1, 64(\base)
	sd a0, 72(\base)
	sd a1, 80(\base)
	sd a2, 88(\base)
	sd a3, 96(\base)
	sd a4, 104(\base)
	sd a5, 112(\base)
	sd a6, 120(\base)
	sd a7, 128(\base)
	sd s2, 136(\base)
	sd s3, 144(\base)
	sd s4, 152(\base)
	sd s5, 160(\base)
	sd s6, 168(\base)
	sd s7, 176(\base)
	sd s8, 184(\base)
	sd s9, 192(\base)
	sd s10, 200(\base)
	sd s11, 208(\base)
	sd t3, 216(\base)
	sd t4, 224(\base)
	sd t5, 232(\base)
	sd t6, 240(\base)
.endm

# Restore registers from the context
.macro reg_restore base
	ld ra, 0(\base)
	ld sp, 8(\base)
	ld gp, 16(\base)
	ld tp, 24(\base)
	ld t0, 32(\base)
	ld t1, 40(\base)
	ld t2, 48(\base)
	ld s0, 56(\base)
	ld s1, 64(\base)
	ld a0, 72(\base)
	ld a1, 80(\base)
	ld a2, 88(\base)
	ld a3, 96(\base)
	ld a4, 104(\base)
	ld a5, 112(\base)
	ld a6, 120(\base)
	ld a7, 128(\base)
	ld s2, 136(\base)
	ld s3, 144(\base)
	ld s4, 152(\base)
	ld s5, 160(\base)
	ld s6, 168(\base)
	ld s7, 176(\base)
	ld s8, 184(\base)
	ld s9, 192(\base)
	ld s10, 200(\base)
	ld s11, 208(\base)
	ld t3, 216(\base)
	ld t4, 224(\base)
	ld t5, 232(\base)
	ld t6, 240(\base)
.endm

.text
.globl switch_to
.align 4
# void switch_to(struct context *next);
# a0: pointer to the context of the next task
# TODO(kode.zhong): We do NOT need mscratch operation
switch_to:
    csrrw t6, mscratch, t6 # Swap t6 and mscratch to save old context
	beqz t6, 1f            # The old context maybe null
	reg_save t6

1:
	# Switch mscratch to point to the context of the new task
	csrw mscratch, a0

	# Restore Registers
	# Use t6 to point to the context of the new task
	mv t6, a0
	reg_restore t6

	# Do actual context switching
	ret

.globl trap_vector
.align 4
trap_vector:
	# Save context
	# csrr t6, mscratch
	# reg_save t6
	csrrw	t6, mscratch, t6	# swap t6 and mscratch
	reg_save t6
	csrw	mscratch, t6

	# Call the C trap_handler in trap.cpp
	csrr a0, mepc
	csrr a1, mcause
	call trap_handler

	# trap_handler will return the return address via a0
	csrw mepc, a0

	# Restore context
	csrr t6, mscratch
	reg_restore t6

	# Return to the position before trap
	mret

.end



