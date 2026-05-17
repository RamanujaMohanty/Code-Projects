.data
x:      .word	0:4
y:      .word	0:4
str1:	.asciiz	"Your coordinates: 25 25\n"
str2:	.asciiz	"Enter move (1 for +x, -1 for -x, 2 for + y, -2 for -y):"
str3:	.asciiz	"Your coordinates: "
sp:     .asciiz	" "
endl:	.asciiz	"\n"
str4:	.asciiz	"Robot at "
str5:	.asciiz	"AAAARRRRGHHHHH... Game over\n"

.text

main:

    li	$s1,25
	li	$s2,25
	li	$s4,1

	la	$s5,x
	la	$s6,y

	sw	$0,($s5)
	sw	$0,($s6)
	sw	$0,4($s5)
	li	$s7,50
	sw	$s7,4($s6)
	sw	$s7,8($s5)
	sw	$0,8($s6)
	sw	$s7,12($s5)
	sw	$s7,12($s6)

	la	$a0,str1
	li	$v0,4

    syscall

	bne	$s4,1,main_exitw

main_while:

    la	$a0,str2
	li	$v0,4
	syscall

	li	$v0,5
	syscall
	move	$s3,$v0

	bne	$s3,1,main_else1
	add	$s1,$s1,1
	beq     $zero, $zero, main_exitif
main_else1:
	bne	$s3,-1,main_else2
	add	$s1,$s1,-1
	beq     $zero, $zero, main_exitif
main_else2:
	bne	$s3,2,main_else3
	add	$s2,$s2,1
	beq     $zero, $zero, main_exitif
main_else3:	bne	$s3,-2,main_exitif
	add	$s2,$s2,-1

main_exitif:	la	$a0,x
	la	$a1,y
	move	$a2,$s1
	move	$a3,$s2
	jal	moveRobots
	move	$s4,$v0

	la	$a0,str3
	li	$v0,4
	syscall
	move	$a0,$s1
	li	$v0,1
	syscall
	la	$a0,sp
	li	$v0,4
	syscall
	move	$a0,$s2
	li	$v0,1
	syscall
	la	$a0,endl
	li	$v0,4
	syscall

	la	$s5,x
	la	$s6,y
	li	$s0,0
main_for:	la	$a0,str4
	li	$v0,4
	syscall
	lw	$a0,($s5)
	li	$v0,1
	syscall
	la	$a0,sp
	li	$v0,4
	syscall
	lw	$a0,($s6)
	li	$v0,1
	syscall
	la	$a0,endl
	li	$v0,4
	syscall
	add	$s5,$s5,4
	add	$s6,$s6,4
	add	$s0,$s0,1
	blt	$s0,4,main_for

	beq	$s4,1,main_while

main_exitw:	la	$a0,str5
	li	$v0,4
	syscall
	li	$v0,10
	syscall

moveRobots:
    addi $sp, $sp, -32
    sw   $ra, 28($sp)
    sw   $s0, 24($sp)
    sw   $s1, 20($sp)
    sw   $s2, 16($sp)
    sw   $s3, 12($sp)
    sw   $s4, 8($sp)
    sw   $s5, 4($sp)

    li   $s4, 1
    move $s0, $a0
    move $s1, $a1
    move $s2, $a2
    move $s3, $a3
    li   $s5, 0

mr_loop:
    bge  $s5, 4, mr_end

    lw   $a0, 0($s0)
    move $a1, $s2
    jal  getNew
    sw   $v0, 0($s0)

    lw   $a0, 0($s1)
    move $a1, $s3
    jal  getNew
    sw   $v0, 0($s1)

    lw   $t0, 0($s0)
    lw   $t1, 0($s1)

    bne  $t0, $s2, mr_next
    bne  $t1, $s3, mr_next

    li   $s4, 0
    beq  $zero, $zero, mr_end

mr_next:
    addi $s0, $s0, 4
    addi $s1, $s1, 4
    addi $s5, $s5, 1
    beq  $zero, $zero, mr_loop

mr_end:
    move $v0, $s4

    lw   $ra, 28($sp)
    lw   $s0, 24($sp)
    lw   $s1, 20($sp)
    lw   $s2, 16($sp)
    lw   $s3, 12($sp)
    lw   $s4, 8($sp)
    lw   $s5, 4($sp)
    addi $sp, $sp, 32

    jr   $ra

getNew:
    sub  $t0, $a0, $a1

    bge  $t0, 10, gn_ge10
    bgt  $t0, 0, gn_gt0
    beq  $t0, 0, gn_eq0
    bgt  $t0, -10, gn_gtneg10
    ble  $t0, -10, gn_leneg10

gn_ge10:
    addi $v0, $a0, -10
    beq  $zero, $zero, gn_end

gn_gt0:
    addi $v0, $a0, -1
    beq  $zero, $zero, gn_end

gn_eq0:
    move $v0, $a0
    beq  $zero, $zero, gn_end

gn_gtneg10:
    addi $v0, $a0, 1
    beq  $zero, $zero, gn_end

gn_leneg10:
    addi $v0, $a0, 10

gn_end:
    jr   $ra
