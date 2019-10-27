/*
  Test du module contact.

  Crée un nouveau contact, puis le libère.
 */

#include <stdlib.h>

#include <contact.h>

int main(void)
{
    struct contact *c = contact_create("Colonel Moutarde", "0612345678");
    contact_list_print(c);
    contact_free(c);

    return EXIT_SUCCESS;
}
