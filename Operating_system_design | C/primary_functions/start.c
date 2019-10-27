#include <cpu.h>
#include <inttypes.h>

#include <stdio.h>
#include "clock.h"
#include "context.h"

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue
uint32_t fact(uint32_t n)
{
    uint32_t res;
    if (n <= 1) {
        res = 1;
    } else {
        res = fact(n - 1) * n;
    }
    return res;
}

//typedef enum STATE {ELU, RDY} STATE;

void idle(void)
{
	for (;;) {
		printf("[%s] pid = %i\n", mon_nom(), mon_pid());
		ordonnance();
	}
}

void proc1(void)
{
	for (;;) {
		printf("[%s] pid = %i\n", mon_nom(), mon_pid());
		ordonnance();
	}	
}

void kernel_start(void)
{
	//-----------------------------------SEANCE 1-------------------------------//
    uint32_t x = fact(5);
	
    //test1
	/* printf("%i",x); */ 
	/* char c = 1; */
	/* printf("\n"); */
	/* printf("%i",x+1); */
	/* printf("%c",c); */

	//test2
	/* printf("%i", x); */
	/* printf("\f\tabd\bc"); */

	/* for(int i=0; i<50; i++) */
	/* 	printf("%i", x+i); */

	(void) x;

	//-----------------------------------SEANCE 2-------------------------------//

	/* sti();//demasquage des interruptions externes */
	/* masque_IRQ(0,0); */
	/* init_traitant_IT(32, traitant_IT_32); */

	//-----------------------------------SEANCE 3-------------------------------//

	add_process(0,"idle", ELU);
	add_process(1,"proc1", RDY);
	
	link_function(1,proc1);
	set_actif(0);
	
	idle();
	
    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

/* #include <cpu.h> */
/* #include <inttypes.h> */

/* #include <stdio.h> */
/* #include "clock.h" */
/* //#include "context.h" */

/* // on peut s'entrainer a utiliser GDB avec ce code de base */
/* // par exemple afficher les valeurs de x, n et res avec la commande display */

/* // une fonction bien connue */
/* uint32_t fact(uint32_t n) */
/* { */
/*     uint32_t res; */
/*     if (n <= 1) { */
/*         res = 1; */
/*     } else { */
/*         res = fact(n - 1) * n; */
/*     } */
/*     return res; */
/* } */

/* #define STACK_LIMIT 512 */
/* #define NB_PROCESS 2 */
/* typedef enum STATE {ELU, RDY} STATE; */

/* typedef struct Process { */
/* 	int32_t pid; */
/* 	char* nom; */
/* 	STATE state; */
/* 	int32_t registers[5]; */
/* 	int32_t stack[STACK_LIMIT]; */
/* } Process; */

/* static Process* process_table[NB_PROCESS]; */
/* int32_t process_actif; */

/* int32_t* get_esp(int32_t pid){ return process_table[pid] -> registers;} */
/* extern void ctx_sw(int32_t* old_context, int32_t* new_context); */


/* void ordonnance(void){ */
/* 	int new_process = 0; */
/* 	if(process_actif == 0) new_process = 1; */

/* 	process_table[process_actif] -> state = RDY; */
/* 	process_table[new_process] -> state = ELU; */

/* 	process_actif = new_process; */
/* 	ctx_sw(get_esp(new_process), get_esp(process_actif)); */
/* } */

/* char* mon_nom(){ return process_table[process_actif] -> nom;} */
/* int32_t mon_pid(){ return process_table[process_actif] -> pid;} */

/* void idle(void) */
/* { */
/* 	for (;;) { */
/* 		printf("[%s] pid = %i\n", mon_nom(), mon_pid()); */
/* 		ordonnance(); */
/* 	} */
/* } */

/* void proc1(void) */
/* { */
/* 	for (;;) { */
/* 		printf("[%s] pid = %i\n", mon_nom(), mon_pid()); */
/* 		ordonnance(); */
/* 	}	 */
/* } */

/* void kernel_start(void) */
/* { */
/* 	//seance 1 */
/*     /\* uint32_t x = fact(5); *\/ */
/*     /\* // quand on saura gerer l'ecran, on pourra afficher x *\/ */

/* 	/\* printf("%i",x); *\/ */
/* 	/\* char c = 1; *\/ */
/* 	/\* printf("\n"); *\/ */
/* 	/\* printf("%i",x); *\/ */
/* 	/\* printf("%c",c); *\/ */

/* 	//seance 2 */

/* 	/\* sti();//demasquage des interruptions externes *\/ */
/* 	/\* masque_IRQ(0,0); *\/ */
/* 	/\* init_traitant_IT(32, traitant_IT_32); *\/ */
/* 	/\* print_uptime("test",4); *\/ */

/* 	//seance 3 */
/* 	/\* typedef enum STATE {ELU, RDY} STATE; //didn't succeed to clean include *\/ */
/* 	printf("test"); */
/* 	Process p0, p1; */
/* 	p0.pid = 0; */
/* 	p0.nom = "idle"; */
/* 	p0.state = ELU; */

/* 	p1.pid = 1; */
/* 	p1.nom = "proc1"; */
/* 	p1.state = RDY; */
/* 	p1.registers[1] = (int32_t) &(p1.stack[STACK_LIMIT - 1]); */
/* 	p1.stack[STACK_LIMIT - 1] = (int32_t) proc1; */
	
/* 	process_table[0] = &p0; */
/* 	process_table[1] = &p1; */

/* 	process_actif = 0; */
/* 	idle(); */
	
/*     // on ne doit jamais sortir de kernel_start */
/*     while (1) { */
/*         // cette fonction arrete le processeur */
/*         hlt(); */
/*     } */
/* } */
