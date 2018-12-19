	.data
n:	.word 5
	.text
lb	$a0, n
jal	fib
addi	$v1, $v0, 0

exit:
li	$v0, 10
syscall

#put your code here
fib:
bne	$a0, $0, notequal1	# if they aren't equal, go to notequal1
add	$v0, $0, $0		# set return value by zero
j	return			# go to return

notequal1:
bne	$a0, 1, notequal2	# if they aren't equal, go to notequal2
addi	$v0, $0, 1		# set return value by 1
j 	return			# go to return

notequal2:
addiu	$sp, $sp, -12		# increase stack size by 12
sw	$ra, 8($sp)		# store saved register ra
sw	$a0, 4($sp)		# store volatile register a0 (argument)
addi	$a0, $a0, -1		# decrease value of argument by 1
jal	fib			# call fib
add	$t0, $v0, $0		# set value of t0 to returned value

sw	$t0, 0($sp)		# store volatile register t0
lw	$a0, 4($sp)		# load volatile register a0 (argument)
addi	$a0, $a0, -2		# decrease value of argument by 2
jal	fib			# call fib

lw	$t0, 0($sp)		# load volatile register t0
lw	$ra, 8($sp)		# load saved register ra
add	$v0, $t0, $v0		# set return value to (t0 + returned value)
addiu	$sp, $sp, 12		# decrease stack size by 8

return:
jr	$ra			# return to caller
