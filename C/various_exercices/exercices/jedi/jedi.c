#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define SIZE 20     // taille maximale d'un champ de caractères : nom, prénom, planète
#define MAXLINELENGTH 100

/* Structure d'une fiche de données Jedi */
struct jedi {
    uint32_t    isj;		    // Identifiant Spatial Jedi : identifiant unique, c'est l'INE des Jedi
    char        nom[SIZE];
    char        prenom[SIZE];
    uint16_t    age;
    float       taille;
    char        planete[SIZE];
};

/*
    Affiche tous les champs de la fiche Jedi passée en paramètre.
    Fonction utilisée par print_isj.
*/
void print_jedi(struct jedi *jedi)
{
    /* A compléter */
    printf("ISJ: %"PRIu32"\n", jedi->isj);
    printf("nom: %s\n", jedi->nom);
    printf("prenom: %s\n", jedi->prenom);
    printf("age: %"PRIu16"\n", jedi->age);
    printf("taille: %1.2f\n", jedi->taille);
    printf("planete: %s\n", jedi->planete);
}

/*
    Recherche et lit une fiche Jedi dans le fichier binaire bin
    en y accédant directement par la clé identifiant isj et affiche
    tous les champs de la fiche trouvée (appel à la fonction print_jedi).
    Retourne 1 en cas de problème, 0 sinon.

    bin : nom du fichier binaire
    isj : Identifiant Spatial Jedi recherché
*/
int16_t print_isj(char *bin, uint32_t isj)
{
    /* A compléter */
    FILE * in = fopen(bin, "rb");
    struct jedi jedi;
    
    printf("%u\n",isj);
    
    fseek(in, isj * sizeof(struct jedi), SEEK_SET);
    
    fread(&jedi, sizeof(struct jedi),1,in);
    print_jedi(&jedi);
    
    fclose(in);
}

/*
    Lit dans le fichier texte (in) toutes les fiches Jedi et les écrit
    dans un fichier binaire. L'identifiant isj fera office de clé d'accès
    direct dans le fichier binaire de sortie (out)
    Retourne 1 en cas de problème, 0 sinon.

    in  : nom du fichier entrée texte (ex : r2.txt)
    out : nom du fichier sortie binaire (ex : d2.bin)

    NOTA BENE :

    Lecture texte :
    On utilisera une variable intermédiaire de type struct jedi
    pour stocker les valeurs lues dans le fichier d'entrée.
    La lecture caractère par caractère ne sera pas utilisée.
    La lecture des fiches du fichier d'entrée texte doit s'effectuer
    obligatoirement en utilisant les fonctions parmi : fgets, sscanf, fscanf
    Solution 1 : fgets + sscanf. Solution 2 : fscanf
    Coder les 2 solutions
    Quand les 2 solutions marcheront bien, amusez vous à supprimer le code isj d'une
    des lignes du fichier r2.txt
    Puis réessayez solution 1 et solution 2. Que constatez vous ?


    Ecriture binaire : on écrira directement la variable de type struct jedi à
    l'emplacement jedi.isj du fichier binaire
*/
int16_t convert_to_bin(char *in, char *out)
{
    struct jedi jedi;
    /* A compléter */
    FILE* text_file = fopen(in,"r");
    FILE* bin_file = fopen(out,"wb");
    
    char line[MAXLINELENGTH];        
    while(fgets(line,MAXLINELENGTH,text_file) != NULL){
        sscanf(line,"%u %s %s %u %f %s", &jedi.isj, jedi.nom, jedi.prenom, &jedi.age, &jedi.taille, jedi.planete);   
        
        fseek(bin_file, jedi.isj * sizeof(struct jedi), SEEK_SET);
        fwrite(&jedi, sizeof(struct jedi), 1, bin_file);
    }
        
    fclose(text_file);
    fclose(bin_file);
}

/*
    main : à écrire complètement
    3 paramètres sont passés au programme (cf. argc, argv):
    - nom fichier texte entree
    - nom fichier binaire sortie
    - identifiant isj recherché
    Exemple d'utilisation :
    ./jedi r2.txt d2.bin 1977
    main effectue les traitements suivants :
    - vérifier que les 3 paramètres attendus sont bien présents, les récupérer
    - appeler convert_to_bin avec les paramètres adéquates
    - appeler print_isj avec les paramètres adéquates
*/

int main(int argc, char ** argv){
    if(argc != 4){
        puts("ERREUR PARAM: format attendu: <nom fichier texte entree> <nom fichier binaire sortie> <identifiant isj recherché>");
        return EXIT_FAILURE;
    }
    
    
    convert_to_bin(argv[1],argv[2]);
    print_isj(argv[2],(uint32_t) strtoul(argv[3],NULL, 10));
    return EXIT_SUCCESS;
}