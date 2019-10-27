    .text
/*
bool est_present(uint32_t val, struct noeud_t *abr)
{
   if (abr == NULL) {
       return false;
   } else if (val == abr->val) {
       return true;
   } else if (val < abr->val) {
       return est_present(val, abr->fg);
   } else {
       return est_present(val, abr->fd);
   }
}

*/
    .globl est_present
est_present:
/* Contexte :
val:	 $a0 de type (uint32_t)
abr:	 $a1 de type (struct noeud_t*)
	à définir */
if_NULL:
	addiu $t0, $zero, 0
	bne $t0, $a1, elif_1
	addiu $v0, $zero, 0
	j fin_present

elif_1:
	lw $t0, 0($a1)
	bne $t0, $a0, elif_2
	addiu $v0, $zero, 1
	j fin_present

elif_2:
	subu $t1, $t0, $a0
	bltz $t1, else

	addiu $sp, $sp, -12
	lw $a1, 4($a1)
	j appel_fct

else:
	addiu $sp, $sp, -12
	lw $a1, 8($a1)
	j appel_fct

appel_fct:	
	sw $ra, 8($sp)
	jal est_present

	lw $ra, 8($sp)
	addiu $sp, $sp, 12
	
	j fin_present
	
fin_present:	
    jr    $ra

/*
void abr_vers_tab(struct noeud_t *abr)
{
    if (abr != NULL) {
        abr_vers_tab(abr->fg);
        *ptr = abr->val;
        ptr++;
        struct noeud_t *fd = abr->fd;
        free(abr);
        abr_vers_tab(fd);
    }
}
*/
    .globl abr_vers_tab
abr_vers_tab:
/* Contexte :  
abr:	 $a0 de type (struct noeud_t*)
ptr:	 var globale de type (uint32_t*)
	*/
	
	sw $a0, 0($sp)
	addiu $sp, $sp ,-8
	sw $ra, 4($sp)
	
if_not_NULL:
	beq $zero, $a0, fin_abs

appel_fg:
	lw $a0, 4($a0)	
	
	jal abr_vers_tab
	lw $a0, 8($sp)
	

	lw $t3, ptr 
	lw $t0, 0($a0)
	sw $t0, 0($t3)
	addiu $t3, $t3, 4
	sw $t3, ptr	

appel_fd:	
	lw $t2, 8($a0)

	addu $a0, $t2, $zero
	jal abr_vers_tab


	
fin_abs:
	lw $ra, 4($sp)
	addiu $sp,$sp,8
	jr    $ra
	
	.data
	.comm ptr,4


/*
	if_not_NULL:
	addiu $t0, $zero, 0
	beq $t0, $a0, fin_abs

appel_fg:
	lw $a0, 4($a0)
	
	addiu $sp, $sp ,-8
	sw $ra, 4($sp)
	
	jal abr_vers_tab
	
	lw $ra, 4($sp)
	addiu $sp,$sp,8
	lw $a0, 0($sp)

	

	lw $t3, ptr 
	lw $t0, 0($a0)
	sw $t0, 0($t3)
	addiu $t3, $t3, 4
	sw $t3, ptr	

appel_fd:	
	lw $t2, 8($a0)

	

	addiu $sp, $sp ,-8
	sw $ra, 4($sp)

	addu $a0, $t2, $zero
	jal abr_vers_tab
	
	lw $ra, 4($sp)
	addiu $sp,$sp,8
	lw $a0, 0($sp)	
	
fin_abs:	
	jr    $ra
	*/
