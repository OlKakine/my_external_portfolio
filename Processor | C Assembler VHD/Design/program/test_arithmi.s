.text
lui $28, 0x1234
ori $28, $28, 0x5678
# $28 <- 0x12345678	
addi $29, $28, 0x000F
# $29 <- 0x12345687	
andi $28, $28, 0x5070
# $28 <- 0x00005070
xori $28, $28, 0x5678
# $28 <- 0x00000608
