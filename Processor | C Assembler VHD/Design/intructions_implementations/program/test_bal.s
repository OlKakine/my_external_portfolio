	addiu $28, $0, 5
	addiu $29, $0, 1
	
reset:
	# $28 <- $28-1, $28>=0
	sub $28, $28, $29
	
	bgezal $28, reset

	addiu $28, $0, 10
	# $28 <- 10
	bltzal $28, reset
	# end of program
