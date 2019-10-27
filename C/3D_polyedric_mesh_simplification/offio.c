/* 
 * File:   offio.c
 * Author: checchio
 * 
 * Created on April 15, 2019, 6:50 PM
 */
#include "offio.h"
#include <stdio.h>
#include <math.h>
#define MAXLINE 40

bool load_faces(FILE* in, struct mesh* mesh, int nb_faces, struct list** vertices_leaving_edges, struct list* origin_vertices);
bool load_vertices(FILE* in, struct mesh* mesh, int nb_vert);
bool appariate(struct mesh* mesh, struct list** vertices_leaving_edges, struct list* origin_vertices);

struct mesh* off_load(char* file_name){
    FILE* in = fopen(file_name, "r");
    
    char line[MAXLINE];
    
    if(fgets(line,MAXLINE,in)!=line){//lecture de OFF
        perror("Erreur load: ");
        fclose(in);
        return NULL;
    }
    if(strcmp(line, "OFF\n")!=0){
        fclose(in);
        fprintf(stderr, "Erreur load: OFF not found");
        return NULL;
    }
    
    if(fgets(line,MAXLINE,in)!=line){//lecture des params
        perror("Erreur load: ");
        fclose(in);
        return NULL;
    }
    uint32_t nb_vert, nb_faces, nb_hedges;
    if(sscanf(line, "%u %u %u", &nb_vert, &nb_faces, &nb_hedges) != 3){
        perror("Erreur load: wrong parameters: ");
        fclose(in);
        return NULL;
    }
    
    struct mesh* mesh = malloc(sizeof(struct mesh)); //création du mesh à remplir
    mesh->faces = list_create(sizeof(struct face));
    mesh->hedges= list_create(sizeof(struct half_edge));
    mesh->vertices = list_create(sizeof(struct vertex));
    
    struct list* vertices_leaving_edges[nb_vert];//tableau non ordonné, pour chaque sommet une liste des hedge le quittant
    for(int i=0; i<nb_vert; i++) vertices_leaving_edges[i]=list_create(sizeof(struct half_edge));
    
    struct list* origin_vertices = list_create(sizeof(struct vertex));//list indexée par le num des hedge et pr valeur le vertex d'origine
    
    //TODO: simplifier/clarifier les free en exit (appel a une fonction?)
    
    if(load_vertices(in, mesh, nb_vert) == false){
        free_mesh(mesh);
        fclose(in);
        
        for(int i=0; i<nb_vert; i++) list_free(vertices_leaving_edges[i]);
        list_free(origin_vertices);
        
        return NULL;
    }
    if(load_faces(in,mesh,nb_faces, vertices_leaving_edges, origin_vertices) == false){
        free_mesh(mesh);
        fclose(in);
        
        for(int i=0; i<nb_vert; i++) list_free(vertices_leaving_edges[i]);
        list_free(origin_vertices);
        
        return NULL;
    }
    
    fclose(in);
    
    if(appariate(mesh,vertices_leaving_edges, origin_vertices) == false){
        free_mesh(mesh);
        
        for(int i=0; i<nb_vert; i++) list_free(vertices_leaving_edges[i]);
        list_free(origin_vertices);
        
        return NULL;
    }
    
    for(int i=0; i<nb_vert; i++) list_free(vertices_leaving_edges[i]);
    list_free(origin_vertices);
    
    return mesh;   
};

bool load_vertices(FILE* in, struct mesh* mesh, int nb_vert){
    char line[MAXLINE];
    
    for(int i=0; i<nb_vert; i++){
        if(fgets(line,MAXLINE,in)!=line){//lecture des params
            perror("Erreur load vertices: ");
            return false;
        }
        struct vertex vertex;
        if(sscanf(line, "%f %f %f", &(vertex.x), &(vertex.y), &(vertex.z)) != 3){
            perror("Erreur load vertices: wrong arguments: ");
            return false;
        }
        list_push_back(mesh->vertices, &vertex);
    }
    
    return true;
    
};

bool load_faces(FILE* in, struct mesh* mesh, int nb_faces, struct list** vertices_leaving_edges, struct list* origin_vertices){
    char line[MAXLINE];
    
    for(int i=0; i<nb_faces; i++){
        if(fgets(line,MAXLINE,in)!=line){//lecture des params
            perror("Erreur load faces: ");
            return false;
        }
        uint32_t inutile, ind0, ind1, ind2;
        if(sscanf(line, "%u %u %u %u", &inutile, &ind0, &ind1, &ind2) != 4){
            perror("Erreur load faces: wrong arguments: ");
            return false;
        }
        
        struct vertex *v0 =list_element(mesh->vertices,ind0);
        struct vertex *v1 =list_element(mesh->vertices,ind1);
        struct vertex *v2 =list_element(mesh->vertices,ind2);
        
        struct half_edge hedge = {NULL, NULL, v1, NULL, NULL };
        v0->leaving_edge = list_push_back(mesh->hedges, &hedge);
                
        struct face f = {v0->leaving_edge};
        struct face *face = list_push_back(mesh->faces, &f);
        v0->leaving_edge->face = face;
        
        struct half_edge hedge1 = {NULL, v0->leaving_edge, v2, face, NULL };
        v1->leaving_edge = list_push_back(mesh->hedges, &hedge1);
        
        struct half_edge hedge2 = {v0->leaving_edge, v1->leaving_edge, v0, face, NULL };
        v2->leaving_edge = list_push_back(mesh->hedges, &hedge2);
 
        v0->leaving_edge->next = v1->leaving_edge;
        v0->leaving_edge->prev = v2->leaving_edge;
        
        v1->leaving_edge->next = v2->leaving_edge;
        
        list_push_back(vertices_leaving_edges[ind0], v0->leaving_edge);
        list_push_back(vertices_leaving_edges[ind1], v1->leaving_edge);
        list_push_back(vertices_leaving_edges[ind2], v2->leaving_edge);
        
        list_push_back(origin_vertices, v0);
        list_push_back(origin_vertices, v1);
        list_push_back(origin_vertices, v2);
    }
    return true;
    
};

bool appariate(struct mesh* mesh, struct list** vertices_leaving_edges, struct list* origin_vertices){
    list_FOR_EACH(mesh->hedges, struct half_edge*, hedge){
        struct list* vertex_leaving_edges = 
            vertices_leaving_edges[list_alloc_identifier(hedge->vertex)];//on selectionne la list de leaving_edges correspondant au vertext pointé par hedge
        
        uint32_t ind_hedge = list_alloc_identifier(hedge);
        struct vertex* origin_vertex = list_element(origin_vertices, ind_hedge);
        
        list_FOR_EACH(vertex_leaving_edges, struct half_edge*, other_hedge){
            if(other_hedge->vertex->x == origin_vertex->x && other_hedge->vertex->y == origin_vertex->y && other_hedge->vertex->z == origin_vertex->z){
                hedge->pair = other_hedge->prev->next; /*other_hedge n'est qu'une copie de la vrai hedge pair
                                                        * on recupere donc la vrai adresse 
                                                        */
                list_erase(vertex_leaving_edges, other_hedge);
                break;
            }
        }
        if(hedge->pair == NULL){
            perror("Appariement failed");
            return false;
        }
        else{
            float norme = powf(hedge->vertex->x - hedge->pair->vertex->x,2) + 
                powf(hedge->vertex->y - hedge->pair->vertex->y,2) + 
                powf(hedge->vertex->z - hedge->pair->vertex->z,2);
            hedge->norme = norme;
            hedge->pair->norme = norme;
        }
    }
    return true;
}

void off_save(char* file_name, struct mesh* mesh){
    FILE* out = fopen(file_name, "w");
    fputs("OFF\n",out);
    fprintf(out,"%u %u %u\n", list_size(mesh->vertices), list_size(mesh->faces), list_size(mesh->hedges)/2);
    
    for(int i=0; i<list_size(mesh->vertices); i++){
        struct vertex* vertex = list_element(mesh->vertices,i);
        fprintf(out,"%f %f %f\n", vertex->x,vertex->y, vertex->z );
    }
    
    for(int i=0; i<list_size(mesh->faces); i++){
        struct face* face = list_element(mesh->faces,i);
        fprintf(out,"3 %u %u %u\n", list_alloc_identifier(face->edges->next->next->vertex),
                list_alloc_identifier(face->edges->vertex), 
                list_alloc_identifier(face->edges->next->vertex));
    }
    
    fclose(out);
};