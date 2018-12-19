	.data
n: 	.word 3
	.text
lb	$a0, n
jal	sum
add	$v1, $v1, $v0

exit:
li	$v0, 10
syscall

#put your code here
sum:
addiu	$sp, $sp, -8		# increase stack size by 8
sw	$ra, 4($sp)		# store saved register ra
sw	$s0, 0($sp)		# store saved register s0

bne	$a0, $0, notequal	# if they aren't equal, go to notequal
add	$s0, $0, $0		# set value of s0 to zero
j	return			# go to return

notequal:
add	$s0, $a0, $0		# set value of s0 to a0
addi	$a0, $a0, -1		# decrease value of argument by 1
jal	sum			# call sum
add	$s0, $s0, $v0		# add returned value to s0

return:
add	$v0, $s0, $0		# set return value by s0
lw	$ra, 4($sp)		# load saved register ra
lw	$s0, 0($sp)		# load saved register s0
addiu	$sp, $sp, 8		# decrease stack size by 8
jr	$ra			# return to caller
