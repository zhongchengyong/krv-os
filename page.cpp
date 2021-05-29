#include "os.hh"
#include <cassert>

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
#define PAGE_ALIGN 12

#define PAGE_TAKEN (uint8_t)(1 << 0)
#define PAGE_LAST  (uint8_t)(1 << 1)

void MemoryManager::InitPage() {
  m_num_pages = (HEAP_SIZE / PAGE_SIZE) - 8;
  printf("HEAP_START = 0x%x, HEAP_SIZE = 0x%x, num of pages = %ld\n", HEAP_START, HEAP_SIZE, m_num_pages);

  Page *page = (Page *) HEAP_START;
  for (uint32_t i = 0; i < m_num_pages; ++i) {
    Clear(page);
    ++page;
  }

  m_alloc_start = AlignPage(HEAP_START + 8 * PAGE_SIZE);
  m_alloc_end = m_alloc_start + (PAGE_SIZE * m_num_pages);

  printf("TEXT:   0x%x -> 0x%x\n", TEXT_START, TEXT_END);
  printf("RODATA: 0x%x -> 0x%x\n", RODATA_START, RODATA_END);
  printf("DATA:   0x%x -> 0x%x\n", DATA_START, DATA_END);
  printf("BSS:    0x%x -> 0x%x\n", BSS_START, BSS_END);
  printf("HEAP:   0x%x -> 0x%x\n", m_alloc_start, m_alloc_end);
}

/**
 * Allocate a memory block which is composed of continuous physical pages.
 * TODO(zhong): Optimize by a new algorithm.
 * @param npages: Page number to allocate.
 */
void *MemoryManager::AllocPage(uint32_t npages) {
  bool found = false;
  Page *search_page = (Page *) HEAP_START;
  for (uint32_t i = 0; i < m_num_pages - npages; ++i) {
    if (IsFree(search_page)) {
      found = true;
      Page *page_start = search_page + 1;
      // Find enough continuous pages
      uint32_t j = i + 1;
      for (; j < (i + npages); ++j) {
        if (!IsFree(page_start)) {
          found = false;
          break;
        }
        ++page_start;
      }

      // Mark flag if found
      if (found) {
        Page *page_target = search_page;
        for (uint32_t k = i; k < (i + npages); ++k) {
          SetFlag(page_target, PAGE_TAKEN);
          ++page_target;
        }
        --page_target;
        SetFlag(page_target, PAGE_LAST);
        return (void *) (m_alloc_start + i * PAGE_SIZE);
      }
    }
    ++search_page;
  }
  return nullptr;
}

void MemoryManager::FreePage(void *p) {
  if (!p || (uint64_t) p > m_alloc_end) {
    return;
  }
  Page *page = (Page *) HEAP_START;
  page += ((uint64_t) p - m_alloc_start) / PAGE_SIZE;

  // Loop and clear allocated pages
  while (!IsFree(page)) {
    Clear(page);
    if (IsLast(page)) break;
    else ++page;
  }
}

void MemoryManager::Clear(Page *page) {
  page->flags = 0;
}

bool MemoryManager::IsFree(Page *page) {
  return !(page->flags & PAGE_TAKEN);
}

void MemoryManager::SetFlag(Page *page, uint8_t flags) {
  page->flags |= flags;
}

bool MemoryManager::IsLast(Page *page) {
  return page->flags & PAGE_LAST;
}

uint32_t MemoryManager::AlignPage(uint32_t address) {
  uint32_t align = (1 << PAGE_ALIGN) - 1;
  return (address + align) & (~align);
}

void MemoryManager::PageTest() {
  void *p = AllocPage(2);
  printf("p = 0x%x\n", p);
  printf("p = 0x%x\n", (uint64_t) p >> 32);

  void *p2 = AllocPage(7);
  printf("p2 = 0x%x\n", p2);
  FreePage(p2);

  void *p3 = AllocPage(4);
  printf("p3 = 0x%x\n", p3);
}
