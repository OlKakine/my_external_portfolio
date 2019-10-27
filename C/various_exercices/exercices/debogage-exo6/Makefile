# Compléter le Makefile effectuant les opérations suivantes :
# - Génération de 2 versions de l'exécutable : <nomexecutable> et <nomexecutable>_fsanitize
# - <nomexecutable> : avec options de compilation standards et mode débogage pour utilisation de valgrind
# - <nomexecutable>_fsanitize : avec options ligne ci-dessus + options mode débogage fsanitize
# - Règle clean : supprimer les fichiers .o et les exécutables générés 
CC=clang

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename $(shell pwd))
