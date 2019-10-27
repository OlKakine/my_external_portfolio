/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <sys/mman.h>
#include <assert.h>
#include <stdint.h>
#include "mem.h"
#include "mem_internals.h"

unsigned long knuth_mmix_one_round(unsigned long in)
{
    return in * 6364136223846793005UL % 1442695040888963407UL;
}

//added function to compute the final magic number
unsigned long magic_final_number(unsigned long in, MemKind k)
{
	unsigned long magic = knuth_mmix_one_round(in);
	magic = magic & ~(0b11UL);
	magic = magic | k ;
	return magic;
}

void *mark_memarea_and_get_user_ptr(void *ptr, unsigned long size, MemKind k)
{
	// size in octet and is the final size including padding
	unsigned long magic = magic_final_number((unsigned long)ptr, k);
	
	unsigned long * ptr_lu = (unsigned long*) ptr;
	*ptr_lu++ = size;
  
	*ptr_lu = magic;
	ptr = (void *) ++ptr_lu;

	char * ptr_c = (char *)ptr_lu; // decalage de taille utile
	ptr_c += (size-32);
	ptr_lu = (unsigned long*)ptr_c;
	
	*ptr_lu++ = magic;
	*ptr_lu = size;
	
    return (void *) ptr;
}

Alloc
mark_check_and_get_alloc(void *ptr)
{
    Alloc a = {};
	unsigned long * ptr_lu = (unsigned long*) ptr;
	ptr_lu -= 2;// se met au debut du marquage
	a.ptr = ptr_lu;
	
	a.size = *ptr_lu;

	
	if(a.size <= CHUNKSIZE) a.kind = SMALL_KIND;
	else if(a.size >= LARGEALLOC+32) a.kind = LARGE_KIND;
	else a.kind = MEDIUM_KIND;
	
	ptr_lu++;
	
	unsigned long magic_read = *ptr_lu;
	unsigned long magic_expected = magic_final_number((unsigned long)a.ptr, a.kind);

	if(magic_read!=magic_expected)
		printf("Expected %lx, actual %lx, kind %u, size %lu", magic_expected, magic_read, a.kind, a.size );
	assert(magic_read == magic_expected);

	char * ptr_c = (char *)ptr_lu;//decalage de taille utile
	ptr_c += a.size - 24;
	ptr_lu = (unsigned long*)ptr_c;

	if(magic_read != *ptr_lu)
		printf("Expected %lx, actual %lx, kind %u \n", magic_read, *ptr_lu, a.kind);
	
	assert(magic_read = *ptr_lu);
	ptr_lu++;
	assert(a.size = *ptr_lu);
	
    return a;
}


unsigned long
mem_realloc_small() {
    assert(arena.chunkpool == 0);
    unsigned long size = (FIRST_ALLOC_SMALL << arena.small_next_exponant);
    arena.chunkpool = mmap(0,
			   size,
			   PROT_READ | PROT_WRITE | PROT_EXEC,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   -1,
			   0);
    if (arena.chunkpool == MAP_FAILED)
	handle_fatalError("small realloc");
    arena.small_next_exponant++;
    return size;
}

unsigned long
mem_realloc_medium() {
    uint32_t indice = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant;
    assert(arena.TZL[indice] == 0);
    unsigned long size = (FIRST_ALLOC_MEDIUM << arena.medium_next_exponant);
    assert( size == (1 << indice));
    arena.TZL[indice] = mmap(0,
			     size*2, // twice the size to allign
			     PROT_READ | PROT_WRITE | PROT_EXEC,
			     MAP_PRIVATE | MAP_ANONYMOUS,
			     -1,
			     0);
    if (arena.TZL[indice] == MAP_FAILED)
	handle_fatalError("medium realloc");
    // align allocation to a multiple of the size
    // for buddy algo
    arena.TZL[indice] += (size - (((intptr_t)arena.TZL[indice]) % size));
    arena.medium_next_exponant++;
    return size; // lie on allocation size, but never free
}


// used for test in buddy algo
unsigned int
nb_TZL_entries() {
    int nb = 0;
    
    for(int i=0; i < TZL_SIZE; i++)
	if ( arena.TZL[i] )
	    nb ++;

    return nb;
}
