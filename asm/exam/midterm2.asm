.text
.globl main

main:
    addi $sp, $sp, -4
    sw   $ra, 0($sp)
    li   $s0, 1

loop_main:
    slti $t0, $s0, 4
    beq  $t0, $0, end_main
    add  $a0, $s0, $0
    jal  poly
    add  $s1, $v0, $0
    li   $v0, 1
    add  $a0, $s1, $0
    syscall
    li   $v0, 11
    li   $a0, 10
    syscall
    addi $s0, $s0, 1
    beq  $0, $0, loop_main

end_main:
    lw   $ra, 0($sp)
    addi $sp, $sp, 4
    li   $v0, 10
    syscall

poly:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $s0, 4($sp)
    sw   $s1, 0($sp)
    add  $s0, $a0, $0
    add  $a0, $s0, $0
    li   $a1, 4
    jal  pow
    add  $s1, $v0, $0
    add  $a0, $s0, $0
    li   $a1, 3
    jal  pow
    add  $v0, $s1, $v0
    addi $v0, $v0, 1
    lw   $s1, 0($sp)
    lw   $s0, 4($sp)
    lw   $ra, 8($sp)
    addi $sp, $sp, 12
    jr   $ra

pow:
    li   $v0, 1
    li   $t0, 0

loop_pow:
    slt  $t1, $t0, $a1
    beq  $t1, $0, end_pow
    mul  $v0, $v0, $a0
    addi $t0, $t0, 1
    beq  $0, $0, loop_pow

end_pow:
    jr   $ra
