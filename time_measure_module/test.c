//zbiorę do kupy wszystkie polecenia konsolowe i wrzucę na discorda ze screenami
//i kompilacją/testowaniem

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/sched.h>
#include <mintomic/mintomic.h>


#include "clock_start.c"
#include "clock_stop.c"
#include "store.c"


//najlepiej do tego modułu zaincludować load i store, bo nie znam się na tyle dobrze
//na kernel modules, zeby tamto przebudowywać

unsigned long flags;
uint64_t start1, end1, wynik1; //wyniki pierwszych pomiarow
uint64_t start2, end2, wynik2; //wyniki drugich pomiarow
uint64_t roznica; //roznica pomiedzy drugim wynikiem a pierwszym
mint_atomic64_t sharedValue = { 0 };

void storeValue(void)
{
    mint_store_64_relaxed(&sharedValue, 0x100000014);
}
uint64_t loadValue(void)
{
    return mint_load_64_relaxed(&sharedValue);
}

static int __init test_start(void){

  int i;

  //pętle tylko testowo sobie zrobiłem, edytujcie wedle uznania parametry
  for(i=0;i<10;i++){

    preempt_disable();          // te linijki służą do
    raw_local_irq_save(flags);  //przejęcia pełnej kontrolii nad CPU
    
    storeValue();
    start1=clock_start();
    loadValue();
    end1 = clock_stop();
    
    int address = makeSpace();
    for(int p = 64; p < number_of_pages; p++) //powinno przesunac o jedna strone do przodu po zapisaniu całego okienka
        store(address, p);
    start2 = clock_start();
    loadValue();  // <- tutaj samego loada do pomiaru, najlepiej jako osobną funkcję
    end2 = clock_stop();

    raw_local_irq_restore(flags);
    preempt_enable();             //wznowienie normalnej pracy

    wynik1 = (end1-start1);
    printk("\n\nWynik 1 pomiaru: \nstart = %lld \nend = %lld\nwynik = %lld\n", start1, end1, wynik1);
    wynik2 = (end2-start2);
    printk("\n\nWyniki 2 pomiaru: \nstart = %lld \nend = %lld\nwynik = %lld\n", start2, end2, wynik2);
  }

return 0;
}

static void __exit hello_end(void) { printk(KERN_INFO "Exit.\n"); }

module_init(test_start);
module_exit(hello_end);
