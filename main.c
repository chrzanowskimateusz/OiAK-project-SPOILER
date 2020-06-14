#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "clock_start.c"
#include "clock_stop.c"
#include "makeSpace.c"
#include "store.c"
#include "load.c"

const int PAGE_COUNT = 64; //okienko
int number_of_pages = 100; //ile stron mamy sprawdzić

int main(void)
{
	printf("The page size for this system is %ld bytes.\n",
  sysconf(_SC_PAGESIZE));  /*_SC_PAGE_SIZE is OK too.*/
  uint64_t start1, end1, wynik1; //wyniki pierwszych pomiarow
  long int PAGE_SIZE = sysconf(_SC_PAGESIZE); //rozmiar strony 4096 bajtow
  int w = 64; //okno
  int buffer_size = PAGE_SIZE * w;  //buffor pamieci
  int address = 0;
  int p;
  uint64_t measure[64];
  address = makeSpace(number_of_pages);

    for( p = 64; p < number_of_pages; p++){
      store(address, p);
      start1=clock_start();
      load(address);
      end1 = clock_stop();
      measure[p] = end1 - start1;
    }


    for( p = 64; p < number_of_pages; p++){
      printf("%d. wynik= %lld\n", p, measure[p]);
    }

	return 0;
}
