	addiu $28, $zero, 20
	addiu $29, $zero, 30
	# All the results are stored in $30
	# 30<20 ? -> 0
	slt $30, $29, $28
	# 20<30 ? -> 1
	slt $30, $28, $29

	sub $28, $zero, $28
	# 30<-20 ? -> 0
	slt $30, $29, $28
	# -20<30 ? -> 1
	slt $30, $28, $29

	sub $29, $zero, $29
	# -30<-20 ? -> 1
	slt $30, $29, $28
	# -20<-30 ? -> 0
	slt $30, $28, $29

	# -20<-20 ? -> 0
	slt $30, $28, $28

	addiu $28, $zero, 1
	# $28 <- MIN
	sll $28, $28, 31

	addiu $29, $zero, 1

	# 1<MIN ? -> 0
	slt $30, $29, $28
	# MIN<1 ? -> 1
	slt $30, $28, $29
