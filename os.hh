#include <cstdint>
#include <cstddef>
#include <cstdarg>

/* uart */
extern void uart_init();
extern void uart_puts(const char *s);

/* printf */
extern int printf(const char *s, ...);
extern void panic(char *s);

/**
 * Memory managemant
 */


class MemoryManager {
  struct Page;
 public:
  MemoryManager() : m_alloc_start{0}, m_alloc_end{0}, m_num_pages{0} {
    InitPage();
  }
  void *AllocPage(int npages);
  void FreePage(void *p);

  void PageTest();

 private:
  uint32_t m_alloc_start;
  uint32_t m_alloc_end;
  uint32_t m_num_pages;
  void InitPage();
  void Clear(Page *page);
  bool IsFree(Page *page);
  void SetFlag(Page *page, uint8_t flags);
  bool IsLast(Page *page);
  uint32_t AlignPage(uint32_t address);

  struct Page {
    uint8_t flags;
  };
};
