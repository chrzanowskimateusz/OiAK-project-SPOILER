#include <time.h>
#include <stdio.h>

void load(int* address, int x) {
	__asm("ldr x, address\n\t");
}
int main() {
	int i = 10;
	int* wsk = &i;
	int j;
	load(wsk, j);
	printf("%d\n", j);
}