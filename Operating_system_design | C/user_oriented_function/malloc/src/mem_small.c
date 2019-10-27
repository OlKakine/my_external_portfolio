/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <assert.h>
#include "mem.h"
#include "mem_internals.h"
#include <string.h>
#include <stdint.h>

void *
emalloc_small(unsigned long size)
{
    /* ecrire votre code ici */
	
	if(arena.chunkpool == NULL){
		unsigned long new_size = mem_realloc_small();//we ask for more space
		
		void* current_chunk = arena.chunkpool;
		for(unsigned long i=0; i<new_size/CHUNKSIZE -1 ; i++){
			void* next_chunk = (unsigned long*)current_chunk + CHUNKSIZE/8;
			*(void**)current_chunk = next_chunk;
			current_chunk = next_chunk;
		} 
	}

	void* p_next_chunk =  *((void**)arena.chunkpool);
	
	void* ptr = mark_memarea_and_get_user_ptr(arena.chunkpool, CHUNKSIZE, SMALL_KIND);

	arena.chunkpool = p_next_chunk;
	
    return (void *) ptr;
}

void efree_small(Alloc a) {
    /* ecrire votre code ici */
	memset(a.ptr, 0, CHUNKSIZE);
	void** current_chunk = (void**) a.ptr;
	*current_chunk = arena.chunkpool;
	arena.chunkpool = a.ptr;
}
