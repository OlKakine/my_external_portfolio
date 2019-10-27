Bienvenue dans le projet de CEP de Vincent Raulin et Olivier Checchin!

Nous allons résumer notre projet dans ce README afin d'en faciliter la compréhension.

SUMMARY:
Nous avons implémenter la totalité des familles d'instructions obligatoires.
La plupart des instructions ont été validées par nos tests et les tests automatiques.
Seules les instructions de la famille 'SLT' semblent ne pas répondre aux tests auto, bien que l'on ai l'impression qu'elles passent nos tests avec succès.
A noter que nos tests sont plutôt simples et ne sont pas automatisés (mais ils sont commentés).

Nous avons réussi à faire fonctionner les programmes fournis y compris mips invader.

Pour ce qui est des interruptions, ou des éventuelles extensions, nous ne les avons pas implémenter.

EXPLICATIONS:
Nous avons décider de 'factoriser' le décodage et l'éxecution des instructions afin de réduire le nombre d'états nécessaires, réduire le nombre de clocks nécessaires et potentiellement réduire la taille de l'hypothétique hardware car on utilise des cablages communs pour différentes instructions. (par ex: sub/subu/slt/sltu font tous une soustraction de 'RS' moins 'RT')

Nous avons même fait certaines opérations directement dans l'état 'decode', comme pour le 'jal' où nous avons mis PC+4 dans $31 à la même clock que le decodage.

On à arranger nos états ainsi:

S_FUNCI: on gère les instructions liées aux immédiats (ligne '001' dans le tableau 'opcode')

S_FUNC: on gère les instructions appartenant à 'special'
S_J_JAL: l'étape de jump commune à j et jal
S_JALR: étape 2 de jalr (la 1ere étant effectuée dans l'état S_FUNC)
S_EQ: étape de test d'égalité pour BEQ et BNE
S_COMP: étape de comparaison pour BLEZ et BGTZ
S_BRANC: étape de branchement (on y arrive après un test à succès) commune à tous les tests

S_BAL_TRUE,S_BAL_FALSE:
BAL signie Branchement avec un AL;
on arrive dans TRUE ou FALSE suivant le résultat du test dans BLTZAL ou BGEZAL;
dans les 2 cas on met PC dans $31;
dans TRUE on fera un branchement mais pas dans FALSE.

S_LOAD,S_LOAD2,S_LOAD3,S_LOAD4: les 4 étapes pour 'lw'
S_STORE,S_STORE2: les 2 étapes pour 'sw'

S_SLT1,S_SLT0:
on arrive dans SLT1 dans le cas où il faut mettre 1 dans le registre de destination lors d'une instruction de la famille de slt (et inversement pour SLT0);
on test dedans le bit IR(29) pour savoir s'il faut le mettre dans RD (SLT/U) ou RS (SLTI/U) 


CONCLUSION:
On est conscient que la compréhension du codage de la PC peut être compliquée (même pour nous... ^^).
Mais on voulait faire quelque chose de plus 'dur' pour avoir un peu plus de challenge pour le partie codage.

Reste les SLTs, les interruptions, et les extensions que l'on a pas pu finaliser comme on le voulait par manque de temps.

Merci d'avoir pris le temps de lire et bon courage pour la review du code !

Checchin Olivier, Vincent Raulin
1A Ensimag
Mai 2019
