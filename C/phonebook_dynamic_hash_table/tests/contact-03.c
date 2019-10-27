/*
  Test du module contact.

  Crée deux contacts, les chaine ensemble, les retire un par un, puis les
  libère.
 */

#include <stdlib.h>

#include <contact.h>

int main(void)
{
    struct contact *list = contact_create("Colonel Moutarde", "0612345678");
    struct contact *c = contact_create("Caporal Ketchup", "06987654321");

    contact_list_push(&list, c);
    contact_list_print(list);

    c = contact_list_remove(&list, "Colonel Moutarde");
    contact_free(c);
    contact_list_print(list);

    c = contact_list_remove(&list, "Caporal Ketchup");
    contact_free(c);
    contact_list_print(list);

    contact_list_free(list);

    return EXIT_SUCCESS;
}
