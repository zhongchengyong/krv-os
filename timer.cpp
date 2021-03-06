#include "os.hh"
#include "riscv.hh"
#include "platform.hh"

#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

extern Scheduler sched;

static uint32_t _tick = 0;

void SetInterval(int interval) {
  int id = read_csr(mhartid);
  *(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + interval;
}

void InitTimer() {
    SetInterval(TIMER_INTERVAL);
    // Enable MTIE in mis csr
    write_csr(mie, read_csr(mie) | MIE_MTIE);
}

void TimerHandler() {
  ++_tick;
  printf("tick: %d\n", _tick);

  SetInterval(TIMER_INTERVAL);
  sched.Schedule();
}
