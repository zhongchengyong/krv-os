#include "os.hh"
#include "riscv.hh"

#define DELAY 1000

void UserTask0(void) {
  Scheduler& sched = Scheduler::GetInstance();
  uart_puts("Task 0: Created!\n");
  while (1) {
    uart_puts("Task 0: Running...\n");
    sched.DelayTask(DELAY);
    sched.YieldTask();
  }
}

void UserTask1(void) {
  Scheduler& sched = Scheduler::GetInstance();
  uart_puts("Task 1: Created!\n");
  while (1) {
    uart_puts("Task 1: Running...\n");
    sched.DelayTask(DELAY);
    sched.YieldTask();
  }
}

void UserTask2(void) {
  Scheduler& sched = Scheduler::GetInstance();
  uart_puts("Task 2: Created!\n");
  while (1) {
    uart_puts("Task 2: Running...\n");
    sched.DelayTask(DELAY);
    sched.YieldTask();
  }
}

/* NOTICE: DON'T LOOP INFINITELY IN main() */
void MainTask(void) {
  Scheduler& sched = Scheduler::GetInstance();
  sched.InitSched();
  Timer timer(sched);
  timer.InitTimer();
  sched.CreateTask(UserTask0);
  sched.CreateTask(UserTask1);
  sched.CreateTask(UserTask2);
  sched.Schedule();
}