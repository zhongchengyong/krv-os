#include "os.hh"

extern void MainTask();

void TestScheduler() {
  uart_puts("Do scheduler test!\n");
  MainTask();
  uart_puts("Would not go here!\n");
}

// Use extern "C" compile with C-language calling convention to compatible with assembly file.
extern "C" {
void KernelStart() {
  uart_init();
  uart_puts("Hello, KRV-OS\n");
  MemoryManager memory_manager;
  memory_manager.PageTest();

  TestScheduler();

  while (1) {}
}
}
