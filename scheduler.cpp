//
// Created by kode.zhong on 2021/5/23.
//
#include "os.hh"

extern "C" {
extern void switch_to(context *next);
}

void Scheduler::WriteMscratch(reg_t x) {
  asm volatile("csrw mscratch, %0" : : "r" (x));
}

void Scheduler::InitSched() {
  WriteMscratch(0);
  m_top = 0;
  m_current = -1;
}

void Scheduler::Schedule() {
  if (m_top <= 0) {
    panic("Nums of task should be greater than zero!");
    return;
  }

  m_current = (m_current + 1) % m_top;
  struct context *next = &(ctx_tasks[m_current]);
  switch_to(next);
}

int Scheduler::CreateTask(void (*statr_routine)()) {
  if (m_top < MAX_TASKS) {
    // Point to its own top of stack
    ctx_tasks[m_top].sp = (reg_t) &task_stack[m_top][STACK_SIZE - 1];
    ctx_tasks[m_top].ra = (reg_t) statr_routine;
    ++m_top;
    return 0;
  } else {
    return -1;
  }
}

void Scheduler::YieldTask() {
  Schedule();
}

void Scheduler::DelayTask(volatile int count) {
  count *= 50000;
  while (count--);
}
