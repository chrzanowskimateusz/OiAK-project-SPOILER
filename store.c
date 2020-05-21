#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

const int PAGE_COUNT = 64; //ile stron chcemy sprawdzić 

int main(void)
{
	printf("The page size for this system is %ld bytes.\n",
	sysconf(_SC_PAGESIZE));  /*_SC_PAGE_SIZE is OK too.*/

    long int PAGE_SIZE = sysconf(_SC_PAGESIZE); //rozmiar strony 
    int w = 64; //okno 
    int buffer_size = PAGE_SIZE * w;  //buffor pamieci 
    int address = 0; //adres poczatku buffora
    int current = 0; 

    //voalatile zapobiega eliminacji z powodu braku wyjść
    /*__asm__ volatile (
            "mov $45, %%eax\n"
            "xor %%ebx, %%ebx\n"
            "int $0x80\n"   //sys_brk - pozwala na zmianę rozmiaru bloku .data - gdyby ktoś chciał się douczyć w temacie http://students.mimuw.edu.pl/SO/Linux/Temat02/brk.html
            
            "add %1, %%eax\n" //liczba bajtow do zarezerowania 64 strony 4096(bytes)*64 
            "mov %%eax, %%ebx\n"
            "mov $45, %%eax\n"
            "int $0x80\n" //sys_brk On success, brk() returns zero.  On error, -1 is returned
            "mov %%eax, %0\n"

            :"=g"(address)
            : "g"(buffer_size)
    );
    */
        __asm__ volatile (
            "movl $45, %%eax\n"
            "xorl %%ebx, %%ebx\n"
            "int $0x80\n"   //sys_brk - pozwala na zmianę rozmiaru bloku .data - gdyby ktoś chciał się douczyć w temacie http://students.mimuw.edu.pl/SO/Linux/Temat02/brk.html
            
            "movl %%eax, %%esi\n" //current position of brk 
            "movl %%eax, %%ebx\n"
            "addl %1, %%ebx\n" //liczba bajtow do zarezerowania 64 strony 4096(bytes)*64, dodajemy do adresu ktory jest w esi
            "movl $45, %%eax\n"
            "int $0x80\n" //sys_brk On success, brk() returns zero.  On error, -1 is returned
            "movl %%esi, %%eax\n"
            "movl %%esi, %0\n" //starting addres 
            "movl $42, (%%esi)\n"

            :"=g"(address)
            : "g"(buffer_size)
    );
    printf("pos of brk: %d\n", address);

	return 0;
}