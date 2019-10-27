
.text
.global main
main:
	ori $a0,$zero,1
	ori $a1,$zero,1
	ori $a2,$zero,2
	jal trace_simple 


boucle: 
	j boucle
trace_simple: 
for: 
	jal affiche_pixel
	addi $a0,$a0,1
	addi $a1,$a1,1
	ori $t0,$zero,100
	beq $t0,$a1,boucle
	j for
	jr $ra 

# context : $a0 =x, $a1=y,$a2= 1 allume, 0 eteint, 2 xor
# $t4 = adresse 
# $t0 = dcl
# $t6 = msk pour allumer

affiche_pixel: 
	andi $t0,$a0,0x1F
	srl $t2,$a0,5
	sll $t3,$a1,4
	or $t3,$t3,$t2
	sll $t3,$t3,2
	lui $t4,0x8005
	ori $t4,$t4,0x1000
	add $t4,$t3,$t4
	lw $t5,0($t4)
	lui $t6,0x8000
	srlv $t6,$t6,$t0
	beq $a2,$zero,eteint
	ori $t7,$zero,2
	beq $a2,$t7,modeXor
allume: 
	or $t5,$t5,$t6
	j fin
modeXor: 
	xor $t5,$t5,$t6
 	j fin 
eteint: 
	nor $t6,$t6,$zero
	and $t5,$t5,$t6
fin: 
	sw $t5,0($t4)	
	jr $ra

	
	
	
