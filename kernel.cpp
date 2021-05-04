extern void uart_init();
extern void uart_puts(const char* s);

// Use extern "C" compile with C-language calling convention to compatible with assembly file.
extern "C" {
  void KernelStart() {
    uart_init();
    uart_puts("Hello, KRV-OS\n");
    while(1) {}
  }
}
