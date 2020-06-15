

static inline uint64_t clock_stop(void)
{
  unsigned cycles_low, cycles_high;

  asm volatile(
              "RDTSCP\n\t"          //Read Time-Stamp-Counter and processor ID
              "mov %%edx, %0\n\t"
              "mov %%eax, %1\n\t"
              "CPUID\n\t"           //serialization
              : "=r" (cycles_high), "=r" (cycles_low)
              ::"%rax", "%rbx", "%rcx", "%rdx");

  return (uint64_t) cycles_high << 32 | cycles_low;
}
