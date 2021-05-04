extern void uart_init();
extern void uart_puts(char* s);

extern "C" {
  void KernelStart() {
    uart_init();
    uart_puts("Hello, KRV-OS\n");
    while(1) {}
  }
}
