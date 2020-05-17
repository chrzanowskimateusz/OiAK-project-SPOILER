//long long int ma minimum 64 bity
//można ulepszyć, bo ten kod nie we wszystkich przypadkach poczeka na zakończenie
//wczesniejszych instrukcji, poczytam trochę i go ulepszę, póki co można testować czasy



unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    unsigned a, d;

    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}
