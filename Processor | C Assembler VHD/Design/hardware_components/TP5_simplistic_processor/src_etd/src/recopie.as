int_to_led:
 ld 0x0100, r0
 st r0, 0x0001
 jmp int_to_led

jmp int_to_led