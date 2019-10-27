#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact;

/*************************/
/* Gestion d'un contact  */
/*************************/

/*
  Retourne un nouveau contact initialisé à l'aide des paramètres name et num.
*/
extern struct contact *contact_create(const char *name, const char *num);

/*
  Libère la mémoire associée au contact c.
*/
extern void contact_free(struct contact *c);

/*
  Retourne le nom du contact passé en paramètre.
*/
extern char *contact_get_name(struct contact *c);

/*
  Retourne le numéro du contact passé en paramètre.
*/
extern char *contact_get_num(struct contact *c);

/*
  Remplace le nom du contact passé en paramètre par _name_.
  Retourne l'ancien nom.
*/
extern char *contact_set_name(struct contact *c, const char *name);

/*
  Remplace le numéro du contact passé en paramètre par _num_.
  Retourne l'ancien numéro.
*/
extern char *contact_set_num(struct contact *c, const char *num);

/************************************/
/* Gestion d'une liste de contacts. */
/************************************/

/*
  Ajoute le contact c en tête de la liste list. list représente l'adresse de la
  première cellule de la liste à modifier.
*/
extern void contact_list_push(struct contact **list, struct contact *c);

/*
  Retire le contact en tête de la liste _list_. _list_ représente l'adresse de
  la première cellule de la liste à modifier. Retourne le contact retiré.
*/
extern struct contact *contact_list_pop(struct contact **list);

/*
  Recherche le contact de nom _name_ dans la liste de contacts représentée par
  _list_. Retourne le contact trouvé si _name_ appartient à la liste, et NULL
  sinon. prev est un paramètre de sortie qui contiendra l'adresse du contact
  précédant le contact trouvé.
 */
extern struct contact *contact_list_lookup(struct contact *list,
                                           const char *name,
                                           struct contact **prev);

/*
  Retire le contact de nom _name_ du chainage pointé par _list_. Retourne le
  struct contact associé au contact retiré, et NULL si aucun contact de ce nom
  ne figure dans la liste.
 */
extern struct contact *contact_list_remove(struct contact **list, const char *nom);

/*
  Libère l'intégralité des contacts présents dans la liste pointée par _list_.
*/
extern void contact_list_free(struct contact *list);

/*
  Affiche la liste de contacts passée en paramètre.
*/
extern void contact_list_print(struct contact *list);

#endif /* _CONTACT_H_ */
