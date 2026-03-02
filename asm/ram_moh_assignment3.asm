# Ramanuja Mohanty
# 922147691
# Assignment 3
# 03/01/26

.text
main:
    beq $s0, $s2, if_equal
    bne $s0, $zero, else_if_not_zero

    li $s1, 0
    j end_if

if_equal:
    li $s1, 1
    j end_if

else_if_not_zero:
    li $s1, -1

end_if:
    li $v0, 10
    syscall
