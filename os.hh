#include "types.hh"

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
  void *AllocPage(uint32_t npages);
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

struct context {
  // ignore x0
  reg_t ra;
  reg_t sp;
  reg_t gp;
  reg_t tp;
  reg_t t0;
  reg_t t1;
  reg_t t2;
  reg_t s0;
  reg_t s1;
  reg_t a0;
  reg_t a1;
  reg_t a2;
  reg_t a3;
  reg_t a4;
  reg_t a5;
  reg_t a6;
  reg_t a7;
  reg_t s2;
  reg_t s3;
  reg_t s4;
  reg_t s5;
  reg_t s6;
  reg_t s7;
  reg_t s8;
  reg_t s9;
  reg_t s10;
  reg_t s11;
  reg_t t3;
  reg_t t4;
  reg_t t5;
  reg_t t6;
};

#define MAX_TASKS  10
#define STACK_SIZE 1024  // TODO(kode.zhong): Naive implementation now

class Scheduler {
 public:
  Scheduler() : m_top{0}, m_current{-1} {}
  static void WriteMscratch(reg_t x);
  void InitSched();
  void Schedule();
  int CreateTask(void (*start)());
  void YieldTask();
  void DelayTask(volatile int count);
 private:
  uint8_t task_stack[MAX_TASKS][STACK_SIZE];
  struct context ctx_tasks[MAX_TASKS];
  int m_top;  // Mark the max available task position
  int m_current; // Point to the context of current task
};