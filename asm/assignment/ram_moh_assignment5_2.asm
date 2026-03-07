
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
main:	li	$s1, 0x89abcdef	#  int x = 0x89abcdef;

