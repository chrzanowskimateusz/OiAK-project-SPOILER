int makeSpace(int number_of_pages)
{
    long int PAGE_SIZE = sysconf(_SC_PAGESIZE); //pagesize
    int w = 64; //window
    int buffer_size = PAGE_SIZE * number_of_pages;  //buffer
    int oldaddress, newaddress = 0;



    __asm__ volatile (
            "movl $45, %%eax\n\t"
            "xorl %%ebx, %%ebx\n\t"
            "int $0x80\n\n\t"   //sys_brk - gives current brk address

            "movl %%eax, %1\n\t" //current position of brk
            "movl %%eax, %%ebx\n\t"
            "addl %2, %%ebx\n\t" //4096(bytes)* number_of_pages
            "movl $45, %%eax\n\t"
            "int $0x80\n\n\t"

            // DEBUG - chceck if we can write into memory
            "movl $42, (%%esi)"

            :"=&a"(newaddress), "=&S" (oldaddress)
            : "g"(buffer_size)
            : "ebx", "memory"
    );

    printf("%d: 0x%x 0x%x\n", buffer_size, oldaddress, newaddress);

    return oldaddress;
}
