.section .data
hello:
	.asciz "Hello world!\n"

.section .text
.global _start
_start:

	movq $1, %rax
	movq $1, %rdi
	movq $hello, %rsi
	movq $14, %rdx
	syscall

	movq $60, %rax
	movq $0, %rdi
	syscall
