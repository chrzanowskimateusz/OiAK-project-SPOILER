//dorzucam tez mój plik do testów z komentarzem, zebyscie wiedzieli jak korzystać

#include <stdio.h>
#include <time.h>
#include "rdtsc.c"

//zmienne do funkcji rdtsc
long long int start,end;

int main(){

double wynik;
double cpufreq = 2500000000; // Mój procek ma 2,5GHz, jesli nie jesteście pewni
                             // czestotliwosci waszego procka to na linuxie
                             // jest polecenie lscpu

start = rdtsc();
printf("testtesttest %d\n", 10);
end = rdtsc();

wynik = (double)(end-start)/cpufreq; // podstaw do wzoru własciwie

printf("\n\nWyniki: \nstart = %lld \nend = %lld\nwynik = %f\n", start, end, wynik);



return 0;
}
