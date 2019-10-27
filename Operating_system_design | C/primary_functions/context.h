#ifndef __CONTEXT_H__
#define __CONTEXT_H__

extern void ctx_sw(int32_t* old_context, int32_t* new_context);
typedef enum STATE {ELU, RDY} STATE;
extern void add_process(int32_t pid, char* nom, STATE state);
extern void set_function_address(int32_t pid,  void (*f)(void));
extern int32_t* get_esp(int32_t pid);
extern void link_function(int32_t pid, void (*f) ());
extern void set_actif(int32_t pid);
extern void ordonnance(void);
extern char* mon_nom();
extern int32_t mon_pid();

#endif
