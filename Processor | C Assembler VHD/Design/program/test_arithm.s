.text

lui $30, 0xCCCC
# $30 <- 0xCCCC0000
lui $29, 0xAAAA
# $29 <- 0xAAAA0000
	
and $28, $29, $30
# $28 <- 0x88880000	
or $28, $29, $30
# $28 <- 0xEEEE0000
xor $28, $29, $30
# $28 <- 0x66660000
nor $28, $29, $30	
# $28 <- 0x1111FFFF
lui $29, 0x0001
lui $30, 0x0002
add $28, $29, $30
# $28 <- 0x00030000
sub $28, $29, $30
# $28 <- 0xFFFF0000
addu $28, $29, $30
# $28 <- 0x00030000
subu $28, $30, $29	
# $28 <- 0x00010000
