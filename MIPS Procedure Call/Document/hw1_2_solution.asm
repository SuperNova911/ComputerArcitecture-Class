      .data
s1: .asciiz "hello"
s2: .asciiz "hello"
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
lb 	 $t0, 0($a0) 		# get the character from s1
lb 	 $t1, 0($a1) 		# get the character from s2
bne 	 $t0, $t1, notequal # if they aren¡¯t equal,
# go to notequal
beq 	 $t0, $0, equal	# if they are equal but zero,
# we¡¯ve checked the whole string;
addi  $a0, $a0, 1 		# increment the pointer s1
addi  $a1, $a1, 1 		# increment the pointer s2
j 	 streq 			# loop by jumping to the top

notequal: 
addi $v0, $0, 0		# set return value to zero
jr 	 $ra				# return to caller

equal: 	
addi  $v0, $0, 1		# set return value to 1
jr	 $ra				# return to caller
