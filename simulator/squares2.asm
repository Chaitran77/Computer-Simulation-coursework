# minimisation: Addresses will be known and start from DM addr. 0.
# MAX 5 tokens per line
# changed to use relative branches

ADDI $s4, $zero, 201 # load 201 into $s4 for SLT comparison
ADD $s0, $zero, $zero # $s0 = i

SLT $at, $s0, $s4 # BLE $s0, 200, DONE
BEQ $at, $zero, 7 

ADD $s1, $zero, $zero # $s1 = j

SLT $at, $s1, $s0 # BLE $s1, $s0, L3
BEQ $at, $zero, 6 

# load from address in register i with 0 offset into $s2, perform addition, store back into memory
LW $s2, $s0 
ADD $s2, $s2, $s0 
SW $s2, $s0 


ADDI $s1, $s1, 1 # j++
J 6 


ADDI $s0, $s0, 1 # i++
J 3 

NOP 

