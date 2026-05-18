
.data
x:	    .word	0:4		            # Array to hold x-coordinates of robots
y:	    .word	0:4		            # Array to hold y-coordinates of robots

str1:	.asciiz	"Your coordinates: 25 25\n"
str2:	.asciiz	"Enter move (1 for +x, -1 for -x, 2 for + y, -2 for -y):"
str3:	.asciiz	"Your coordinates: "
sp:	    .asciiz	" "
endl:	.asciiz	"\n"
str4:	.asciiz	"Robot at "
str5:	.asciiz	"AAAARRRRGHHHHH... Game over\n"

.text

main:
    # Initialized Variables
    li	$s1, 25		                # myX = 25
	li	$s2, 25		                # myY = 25
	li	$s4, 1		                # status = 1 (1 = alive, 0 = dead)

	la	$s5, x		                # Load base address of x-array
	la	$s6, y		                # Load base address of y-array

    # Initialize Robot Positions
	sw	$0, 0($s5)	                # Robot 0: x[0] = 0
	sw	$0, 0($s6)	                # Robot 0: y[0] = 0
	sw	$0, 4($s5)	                # Robot 1: x[1] = 0
	li	$s7, 50
	sw	$s7, 4($s6)	                # Robot 1: y[1] = 50
	sw	$s7, 8($s5)	                # Robot 2: x[2] = 50
	sw	$0, 8($s6)	                # Robot 2: y[2] = 0
	sw	$s7, 12($s5)                # Robot 3: x[3] = 50
	sw	$s7, 12($s6)                # Robot 3: y[3] = 50

    # Print initial coordinates
	la	$a0, str1
	li	$v0, 4
	syscall

	bne	$s4, 1, main_exitw	        # while (status == 1)

main_while:
    # Prompt for move
	la	$a0, str2
	li	$v0, 4
	syscall

    # Read user input
	li	$v0, 5
	syscall
	move $s3, $v0                   # move = user input

    # Process User Move
	bne	$s3, 1, main_else1	        # if (move == 1)
	add	$s1, $s1, 1		            # myX++
	beq $zero, $zero, main_exitif

main_else1:
	bne	$s3, -1, main_else2	        # else if (move == -1)
	add	$s1, $s1, -1	            # myX--
	beq $zero, $zero, main_exitif

main_else2:
	bne	$s3, 2, main_else3	        # else if (move == 2)
	add	$s2, $s2, 1		            # myY++
	beq $zero, $zero, main_exitif

main_else3:
    bne	$s3, -2, main_exitif	    # else if (move == -2)
	add	$s2, $s2, -1	            # myY--

main_exitif:
    # Update Robot Positions
    la	$a0, x		                # arg0: &x[0]
	la	$a1, y		                # arg1: &y[0]
	move $a2, $s1	                # arg2: myX
	move $a3, $s2	                # arg3: myY
	jal	moveRobots	                # Call moveRobots subroutine
	move $s4, $v0	                # status = moveRobots(...)

    # Print updated user coordinates
	la	$a0, str3
	li	$v0, 4
	syscall
	move $a0, $s1
	li	$v0, 1
	syscall
	la	$a0, sp
	li	$v0, 4
	syscall
	move $a0, $s2
	li	$v0, 1
	syscall
	la	$a0, endl
	li	$v0, 4
	syscall

    # Print Robot Positions
	la	$s5, x
	la	$s6, y
	li	$s0, 0		                # loop counter i = 0

main_for:
    la	$a0, str4
	li	$v0, 4
	syscall
	lw	$a0, 0($s5)	                # print x[i]
	li	$v0, 1
	syscall
	la	$a0, sp
	li	$v0, 4
	syscall
	lw	$a0, 0($s6)	                # print y[i]
	li	$v0, 1
	syscall
	la	$a0, endl
	li	$v0, 4
	syscall

    add	$s5, $s5, 4	                # increment x pointer
	add	$s6, $s6, 4	                # increment y pointer
	add	$s0, $s0, 1	# i++
	blt	$s0, 4, main_for

	beq	$s4, 1, main_while	        # loop if status is still 1 (alive)

main_exitw:

    # Game Over Output
    la	$a0, str5
	li	$v0, 4
	syscall
	li	$v0, 10		                # Exit program cleanly
	syscall

# int moveRobots(int *arg0, int *arg1, int arg2, int arg3)
# Updates the positions of all four robots and checks for collisions.

moveRobots:

    # Function Stack Setup
    addi $sp, $sp, -32              # Allocate space for 8 items
    sw   $ra, 28($sp)               # Save return address
    sw   $s0, 24($sp)               # Save $s0 (ptrX)
    sw   $s1, 20($sp)               # Save $s1 (ptrY)
    sw   $s2, 16($sp)               # Save $s2 (arg2 / human X)
    sw   $s3, 12($sp)               # Save $s3 (arg3 / human Y)
    sw   $s4, 8($sp)                # Save $s4 (alive status)
    sw   $s5, 4($sp)                # Save $s5 (loop counter i)

    # Initialize Local Variables
    li   $s4, 1                     # alive = 1
    move $s0, $a0                   # ptrX = arg0
    move $s1, $a1                   # ptrY = arg1
    move $s2, $a2                   # Save human X locally
    move $s3, $a3                   # Save human Y locally
    li   $s5, 0                     # i = 0

mr_loop:
    bge  $s5, 4, mr_end             # for (i=0; i<4; i++)

    # Update X Coordinate
    lw   $a0, 0($s0)                # Pass *ptrX to getNew
    move $a1, $s2                   # Pass human X to getNew
    jal  getNew
    sw   $v0, 0($s0)                # *ptrX = getNew(*ptrX, arg2)

    # Update Y Coordinate
    lw   $a0, 0($s1)                # Pass *ptrY to getNew
    move $a1, $s3                   # Pass human Y to getNew
    jal  getNew
    sw   $v0, 0($s1)                # *ptrY = getNew(*ptrY, arg3)

    # Check for Collision
    lw   $t0, 0($s0)                # Load updated *ptrX
    lw   $t1, 0($s1)                # Load updated *ptrY

    bne  $t0, $s2, mr_next          # If X coords mismatch, skip to next
    bne  $t1, $s3, mr_next          # If Y coords mismatch, skip to next

    # Collision detected!
    li   $s4, 0                     # alive = 0
    beq  $zero, $zero, mr_end       # break out of loop

mr_next:
    addi $s0, $s0, 4                # ptrX++
    addi $s1, $s1, 4                # ptrY++
    addi $s5, $s5, 1                # i++
    beq  $zero, $zero, mr_loop

mr_end:
    move $v0, $s4                   # Set return value to 'alive' status

    # Function Stack Restore
    lw   $ra, 28($sp)
    lw   $s0, 24($sp)
    lw   $s1, 20($sp)
    lw   $s2, 16($sp)
    lw   $s3, 12($sp)
    lw   $s4, 8($sp)
    lw   $s5, 4($sp)
    addi $sp, $sp, 32               # Deallocate stack frame

    jr   $ra                        # Return to main

#   int getNew(int arg0, int arg1)
#   Calculates a single new coordinate for a robot based on human pos.

getNew:
    sub  $t0, $a0, $a1              # temp = robot_coord - human_coord

    # Evaluate distance conditions
    bge  $t0, 10, gn_ge10           # if temp >= 10
    bgt  $t0, 0, gn_gt0             # else if temp > 0
    beq  $t0, 0, gn_eq0             # else if temp == 0
    bgt  $t0, -10, gn_gtneg10       # else if temp > -10
    ble  $t0, -10, gn_leneg10       # else if temp <= -10

gn_ge10:
    addi $v0, $a0, -10              # Move 10 units closer (negative direction)
    beq  $zero, $zero, gn_end

gn_gt0:
    addi $v0, $a0, -1               # Move 1 unit closer (negative direction)
    beq  $zero, $zero, gn_end

gn_eq0:
    move $v0, $a0                   # No movement
    beq  $zero, $zero, gn_end

gn_gtneg10:
    addi $v0, $a0, 1                # Move 1 unit closer (positive direction)
    beq  $zero, $zero, gn_end

gn_leneg10:
    addi $v0, $a0, 10               # Move 10 units closer (positive direction)

gn_end:
    jr   $ra                        # Return new coordinate
