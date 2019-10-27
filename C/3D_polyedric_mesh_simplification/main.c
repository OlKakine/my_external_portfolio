/* 
 * File:   main.c
 * Author: checchio
 *
 * Created on April 15, 2019, 8:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "offio.h"
#include "print_mesh.h"
#include "coherence.h"
#include "list.h"
#include "collapse.h"

void simplify(struct mesh*, uint32_t);
bool comparaison_hedge(struct half_edge *hedge1, struct half_edge* hedge2);

int main(int argc, char** argv) {
    
    struct mesh *mesh = off_load("maillages/octahedron.off");
    
    if(mesh != NULL){
        //print_mesh(mesh);
        //printf("%i\n",coherence_maillage(*mesh));
        simplify(mesh, list_size(mesh->hedges)/4);
        
        off_save("test.off",mesh);
    
        free_mesh(mesh);
    }
    return (EXIT_SUCCESS);
}

void simplify(struct mesh* mesh, uint32_t objectif_edge){
    list_merge_sort(mesh->hedges, comparaison_hedge);
    
    while((list_size(mesh->hedges)/2) > objectif_edge){
        collapse_half_edge(mesh, list_front(mesh->hedges));
        list_insertion_sort(mesh->hedges, comparaison_hedge);
    }
};

bool comparaison_hedge(struct half_edge *hedge1, struct half_edge* hedge2){
    return hedge1->norme < hedge2->norme;
}