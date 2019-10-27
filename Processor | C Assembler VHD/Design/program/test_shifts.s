.text
# Pour les tests ne pas utiliser le registre $1 
lui $28, 0xAAAA
srl $28, $28, 0x0003
# $28 <- 0x15554000
sll $28, $28, 0x0003
# $28 <- 0xAAAA0000
sra $28, $28, 0x0003
# $28 <- 0xF5554000
ori $29, 0x0004
# même choses mais avec décalage de 4
srlv $28, $28, $29

sllv $28, $28, $29

srav $28, $28, $29
# max_cycle 50
# pout_start
# 12340000
# ABCD0000
# pout_end
