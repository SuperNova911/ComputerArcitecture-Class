      .data
n:    .word  3
      .text
lb 	$a0 , n
jal	sum
add	$v1, $v1, $v0

exit:
li	$v0, 10
syscall

#put your code here


#put your code
sum:
addiu	$sp, $sp, -8
sw	$ra, 4($sp)
sw	$s0, 0($sp)
bne	$a0, $0, then
else:
add	$s0, $0, $0
j	end
then:
add	$s0, $a0, $0
addi	$a0, $a0, -1
jal	sum
add	$s0, $s0, $v0
end:
add	$v0, $s0, $0
lw	$ra, 4($sp)
lw	$s0, 0($sp)
addiu	$sp, $sp, 8
jr	$ra


sum:
addiu	$sp, $sp, -8
sw	$ra, 4($sp)
bne	$a0, $0, then
else:
add	$v0, $0, $0
j	end
then:
add	$t0, $a0, $0
sw	$t0, 0($sp)
addi	$a0, $a0, -1
jal	sum
lw	$t0, 0($sp)
add	$v0, $t0, $v0
end:
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra


if not equal s1 s2
then
return 0

else
s1 pointer move 	
s2 pointer move
if 