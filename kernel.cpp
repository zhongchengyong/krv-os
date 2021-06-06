#include "os.hh"

extern void MainTask();

void TestScheduler() {
  uart_puts("Do scheduler test!\n");
  MainTask();
  uart_puts("Would not go here!\n");
}

extern void InitTrap();
extern void InitPLIC();


// Use extern "C" compile with C-language calling convention to compatible with assembly file.
extern "C" {
void KernelStart() {
  uart_init();
  uart_puts("Hello, KRV-OS\n");
  MemoryManager memory_manager;
  memory_manager.PageTest();

  InitTrap();
  InitPLIC();
  InitTimer();

  TestScheduler();

  uart_puts("Not reached....\n");

  while (1) {}
}
}
