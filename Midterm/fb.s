# SOURCES USED
# https://stackoverflow.com/questions/8858104/64bit-nasm-division-idiv
# https://www.cs.cmu.edu/afs/cs/academic/class/15213-s20/www/recitations/x86-cheat-sheet.pdf
# https://github.com/realead/pgu_64/blob/master/examples/printf_example/printf_example64.s

.section .data
formatnumber:
	.ascii "%d\n\0"
firststring:
        .ascii "Fizz\n\0"
secondstring:
        .ascii "Buzz\n\0"
thirdstring:
        .ascii "FizzBuzz\n\0"
temp:
	.int 0

.section .text
.globl _start
_start:
	movq $0, %rbx			# rbx = 0

mainloop:
	movq %rbx, %rax			# rax++
	inc %rax
	cmp $100, %rax			# compare rax = 100, 
	jg final			# jump to final if greater

# Check if divisible by 3 and 5
	movq %rax, temp			# replace rax to temp
	movq $0, %rdx			# clear remainder
	movq %rax, %rbx			# dividend rax moved to rbx
	movq $3, %rsi			# divisor is rsi=3
	idiv %rsi			# divide
	cmp $0, %rdx			# check if there is no remainder
	movq %rdx, %rbp			# store remainder to rbp

	movq temp, %rax			# replace rax to temp
	movq $0, %rdx
	movq %rax, %rbx
	movq $5, %rsi			# divisor is rsi=5
	idiv %rsi
	addq %rdx, %rbp			# add to prev remainder
	cmp $0, %rbp			# if remainder is still 0, 
	je printdiv35			# print thirdstring
	
# Else, check if divisible by just 3
 	movq temp, %rax
	movq $0, %rdx			# clear remainder
	movq %rax, %rbx			# dividend rax moved to rbx 
        movq $3, %rsi			# divisor is rsi=3
        idiv %rsi			# divide
	
	cmp $0, %rdx			# if there is no remainder
	je printdiv3			# jump to print firststring
	
# Else, check if divisible by just 5
	movq temp, %rax			# refresh rax 
	movq $0, %rdx			# clear remainder
	movq %rax, %rbx			# dividend rax moved to rbx
	movq $5, %rsi			# divisor is rsi=5
	idiv %rsi			# divide

	cmp $0, %rdx			# if there is no remainder
	je printdiv5			# jump to print secondstring

# Print number if not divisible by any
	movq $formatnumber, %rdi
        movq temp, %rsi
        call printf                     # print current number 

	jmp mainloop			# repeat to mainloop

printdiv35:
	movq $thirdstring, %rdi         # thirdstring is in rdi 
        call printf
        jmp mainloop

printdiv3:
	movq $firststring, %rdi		# firststring is in rdi 
	call printf
	jmp mainloop

printdiv5:
	movq $secondstring, %rdi	# secondstring is in rdi
	call printf
	jmp mainloop

final:
	movq $0, %rdi
	call exit


