##########################################################################
# Daniel Ortiz, CS 2318-002, Assignment 2 Part 1 Program D		 #
##########################################################################
# This program takes 3 exam grades and outputs the average               #
############################ data segment ################################
			.data
scoresArr:		.space 12
exam1:			.asciiz "Exam 1? \n"
exam2:			.asciiz "\nExam 2? \n"
final:			.asciiz "\nFinal? \n"
avg:			.asciiz "Average: "
			.text
			.globl main
############################ code segment ################################
main:

			li $v0, 4
			la $a0, exam1
			syscall
			li $v0, 5
			syscall
			# store exam 1 into $t5
			move $t5, $v0
			li $v0, 4
			la $a0, exam2
			syscall
			li $v0, 5
			syscall
			# store exam 2 into $t6
			move $t6, $v0
			li $v0, 4
			la $a0, final
			syscall
			li $v0, 5
			syscall
			# store final into $t7
			move $t7, $v0
			
			# stored 2558 in $t9 & 614 in $t8
			li $t9, 2558
			li $t8, 614
			
			# multiply exam 1 $t5 by 512 & store into $t1
			sll $t1, $t5, 9
			# divide $t1 by $t9 & store back into $t1	
			divu $t1, $t9
			mflo $t1
			# mult exame 2 $t6 by $t8 & store into $t2
			mul $t2, $t8, $t6
			# divide $t2 by 2048 and store into $t2
			srl $t2, $t2 11
			# divide final $t7 by 2 & store into $t3
			srl $t3, $t7, 1
			# add up $t1, $t2, $t3 and store into $t4
			add $t4, $t1, $t2
			add $t4, $t4, $t3
			
			# print result
			li $v0, 4
			la $a0, avg
			syscall
			move $a0, $t4
			li $v0, 1
			syscall
			
			# exit
			li $v0, 10
