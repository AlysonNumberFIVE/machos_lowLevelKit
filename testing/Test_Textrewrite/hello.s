


section .text
global	_hello

_hello:
	jmp		_jump_call
	
	mov 	rax, 0x20000004
	mov		rdi, 1
	pop		rsi
	mov		rdx, 12
	syscall

	mov		rax, 1
	syscall

_jump_call:

	call 	_hello
	db		'Hello world', 10
		
