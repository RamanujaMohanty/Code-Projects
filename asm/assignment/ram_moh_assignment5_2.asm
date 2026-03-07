# Description:  User enters count. Program performs xor and shift right
#               operations, for count iterations.
#               Note: spim doesn't support printing integers in hex
#               (though we can write a utility function!) Look at
#               $s1 in spim to trace the operations.

# count	$s0
# x	$s1
# i	$s2

	.data
endl:   .asciiz "\n"
	.text
main:
	li	$s1, 0x89abcdef	#  int x = 0x89abcdef;
	
	# cin >> count
	li	$v0, 5		#  system call to read integer
	syscall
	move	$s0, $v0		#  store user input in $s0 (count)
	
	# for (int i = 0; ...)
	li	$s2, 0		#  intialize $s2 (i) to 0
loop:
	# i < count;
	bge	$s2, $s0, end_loop	# if i >= count, then exit loop
	
	# x = x ^ 0x00010002
	li	$t0, 0x00010002
	xor	$s1, $s1, $t0
	
	# cout << x << endl
	li	$v0, 1		# system call to print integer
	move	$a0, $s1		# move x to argument register
	syscall
	
	li	$v0, 4		# system call to print string
	la	$a0, endl		# load address of new line
	syscall
	
	# x = x >> 1
	sra	$s1, $s1, 1	# shift 1 to right by 1 bit
	
	# ... i++)
	addi	$s2, $s2, 1	# increment i by 1
	j	loop		# jump back to loop condition
end_loop:
	li	$v0, 10		# system call for exit
	syscall