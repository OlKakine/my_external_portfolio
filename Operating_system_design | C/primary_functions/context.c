#include <inttypes.h>
#include <stdlib.h>

#define STACK_LIMIT 512
#define NB_PROCESS 2
typedef enum STATE {ELU, RDY} STATE;
extern void ctx_sw(int32_t* old_context, int32_t* new_context);

//TODO: add better gestion idle

typedef struct Process {
	int32_t pid;
	char* nom;
	STATE state;
	int32_t registers[5];
	int32_t stack[STACK_LIMIT];
} Process;

static Process process_table[NB_PROCESS];
int32_t process_actif;

void add_process(int32_t pid, char* nom, STATE state){
	Process p = process_table[pid];
	p.pid = pid;
	p.nom = nom;
	p.state = state;

	process_table[pid] = p;
	p.registers[1] = (int32_t) & p.stack[STACK_LIMIT-1];	//esp
}

void set_function_address(int32_t pid,  void (*f)(void)){
	process_table[pid].stack[STACK_LIMIT - 1] = (int32_t)f;
}

void set_actif(int32_t pid) {process_actif = pid;}

void link_function(int32_t pid, void (*f) ()){
	process_table[pid].stack[STACK_LIMIT - 1] = (int32_t) f;
}

int32_t* get_esp(int32_t pid){ return process_table[pid].registers;}

void ordonnance(void){
	int new_process = 0;
	if(process_actif == 0) new_process = 1;

	process_table[process_actif] . state = RDY;
	process_table[new_process] . state = ELU;

	process_actif = new_process;
	ctx_sw(get_esp(new_process), get_esp(process_actif));
}

char* mon_nom(){ return process_table[process_actif] . nom;}
int32_t mon_pid(){ return process_table[process_actif] . pid;}



