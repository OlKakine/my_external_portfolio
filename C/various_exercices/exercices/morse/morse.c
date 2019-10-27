#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define NBCAR 37
#define MAXLENCODE 6

static const char texte_ref[NBCAR] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r',
     's','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',
     ' '};


static char morse_ref[][MAXLENCODE] = {{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},
    {".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},
    {"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."},{".----"},
    {"..---"},{"...--"},{"....-"},{"....."},{"-...."},{"--..."},{"---.."},{"---."},
    {"-----"},{"//"}};

/* help : fonction affichant tout le tableau du code morse pouvant
   être codé ou décodé par ce programme */
void help()
{
    for(int i=0; i<NBCAR; i++){
        printf(" %c :  %s\n",texte_ref[i],morse_ref[i]);
    }
}

/* affiche_texte : fonction affichant le texte correspondant au code
   morse passe en paramètre */
void affiche_texte(char *morse)
{
    char tmp_tab_morse[strlen(morse)+1];
    strcpy(tmp_tab_morse,morse);
    
    char *code_morse;
    const char delim[]=" ";
    
    code_morse = strtok(tmp_tab_morse,delim);
    int j=0;
    
    while(code_morse != NULL){
        for(int i=0; i<NBCAR; i++){
            if (strcmp(code_morse,morse_ref[i])==0)
            {
                printf("%c",texte_ref[i]);
                break;
            }
        }
        code_morse = strtok(NULL,delim);
    }
    puts("\n");
}

/* affiche_morse : fonction affichant le code Morse correspondant au
   texte passé en paramètre */
void affiche_morse(char *texte)
{
    for(int i=0; i<strlen(texte);i++){
        for(int j=0; j<NBCAR; j++){
            if(tolower(texte[i])==texte_ref[j]){
                printf("%s ", morse_ref[j]);
                break;
            }
        }
    }
    puts("\n");
}
