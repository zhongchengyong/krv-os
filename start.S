.global _start
.text

_start:
  csrr t0, mhartid
  j KernelStart
