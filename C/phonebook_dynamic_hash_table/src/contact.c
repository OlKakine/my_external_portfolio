/* TODO! */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*
  Un contact représente une association {nom, numéro}.
*/
struct contact{
	char *nom;
	char *numero;
	struct contact *suivant;
};

/*************************/
/* Gestion d'un contact  */
/*************************/

/*
  Retourne un nouveau contact initialisé à l'aide des paramètres name et num.
*/
struct contact *contact_create(const char *name, const char *num){
	int len = strlen(name);
	char *nom = malloc((len+1)*sizeof(char));
	strcpy(nom, name);
	
	len = strlen(num);
	char *numero = malloc((len+1)*sizeof(char));
	strcpy(numero,num);

	struct contact *contact = malloc(sizeof(struct contact));
	contact->nom = nom;
	contact->numero = numero;
	contact->suivant = NULL;

	return contact;	
};

/*
  Libère la mémoire associée au contact c.
*/
extern void contact_free(struct contact *c){
	free(c->nom);
	free(c->numero);
	free(c);
};

/*
  Retourne le nom du contact passé en paramètre.
*/
char *contact_get_name(struct contact *c){
	return c->nom;
};

/*
  Retourne le numéro du contact passé en paramètre.
*/
char *contact_get_num(struct contact *c){
	return c->numero;
};

/*
  Remplace le nom du contact passé en paramètre par _name_.
  Retourne l'ancien nom.
*/
char *contact_set_name(struct contact *c, const char *name){
	char *oldname = c->nom;
	
	int len = strlen(name);
	char *nom = malloc((len+1)*sizeof(char));

	strcpy(nom, name);
	c->nom = nom;

	return oldname;
};

/*
  Remplace le numéro du contact passé en paramètre par _num_.
  Retourne l'ancien numéro.
*/
char *contact_set_num(struct contact *c, const char *num){
	char *oldnum = c->numero;
	
	int len = strlen(num);
	char *numero = malloc((len+1)*sizeof(char));

	strcpy(numero, num);
	c->numero = numero;

	return oldnum;
   
};

/************************************/
/* Gestion d'une liste de contacts. */
/************************************/

/*
  Ajoute le contact c en tête de la liste list. list représente l'adresse de la
  première cellule de la liste à modifier.
*/
void contact_list_push(struct contact **list, struct contact *c){
	if(c == NULL) return;
	
	c->suivant = *list;
	*list = c;
};

/*
  Retire le contact en tête de la liste _list_. _list_ représente l'adresse de
  la première cellule de la liste à modifier. Retourne le contact retiré.
*/
struct contact *contact_list_pop(struct contact **list){
	if(*list == NULL) return NULL;
	
	struct contact *popped = *list;
	*list = popped->suivant;
	popped->suivant = NULL;
	
	return popped;
};

/*
  Recherche le contact de nom _name_ dans la liste de contacts représentée par
  _list_. Retourne le contact trouvé si _name_ appartient à la liste, et NULL
  sinon. prev est un paramètre de sortie qui contiendra l'adresse du contact
  précédant le contact trouvé.
 */
struct contact *contact_list_lookup(struct contact *list, const char *name,	struct contact **prev){
	struct contact *current = list;
	*prev = NULL;
	
	while(current != NULL){
		if(strcmp(current->nom, name)==0){
			return current;
		}
		*prev = current;
		current = current->suivant;
	}
	*prev = NULL;
	return NULL;
};

/*
  Retire le contact de nom _name_ du chainage pointé par _list_. Retourne le
  struct contact associé au contact retiré, et NULL si aucun contact de ce nom
  ne figure dans la liste.
 */
struct contact *contact_list_remove(struct contact **list, const char *nom){
	struct contact *prev;
	struct contact *to_remove = contact_list_lookup(*list, nom, &prev);
	
	if(to_remove == NULL) return NULL;
	
	if(prev == NULL) *list = to_remove->suivant;
	else prev->suivant = to_remove->suivant;

	to_remove->suivant = NULL;
	return to_remove;
};

/*
  Libère l'intégralité des contacts présents dans la liste pointée par _list_.
*/
void contact_list_free(struct contact *list){
	struct contact *current = list;
	struct contact *suivant = NULL;
	while(current != NULL){
		suivant = current->suivant;
		contact_free(current);
		current = suivant;
	}
	//PB: list pointe alors vers une zone de mémoire libérée.
};

/*
  Affiche la liste de contacts passée en paramètre.
*/
void contact_list_print(struct contact *list){
	if(list == NULL){
		printf("{}\n");
		return;
	}
	
	struct contact *current = list;
	printf("{\n");
	while(current != NULL){
		printf(" %s : %s\n", current->nom, current->numero);
		current = current->suivant;
	}
	printf("}\n");
};
