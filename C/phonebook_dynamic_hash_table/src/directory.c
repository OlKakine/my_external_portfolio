
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>

struct dir{
	uint32_t len;
	uint32_t nb_contact;
	struct contact **lists;
};

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    struct contact **lists= calloc(len,sizeof(struct contact*));
	struct dir *dir = malloc(sizeof(struct dir));
	dir->lists = lists;
	dir->len = len;
	dir->nb_contact = 0;
	
	return dir;
}

/*
  Redimensionne dynamiquement la table de hachage si besoin lors d'un ajout ou retrait
  de contact.
  On laisse la possibilité de donner une taille fixe initiale au dir puis un série d'ajout
  jusqu'a 75% sans redimensionnement dynamique: 
  le redimensionnement n'a lieu que lors d'un ajout et dépassement de 75%
  ou d'un retrait quand nb contact < 15% de len de dir et nb contact > 10.
*/
void dir_resize(struct dir *dir, bool is_insert){
	uint32_t new_size;
	
	if( ((4*dir->nb_contact) > (3*dir->len)) && is_insert ){//nb_contact depasse 75% de len
		new_size = 2*dir->len;
	}
	else if( (20*dir->nb_contact) < (3*dir->len)
			 && !is_insert
			 && dir->len > 10){//nb_contact < 15% de len
		new_size = dir->len / 2 ;
		new_size = new_size < 10 ? 10 : new_size; //on met new_size à 10 au minimum
	}
	else return;//sinon on ne fait rien

	struct contact *contact_to_move; //can be implemented in contact.c move a list to another
	struct contact **new_lists = calloc(new_size,sizeof(struct contact*));
	struct contact *old_list;
	for(int i=0; i<dir->len; i++){
		old_list = (dir->lists)[i];
		contact_to_move = contact_list_pop(&old_list);
		
		while(contact_to_move != NULL){
			char *contact_name = contact_get_name(contact_to_move);
			uint32_t ind_list = (hash(contact_name)%(new_size));
			struct contact **p_list = &(new_lists[ind_list]);
			
			contact_list_push(p_list, contact_to_move);
			contact_to_move = contact_list_pop(&old_list);
		}		
	}
	free(dir->lists);
	dir->len = new_size;
	dir->lists = new_lists;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
	uint32_t ind_list = (hash(name)%(dir->len));
	struct contact **p_list = &((dir->lists)[ind_list]); //pointeur vers la liste concernée
	struct contact *prev = NULL;//prev inutile ici
	
	struct contact *new = contact_list_lookup(*p_list, name, &prev);
	char *ancien = NULL;

	if(new != NULL) ancien = contact_set_num(new, num);
	else {
		contact_list_push(p_list, contact_create(name,num));
		dir->nb_contact++;
		dir_resize(dir,true);
	}
	
	return ancien;
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t ind_list = hash(name) % (dir->len);
	struct contact *list = (dir->lists)[ind_list];

	struct contact *prev = NULL;//prev inutile ici
	struct contact *contact_found = contact_list_lookup(list, name, &prev);

	if(contact_found == NULL) return NULL;

	return contact_get_num(contact_found);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
	uint32_t ind_list = hash(name) % (dir->len);
	struct contact **p_list = &((dir->lists)[ind_list]);

	struct contact *to_remove = contact_list_remove(p_list,name);
	if(to_remove != NULL) {
		contact_free(to_remove);
		dir->nb_contact--;
		dir_resize(dir,false);
	}
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for(int i=0; i<dir->len; i++) contact_list_free((dir->lists)[i]);
	free(dir->lists);
	free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
	puts("Debut annuaire:");
	for(int i=0; i<dir->len; i++) contact_list_print((dir->lists)[i]);
	puts("Fin annuaire.");
}

