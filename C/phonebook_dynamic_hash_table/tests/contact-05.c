/*
  Test du module contact.

  Créé un contact et change son numéro.
 */

#include <stdlib.h>
#include <stdio.h>

#include <contact.h>

int main(void)
{
    struct contact *c = contact_create("Caporal Ketchup", "06987654321");
    contact_list_print(c);
    char *oldnum = contact_set_num(c, "3615");
    printf("%s avait un autre numéro avant, c'était le %s. Maintenant c'est %s.\n",
           contact_get_name(c),
           oldnum,
           contact_get_num(c));
    contact_list_print(c);

    free(oldnum);
    contact_free(c);

    return EXIT_SUCCESS;
}
