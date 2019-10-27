/*
  Test du module contact.

  Créé un contact et change son nom.
 */

#include <stdlib.h>
#include <stdio.h>

#include <contact.h>

int main(void)
{
    struct contact *c = contact_create("Caporal Ketchup", "06987654321");
    contact_list_print(c);
    char *oldname = contact_set_name(c, "Sergent Mayo");
    printf("%s s'appelait %s avant.\n", contact_get_name(c), oldname);
    contact_list_print(c);

    free(oldname);
    contact_free(c);
 
    return EXIT_SUCCESS;
}
