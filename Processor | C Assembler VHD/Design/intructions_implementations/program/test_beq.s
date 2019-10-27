reset:
	# Here beq will jump back
	# If we change the values of $28 and $29, bne will jump
	addiu $28, $zero, 0

	addiu $29, $zero, 0

	bne $28, $29, reset

	beq $28, $29, reset
