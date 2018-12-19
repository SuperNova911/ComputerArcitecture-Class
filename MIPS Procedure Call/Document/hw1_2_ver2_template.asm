	.data
n: .word 5
	.text
lb	$a0,	n
jal	fib
addi	$v1,	$v0,	0

exit:
li 	$v0,	10
syscall

#put your code here
