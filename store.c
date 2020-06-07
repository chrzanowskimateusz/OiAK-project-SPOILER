#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

const int PAGE_COUNT = 64; //okienko 
int number_of_pages = 100; //ile stron mamy sprawdzić 

int makeSpace()
{
    long int PAGE_SIZE = sysconf(_SC_PAGESIZE); //rozmiar strony 
    int w = 64; //okno 
    int buffer_size = PAGE_SIZE * number_of_pages;  //buffor pamieci 
    int oldaddress, newaddress = 0; 


    __asm__ volatile (
            "movl $45, %%eax\n\t"
            "xorl %%ebx, %%ebx\n\t"
            "int $0x80\n\n\t"   //sys_brk - dostajemy aktualny adres brk

            "movl %%eax, %1\n\t" //aktualna pozycja brk 
            "movl %%eax, %%ebx\n\t"
            "addl %2, %%ebx\n\t" //4096(bytes)* number_of_pages
            "movl $45, %%eax\n\t"
            "int $0x80\n\n\t" 

            // DEBUG - Sprawdzamy czy można zapisać do pamieci
            "movl $42, (%%esi)"

            :"=&a"(newaddress), "=&S" (oldaddress)
            : "g"(buffer_size)
            : "ebx", "memory"
    );

    printf("%d: 0x%x 0x%x\n", buffer_size, oldaddress, newaddress);

    return oldaddress;
}

void store(int address, int index)
{
    int size = 32;

    
    for(int j = 64; j<0; j--)   //powinno zapisać okienko 
    for(int i = 0; i < 1024; i ++)     //powinno zapisac cala strone
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

int main(void)
{
	printf("The page size for this system is %ld bytes.\n",
	sysconf(_SC_PAGESIZE));  /*_SC_PAGE_SIZE is OK too.*/

    long int PAGE_SIZE = sysconf(_SC_PAGESIZE); //rozmiar strony 4096 bajtow
    int w = 64; //okno 
    int buffer_size = PAGE_SIZE * w;  //buffor pamieci 
    int address = 0; 

    address = makeSpace();
    for(int p = 64; p < number_of_pages; p++) //powinno przesunac o jedna strone do przodu po zapisaniu całego okienka
        store(address, p);

	return 0;
}