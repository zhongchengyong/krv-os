#include "os.hh"
#include "riscv.hh"
#include "platform.hh"

#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

void Timer::SetInterval(int interval) {
  int id = read_csr(mhartid);
  *(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + interval;
}

void Timer::InitTimer() {
    SetInterval(TIMER_INTERVAL);
    // Enable MTIE in mis csr
    write_csr(mie, read_csr(mie) | MIE_MTIE);
}

void Timer::TimerHandler() {
  ++m_tick;
  printf("tick: %d\n", m_tick);

  SetInterval(TIMER_INTERVAL);
  m_sched.Schedule();
}
