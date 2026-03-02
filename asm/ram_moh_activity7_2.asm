# Ramanuja Mohanty
# 922147691
# 03/01/26
# if-or statement translation

.data

.text
main:
    li $s0, 10
    li $s1, 1
    li $s2, 0

    li $v0, 1
    move $a0, $s2
    syscall

    slti $t0, $s1, 3
    bne $t0, $zero, set_flag

    slti $t0, $s0, 4
    beq $t0, $zero, end_if_or

set_flag:
    li $s2, 1

end_if_or:
    li $v0, 1
    move $a0, $s2
    syscall

    li $v0, 10
    syscall
