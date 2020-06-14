void load(int address, int index)
{
    int size = 32;
    int load = 0;

    for(int i = 0; i < 1024; i ++)  //powinno zapisac cala strone
    {

        __asm__ volatile (
            "movl %1, %%ecx\n"
            "movl %0, %%eax\n"
            "movl (%%eax, %%ecx), %2 \n"
            :
            :"g"(address), "g"(size*i), "g"(load)
            :"memory"
        );
    }
}
