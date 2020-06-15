void store(int address, int index)
{
    int size = 32;


    for(int j = 64; j<0; j--)          //writing whole window
    for(int i = 0; i < 1024; i ++)     //writing whole page
    {

        __asm__ volatile (
            "movl %1, %%ecx\n"
            "movl %0, %%eax\n"
            "movl $1, (%%eax, %%ecx)\n"
            :
            :"g"(address), "g"(size*i + (index-j)*4096*8)
            :"memory"
        );
    }
}
