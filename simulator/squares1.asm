ADD $s0, $zero, $zero # $s0 = i
L1: BLE $s0, 200, DONE

ADD $s1, $zero, $zero # $s1 = j
L2: BLE $s1, $s0, L3


# load from address in register i with 0 offset into $s2, perform addition, store back into memory
LW $s2, $s0
ADD $s2, $s2, $s0
SW $s0, $s2


ADDI $s1, $s1, 1
J L2

L3: ADDI $s0, $s0, 1
J L1
DONE: NOP

