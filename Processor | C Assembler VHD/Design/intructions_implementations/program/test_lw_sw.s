	addiu $28, $zero, 100

	addiu $29, $zero, 1024
# We write 100 at address 1024
	sw $28, 0($29)
# We read te content at address 1024 in $30
	lw $30, 0($29)
