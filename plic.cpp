#include "os.hh"
#include "platform.hh"
#include "riscv.hh"

void InitPLIC() {
  int hart = r_tp();

  // Set uart interrupt priority
  *(uint32_t*)PLIC_PRIORITY(UART0_IRQ) = 1;
  // Enable uart0
  *(uint32_t*)PLIC_MENABLE(hart) = (1 << UART0_IRQ);
  // Set threashold for current hart
  *(uint32_t*)PLIC_MTHRESHOLD(hart) = 0;
  // Enable external interrupt in mie
  write_csr(mie, read_csr(mie) | MIE_MEIE);
  // Enable machine mode global interrupt
  write_csr(mstatus, read_csr(mstatus) | MSTATUS_MIE);

  printf("Init PLIC\n");
}

/**
 * DESCRIPTION:
 *	Query the PLIC what interrupt we should serve.
 *	Perform an interrupt claim by reading the claim register, which
 *	returns the ID of the highest-priority pending interrupt or zero if there 
 *	is no pending interrupt. 
 *	A successful claim also atomically clears the corresponding pending bit
 *	on the interrupt source.
 * RETURN VALUE:
 *	the ID of the highest-priority pending interrupt or zero if there 
 *	is no pending interrupt.
 */
int ClaimPLIC() {
  int hart = r_tp();
  int irq = *(uint32_t*)PLIC_MCLAIM(hart);
  return irq;
}

/** 
 * DESCRIPTION:
  *	Writing the interrupt ID it received from the claim (irq) to the 
 *	complete register would signal the PLIC we've served this IRQ. 
 *	The PLIC does not check whether the completion ID is the same as the 
 *	last claim ID for that target. If the completion ID does not match an 
 *	interrupt source that is currently enabled for the target, the completion
 *	is silently ignored.
 * RETURN VALUE: none
 */
void CompletePLIC(int irq) {
  int hart = r_tp();
  *(uint32_t*)PLIC_MCOMPLETE(hart) = irq;
}