/*
  Test du module contact.

  Crée deux contacts, les chaine ensemble, effectue trois recherches, puis les
  libère.
 */

#include <stdlib.h>
#include <stdio.h>

#include <contact.h>

int main(void)
{
    struct contact *list = contact_create("Colonel Moutarde", "0612345678");
    struct contact *c = contact_create("Caporal Ketchup", "06987654321");

    contact_list_push(&list, c);
    contact_list_print(list);

    const char *names[3] = {
        "Caporal Ketchup",
        "Colonel Moutarde",
        "Tartempion"
    };

    for (size_t i = 0; i < 3; i++) {
        struct contact *prev = NULL;
        c = contact_list_lookup(list, names[i], &prev);
        if (c == NULL) {
            printf("%s n'appartient pas à la liste!\n", names[i]);
        } else {
            printf("%s appartient à la liste, ", names[i]);
            if (prev == NULL) {
                printf("et c'est le 1er!\n");
            } else {
                printf("et son précédent est %s!\n", contact_get_name(prev));
            }
        }
    }

    contact_list_free(list);

    return EXIT_SUCCESS;
}
