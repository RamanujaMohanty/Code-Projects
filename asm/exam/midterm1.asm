# Ramanuja Mohanty
# 04/08/2026
# Midterm 01

.data
x:	.space 24
.text
.globl main
main:
	la $s0, x
	li $t0, 0

loop:
	sw $t0, 0($s0)
	
	addi $s0, $s0, 4
	addi $t0, $t0, 1
	
	ble $t0, 5, loop

exit:
	li $v0, 10
	syscall