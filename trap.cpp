#include "os.hh"
#include "riscv.hh"
#include "platform.hh"

extern "C" {
extern void trap_vector();

reg_t trap_handler(reg_t epc, reg_t cause);
}

void InitTrap() {
  write_csr(mtvec, (reg_t)trap_vector); 
  printf("Init trap.....\n");
}

void ExternalIntHandler() {
	int irq = ClaimPLIC();

	if (irq == UART0_IRQ){
      		uart_isr();
	} else if (irq) {
		printf("unexpected interrupt irq = %d\n", irq);
	}
	
	if (irq) {
		CompletePLIC(irq);
	}
}

reg_t trap_handler(reg_t epc, reg_t cause) {
  uart_puts("In trap handler.\n");
  reg_t ret_pc = epc;
  reg_t cause_code = cause & 0xfff;
  if (cause & 0x80000000) {
    switch (cause_code) {
      case 3:
        uart_puts("Software interrupt.\n");
        break;
      case 7:
        uart_puts("Timer interrupt.\n");
        break;
      case 11:
        uart_puts("Timer interrupt.\n");
        ExternalIntHandler();
        break;
      default:
        uart_puts("Unknown interrupt.\n");
        break;
    }
  } else {
    uart_puts("Sync exception.\n");
    ret_pc += 4;
  }
  return ret_pc;
}