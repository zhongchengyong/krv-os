#include "os.hh"

// Use extern "C" compile with C-language calling convention to compatible with assembly file.
extern "C" {
  void KernelStart() {
    uart_init();
    uart_puts("Hello, KRV-OS\n");
    MemoryManager memory_manager;
    memory_manager.PageTest();
    while(1) {}
  }
}
