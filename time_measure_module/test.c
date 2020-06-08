//zbiorę do kupy wszystkie polecenia konsolowe i wrzucę na discorda ze screenami
//i kompilacją/testowaniem

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/sched.h>

#include "clock_start.c"
#include "clock_stop.c"
#include "store.c"


//najlepiej do tego modułu zaincludować load i store, bo nie znam się na tyle dobrze
//na kernel modules, zeby tamto przebudowywać

unsigned long flags;
uint64_t start, end, wynik;

static int __init test_start(void){

  int i;

  //pętle tylko testowo sobie zrobiłem, edytujcie wedle uznania parametry
  for(i=0;i<10;i++){

    preempt_disable();          // te linijki służą do
    raw_local_irq_save(flags);  //przejęcia pełnej kontrolii nad CPU
    int address = makeSpace();
    for(int p = 64; p < number_of_pages; p++) //powinno przesunac o jedna strone do przodu po zapisaniu całego okienka
        store(address, p);
    start = clock_start();
    printk("testtesttest %d\n", 10);  // <- tutaj samego loada do pomiaru, najlepiej jako osobną funkcję
    end = clock_stop();

    raw_local_irq_restore(flags);
    preempt_enable();             //wznowienie normalnej pracy

    wynik = (end-start);
    printk("\n\nWyniki: \nstart = %lld \nend = %lld\nwynik = %lld\n", start, end, wynik);
  }

return 0;
}

static void __exit hello_end(void) { printk(KERN_INFO "Exit.\n"); }

module_init(test_start);
module_exit(hello_end);
