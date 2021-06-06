#include "os.hh"
#include "platform.hh"
#include "riscv.hh"

extern Scheduler sched;

extern "C" {
extern void trap_vector();

reg_t trap_handler(reg_t epc, reg_t cause);
}

void InitTrap() { write_csr(mtvec, (reg_t)trap_vector); }

void ExternalIntHandler() {
  int irq = ClaimPLIC();

  if (irq == UART0_IRQ) {
    uart_isr();
  } else if (irq) {
    printf("unexpected interrupt irq = %d\n", irq);
  }

  if (irq) {
    CompletePLIC(irq);
  }
}

reg_t trap_handler(reg_t epc, reg_t cause) {
  reg_t ret_pc = epc;
  reg_t cause_code = cause & 0xfff;
  if (cause >> 63) {
    switch (cause_code) {
      case 3: {
        uart_puts("Software interrupt.\n");
        /*
         * acknowledge the software interrupt by clearing
         * the MSIP bit in mip.
         */
        int id = read_csr(mhartid);
        *(uint32_t*)CLINT_MSIP(id) = 0;
        sched.Schedule();
        break;
      }
      case 7:
        uart_puts("Timer interrupt.\n");
        TimerHandler();
        break;
      case 11:
        uart_puts("External interrupt.\n");
        ExternalIntHandler();
        break;
      default:
        uart_puts("Unknown interrupt.\n");
        break;
    }
  } else {
    uart_puts("Sync exception.\n");
    panic("OOPS! What can I do!");
    ret_pc += 4;
  }
  return ret_pc;
}