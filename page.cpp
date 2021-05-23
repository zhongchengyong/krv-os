#include "os.hh"

/**
 * Following global variables defined in mem.S
 */

extern uint32_t TEXT_START;
extern uint32_t TEXT_END;
extern uint32_t DATA_START;
extern uint32_t DATA_END;
extern uint32_t RODATA_START;
extern uint32_t RODATA_END;
extern uint32_t BSS_START;
extern uint32_t BSS_END;
extern uint32_t HEAP_START;
extern uint32_t HEAP_SIZE;

#define PAGE_SIZE  4096
#define PAGE_ORDER 12

#define PAGE_TAKEN (uint8_t)(1 << 0)
#define PAGE_LAST  (uint8_t)(1 << 1)

void MemoryManager::InitPage() {
  m_num_pages = (HEAP_SIZE / PAGE_SIZE) - 8;

  printf("HEAP_START = 0x%x, HEAP_SIZE = 0x%lx, num of pages = %ld\n", HEAP_START, HEAP_SIZE, m_num_pages);
//  m_alloc_start= _align_page(HEAP_START + 8 * PAGE_SIZE);
//  m_alloc_end= _alloc_start + (PAGE_SIZE * _num_pages);

  printf("TEXT:   0x%x -> 0x%x\n", TEXT_START, TEXT_END);
  printf("RODATA: 0x%x -> 0x%x\n", RODATA_START, RODATA_END);
  printf("DATA:   0x%x -> 0x%x\n", DATA_START, DATA_END);
  printf("BSS:    0x%x -> 0x%x\n", BSS_START, BSS_END);
//  printf("HEAP:   0x%x -> 0x%x\n", _alloc_start, _alloc_end);
}
