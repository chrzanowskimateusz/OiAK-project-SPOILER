void load(int address, int index)
{
    int size = 32;
    int load = 0;

        __asm__ volatile (
            "movl %1, %%ecx\n"
            "movl %0, %%eax\n"
            "movl (%%eax, %%ecx), %%ebx \n"
            :
            :"g"(address), "g"(size*index)
            :"ebx", "memory"
        );
}
