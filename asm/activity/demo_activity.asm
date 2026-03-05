.data
x: .word 4
y: .word -1

.text
main:
    lw $t0, 0x10010000
    lw $t1, x
    la $a0, x
    l2 $t1, ($a0)
    la $a0, x
    lw $t1, ($a0)
    lw $t1, 4($a0)
