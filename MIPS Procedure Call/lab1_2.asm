	.data
s1:	.asciiz "hello"
s2:	.asciiz "hello"
	.text
	
la	$a0, s1
la	$a1, s2
jal	streq
add	$v1, $v1, $v0

exit:
li	$v0, 10
syscall

#put your code here
streq:
lb	$t0, ($a0)
lb	$t1, ($a1)

loop:
beq	$t0, $t1, then
add	$v0, $0, $0
j	return
then:
and	$t2, $t0, $t1
beq	$t2, $0, endloop
addi	$a0, $a0, 1
addi	$a1, $a1, 1
lb	$t0, ($a0)
lb	$t1, ($a1)
j	loop
endloop:
addi	$v0, $0, 1
return:
jr	$ra