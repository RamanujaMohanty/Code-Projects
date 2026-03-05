# Description: 	User enters x. Program subtracts 5 from x repeatedly,
#		until x <= 0, and prints x.
#
# #include <iostream.h>
# int main(void)
# {
#   int x;
#
#   cin >> x; // read an int, store in x
#   while (x > 0)
#     x = x - 5;
#
#   cout << x << endl;
#
# }
# x	$s0

# Ramanuja Mohanty
# 03/04/26
# Assignment 5.1

.data
endl:   .asciiz	"\n"

.text

main:
    li $v0, 5
    syscall
    move $s0, $v0

loop:
    blez $s0, end_loop
    addi $s0, $s0, -5
    j loop

end_loop:
    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 4
    la $a0, endl
    syscall

    li $v0, 10
    syscall
