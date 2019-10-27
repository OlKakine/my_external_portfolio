/*
void tri_min(int32_t tab[], uint32_t taille)
{
    uint32_t i, j, ix_min;
    int32_t tmp; 
    for (i = 0; i < taille - 1; i++) {
        for (ix_min = i, j = i + 1; j < taille; j++) {
            if (tab[j] < tab[ix_min]) {
                ix_min = j;
            }
        }
        tmp = tab[i];
        tab[i] = tab[ix_min];
        tab[ix_min] = tmp;
    }
}
*/
    .text
    .globl tri_min
/* void tri_min(int32_t tab[], uint32_t taille) */
/* Contexte : à définir
tab: $a0 de type (int32_t [])
taille:	$a1 de type (uint32_t)
i,j, ix_min: $t0..2 de type (uint32_t)
tmp:	$t3 de type (int32_t)
*/
tri_min:
	addu $t0, $zero, $zero
	
for1_1:	
	addiu $t4, $a1, -1
	subu $t4, $t4, $t0
	blez $t4, fin

	addu $t2, $zero, $t0
	addiu $t1, $t0, 1
		
for2:
	subu $t4, $a1, $t1
	blez $t4, for1_2

	sll $t7, $t1, 2
	addu $t4, $a0, $t7
	lw $t5, 0($t4)
	sll $t7, $t2, 2
	addu $t4, $a0, $t7
	lw $t6, 0($t4)
	subu $t5, $t6, $t5
	blez $t5, fin_for2

	addu $t2, $zero, $t1

fin_for2:
	addiu $t1, $t1, 1
	j for2

for1_2:
	sll $t7, $t0, 2
	addu $t5, $a0, $t7
	lw $t3, 0($t5)

	sll $t7, $t2, 2
	addu $t4, $a0, $t7
	lw $t6, 0($t4)
	sw $t6, 0($t5)

	sw $t3, 0($t4)

	addiu $t0, $t0, 1
	j for1_1

fin:	
    jr $ra

