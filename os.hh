#include <cstdint>
#include <cstddef>
#include <cstdarg>

/* uart */
extern void uart_init();
extern void uart_puts(const char* s);

/* printf */
 extern int  printf(const char* s, ...);
 extern void panic(char *s);

/**
 * Memory managemant
 */


class MemoryManager {
 public:
   MemoryManager() : m_alloc_start{0}, m_alloc_end{0}, m_num_pages{0} {}
   void InitPage();

 private:
  uint32_t m_alloc_start;
  uint32_t m_alloc_end;
  uint32_t m_num_pages;

  struct Page {
      uint8_t flags;
  };
};
