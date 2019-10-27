#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Structure de données représentant l'adresse postale d'un
   contact. */
struct adresse
{
    uint16_t numero;
    char *rue;
    uint32_t code_postal;
    char *pays;
};

/* Structure de données représentant un contact. */
struct contact
{
    char *prenom;
    char *nom;
    struct adresse *adr;
};


/*
   Fonction de création d'une adresse postale. Elle retourne une
   adresse postale nouvellement allouée et initialisée en fonction des
   paramètres numero, rue, code_postal et pays.
   */
static struct adresse *creer_adresse(uint16_t numero,
				     const char *rue,
				     uint16_t code_postal,
				     const char *pays)
{
    struct adresse *adr = NULL;
    adr = malloc(sizeof(struct adresse));
    adr->numero = numero;
    adr->rue = rue;
    adr->code_postal=code_postal;
    adr->pays = pays;    
    return adr;
}

/*
   Fonction de création d'un contact. A la différence de
   creer_adresse, on ne va pas retourner le contact nouvellement
   alloué et initialisé, mais on va plutôt allouer et initialiser le
   (struct contact *) dont l'adresse est passée dans le paramètre
   nouveau_contact.
   */
static void creer_contact(struct contact **nouveau_contact,
			  const char *prenom,
			  const char *nom,
			  uint16_t numero,
			  const char *rue,
			  uint16_t code_postal,
			  const char *pays)
{
    *nouveau_contact = malloc(sizeof(struct contact));
    (*nouveau_contact)->adr = creer_adresse(numero,rue,code_postal,pays);
    (*nouveau_contact)->nom = nom;
    (*nouveau_contact)->prenom = prenom;    
}

/*
   Libère l'adresse postale passée en paramètre. En sortie, le pointeur
   qui pointait sur cette adresse vaut NULL.
   */
static void liberer_adresse(struct adresse **adr)
{
    free(*adr);
    *adr = NULL;
}

/*
   Libère le contact passé en paramètre. Notez qu'ici, on ne spécifie
   rien sur la valeur que doit prendre le pointeur qui pointait sur le
   contact libéré après exécution de la fonction liberer_contact.
   */
static void liberer_contact(struct contact *c)
{
    struct adresse *p_adr = c->adr;
    struct adresse **p_p_adr = &p_adr;
    liberer_adresse(p_p_adr);
    free(c);
}

/*
   Affiche le contact passé en paramètre (son prénom, son nom, son
   adresse) sur la sortie standard.
   */
static void afficher_contact(struct contact *c)
{
    printf("%s %s:\n", c->prenom, c->nom);
    printf("%hu %s %u %s\n", c->adr->numero, c->adr->rue, c->adr->code_postal, c->adr->pays);
}


int main(void)
{
    struct contact *led_zep = NULL, *acdc = NULL;
    creer_contact(&led_zep, "Led", "Zeppelin", 1, "Stairway to Heaven", 1977, "UK");
    creer_contact(&acdc, "AC", "DC", 666, "Highway to Hell", 1979, "Australia/UK");

    afficher_contact(led_zep);
    afficher_contact(acdc);

    liberer_contact(led_zep);
    liberer_contact(acdc);
    return EXIT_SUCCESS;
}
