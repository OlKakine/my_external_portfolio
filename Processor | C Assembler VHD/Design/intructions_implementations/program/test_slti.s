	addiu $29, $zero, 30
	addiu $28, $zero, 20
	# All the results are stored in $30
	# 30<20 ? -> 0
	slti $30, $29, 20
	# 20<30 ? -> 1
	slti $30, $28, 30

	sub $28, $zero, $28
	# 30<-20 ? -> 0
	slti $30, $29, -20
	# -20<30 ? -> 1
	slti $30, $28, 30

	sub $29, $zero, $29
	# -30<-20 ? -> 1
	slti $30, $29, -20
	# -20<-30 ? -> 0
	slti $30, $28, -30

	# -20<-20 ? -> 0
	slti $30, $28, -20

	addiu $28, $zero, 1
	# $28 <- MIN
	sll $28, $28, 31
	# -1<MIN ? -> 0
	slti $30, $28, 1
