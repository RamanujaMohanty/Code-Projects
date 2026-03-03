# Ramanuja Mohanty
# 03/03/26
# Assignment 4

.data

.text
.globl main

main:
	li $t0, 0  	# int sum = 0
	li $t1, 0  	# int i = 0
loop:
	bgt $t1, 3, done	# if (i > 3) break loop
	addu $t0, $t0, $t1	# sum = sum + i | sum += i
	addiu $t1, $t1, 1	# i = i + 1 | i++
	j loop		# jump to start of loop
done:
	move $a0, $t0	# argument = sum
	li $v0, 1		# syscall 1 = print_int
	syscall
	li $v0, 10		# syscall 10 = exit
	syscall