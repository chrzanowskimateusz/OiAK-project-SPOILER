#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include "clock_start.c"
#include "clock_stop.c"
#include "makeSpace.c"
#include "store.c"
#include "load.c"

const int PAGE_COUNT = 64; //window = 64
int number_of_pages = 100; //number of pages to check

int main(void)
{
	printf("The page size for this system is %ld bytes.\n", sysconf(_SC_PAGESIZE));  /*_SC_PAGE_SIZE is OK too.*/
  uint64_t start1, end1, measure; //var's for measurement
  int address = 0;
  int p;

  FILE *f = fopen("pomiar.txt", "w");   //open file to save results
  address = makeSpace(number_of_pages); //reserve space for operation

  for( p = 64; p < number_of_pages; p++){   // start from 64 - window
    store(address, p);              //store whole page
    for(int i = 0; i < 1024; i ++)  //load every bit
      {
        start1=clock_start();       //start measurement
        load(address, i);           //perform load on target address and exact bit index
        end1 = clock_stop();        //end measurment
        measure = end1 - start1;    
        fprintf(f, "%lld\n", measure);    //save result into textfile
      }

  }
  fclose(f);   //close file
	return 0;
}
