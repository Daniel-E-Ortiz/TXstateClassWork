# Daniel Ortiz, CS 2318-001, Assignment 2 Part 1 Program A
			.data
promptInt:		.asciiz "Enter an Integer: "
promptStr:		.asciiz "Enter a String (no more than 40 characters): "
promptChar:		.asciiz	"Enter a Character: "
displayInt:		.asciiz "Your Integer: "
displayStr:		.asciiz "Your String: "
displayChar:		.asciiz "Your Character: "
	
stringBuffer:		.space 40
			
			.text
			.globl main
main:
			li $v0, 4		# print integer prompt
			la $a0, promptInt
			syscall
			
			li $v0, 5		# read integer
			syscall
			move $t0, $v0		# store integer into $t0
			
			li $v0, 4		# print displayInt prompt
			la $a0, displayInt
			syscall
			
			li $v0, 1		# display integer
			move $a0, $t0				
			syscall
			li $v0, 11
			li $a0, '\n'
			syscall
			
			li $v0, 4		# print string prompt
			la $a0, promptStr
			syscall
			
			li $v0, 8		# read string input
			la $a0, stringBuffer
			li $a1, 40
			syscall
			move $t1, $v0		# store string into $t1
			
			li $v0, 4		# display string text
			la $a0, displayStr
			syscall
			
			li $v0, 4		# display string
			la $a0, stringBuffer		
			syscall
			
			li $v0, 4		# print character prompt
			la $a0, promptChar
			syscall
			
			li $v0, 12		# read single character
			syscall	
			move $t2, $v0		# store character into $t2
			li $v0, 11
			li $a0, '\n'
			syscall
			
			li $v0, 4		# display character text
			la $a0, displayChar
			syscall
			
			move $a0, $t2
			li $v0, 11
			syscall
						
			li $v0, 10 		#Graceful exit
			syscall	