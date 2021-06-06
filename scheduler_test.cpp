#include <memory>

#include "os.hh"
#include "riscv.hh"

#define DELAY 1000

extern Scheduler sched;

void UserTask0(void) {
  uart_puts("Task 0: Created!\n");
  // sched.YieldTask();
  uart_puts("Task 0 back to run.\n");
  while (1) {
    uart_puts("Task 0: Running...\n");
    sched.DelayTask(DELAY);
  }
}

void UserTask1(void) {
  uart_puts("Task 1: Created!\n");
  while (1) {
    uart_puts("Task 1: Running...\n");
    sched.DelayTask(DELAY);
  }
}

void UserTask2(void) {
  uart_puts("Task 2: Created!\n");
  while (1) {
    uart_puts("Task 2: Running...\n");
    sched.DelayTask(DELAY);
  }
}

/* NOTICE: DON'T LOOP INFINITELY IN main() */
void MainTask(void) {
  int id = read_csr(mhartid);
  uart_puts("In main task...\n");
  sched.InitSched();
  sched.CreateTask(UserTask0);
  sched.CreateTask(UserTask1);
  sched.CreateTask(UserTask2);
  sched.Schedule();
}