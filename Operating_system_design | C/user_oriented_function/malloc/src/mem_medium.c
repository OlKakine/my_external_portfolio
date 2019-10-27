/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <stdint.h>
#include <assert.h>
#include "mem.h"
#include "mem_internals.h"
#include "string.h"

void* recursive_tzl_division(unsigned int i_desired, unsigned int i_first_free,
							 unsigned long size);

unsigned int puiss2(unsigned long size) {
    unsigned int p=0;
    size = size -1; // allocation start in 0
    while(size) {  // get the largest bit
	p++;
	size >>= 1;
    }
    if (size > (1 << p))
	p++;
    return p;
}


void *
emalloc_medium(unsigned long size)
{
    assert(size < LARGEALLOC);
    assert(size > SMALLALLOC);
    /* ecrire votre code ici */
	void* ptr = NULL;
	
	unsigned int ind_tzl = puiss2(size+32);
	
	if(arena.TZL[ind_tzl] != NULL){ //si bloc de la bonne taille disponible
		void* p_block_to_be_used = arena.TZL[ind_tzl];
		arena.TZL[ind_tzl] = *((void**)arena.TZL[ind_tzl]);
		ptr = mark_memarea_and_get_user_ptr(p_block_to_be_used, size+32, MEDIUM_KIND);	
	}		
	else {
		unsigned int i_first_free = ind_tzl;
		unsigned int i_max = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant;
		while(1){
			if(arena.TZL[i_first_free] != NULL) break;
			i_first_free++;
			//on rajoute un bloc de taille max
			//s'il n'y a pas de bloc free de taille sup
			if(i_first_free >= i_max) mem_realloc_medium();
		}
		ptr = recursive_tzl_division(ind_tzl, i_first_free, size+32);		
	}
	
    return (void *) ptr;
}

//added
//i_size is the log2 of the block's size (also indice of corresponding tzl table)
void* compute_buddy_address(void* ptr, unsigned int i_size){
	return (void*) ((uintptr_t)ptr ^ 1<<(i_size));
}

//added
//requirement: i_first_free > i_desired
//return the address of a marked block of the size we are looking for
//
//i_desired indicates which size of block we are looking for (in pow of two)
//i_first_free is the indice of the tzl table containing a free block of sup size
void* recursive_tzl_division(unsigned int i_desired, unsigned int i_first_free,
							 unsigned long size){
	
	void* bloc_free = arena.TZL[i_first_free];
	//on pointe tzl[first free] vers son hypothetique deuxieme bloc free
	arena.TZL[i_first_free] = *(void**)bloc_free;

	void* p_buddy_new_first_free = compute_buddy_address(bloc_free, i_first_free-1);
	
	if(i_desired == i_first_free - 1){//when block free is double of desired size
		arena.TZL[i_desired] = p_buddy_new_first_free;
		return mark_memarea_and_get_user_ptr(bloc_free, size, MEDIUM_KIND);	
	}
	else{//else we divide the first block free into two smaller one
		 // and recursively continue applying this algo on the 'left' small block
		arena.TZL[i_first_free-1] = bloc_free;
		*((void**)bloc_free) = p_buddy_new_first_free;
		return recursive_tzl_division(i_desired, i_first_free - 1, size);
	}	
}

//added
void add_to_tzl(void* bloc, unsigned int ind){
	*((void**)bloc) = arena.TZL[ind];
	arena.TZL[ind] = (void**)bloc;
}

void efree_medium(Alloc a) {
    /* ecrire votre code ici */
	memset(a.ptr, 0, a.size);
	unsigned int i_tzl = puiss2(a.size);
	void* p_buddy = compute_buddy_address(a.ptr, i_tzl);

	void** list_blocs_free = arena.TZL[i_tzl];
	if(list_blocs_free == NULL)	{//if list is empty we add the block as head
		arena.TZL[i_tzl] = a.ptr;
		return;
	}

	void** last_checked_bloc = list_blocs_free;
	while(list_blocs_free != NULL && list_blocs_free!=p_buddy){
		//we explore the list looking for the buddy block
		last_checked_bloc = list_blocs_free;
		list_blocs_free = (void**) *list_blocs_free;			
	}

	if(list_blocs_free == NULL)//buddy encore alloue
		*last_checked_bloc = a.ptr; //on ajoute le block a la fin de la liste
	else{//buddy is free
		void* left_bloc = p_buddy < a.ptr ? p_buddy : a.ptr;
		//on enleve le buddy de la liste

		//this steps can be better coded
		if(arena.TZL[i_tzl] == p_buddy){//buddy is head of the list
			arena.TZL[i_tzl] = *(void**) p_buddy;
			memset(p_buddy, 0, a.size);
			if(arena.TZL[i_tzl+1]==NULL){//we need to stop freeing bigger blocs
				arena.TZL[i_tzl+1] = left_bloc;
				return;
			}
		}
		else{
			*last_checked_bloc = *(void**) p_buddy;//delete buddy from tzl[i_tzl]
			if(arena.TZL[i_tzl+1]==NULL){
				arena.TZL[i_tzl+1] = left_bloc;
				return;
			}
		}
			
		//we recursively free the bigger block(s) obtained
		
		//Alloc b = {left_bloc, a.kind, a.size*2};
		Alloc b ={};
		b.ptr = left_bloc;
		b.kind = a.kind;
		b.size = 1<<(i_tzl+1);

		efree_medium(b);	   
	}
}


