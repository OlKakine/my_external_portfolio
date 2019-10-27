/* 
 * File:   coherence.c
 * Author: checchio
 * 
 * Created on April 15, 2019, 5:28 PM
 */
#include <stdbool.h>
#include <string.h>
#include "coherence.h"
#include "list.h"

bool coherence_maillage(struct mesh mesh){
    if(coherence_null(mesh) == false) return false;
    
    if(coherence_fermeture(mesh.hedges) == false) return false;
    
    return true;    
};

bool coherence_null(struct mesh mesh){
    list_FOR_EACH(mesh.faces,struct face*,face){
        if(face->edges == NULL){
            printf("Erreur: presence de NULL dans la face");
            print_face(face);
            return false;
        }
    } 
    list_FOR_EACH(mesh.hedges,struct half_edge*,hedge){
        if((hedge->next == NULL) || (hedge->prev == NULL) || (hedge->vertex == NULL) || (hedge->face == NULL) || (hedge->pair == NULL)){
            printf("Erreur: presence de NULL dans l'half edge");
            print_half_edge(hedge);
            return false;
        }
    }
    list_FOR_EACH(mesh.vertices,struct vertex*,vertex){
        if(vertex->leaving_edge == NULL){
            printf("Erreur: presence de NULL dans le vertex");
            print_vertex(vertex);
            return false;
        }
    } 
    return true;
};

bool coherence_fermeture(struct list *hedges){
    list_FOR_EACH(hedges,struct half_edge*,hedge){
        if(hedge->pair->pair != hedge){
            printf("Erreur de fermeture: mauvais appariemment dans l'half edge\n");
            print_half_edge(hedge);
            return false;
        }
    }
    return true;
};