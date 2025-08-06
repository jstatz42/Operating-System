.section .data
.align 0x10
idtr:
	.word 0 # 16 bit limit
	.long 0 # 32 bit base

divString: .asciz "Division error handler"
keyboardInterrupt: .asciz "Keyboard interrupt handler"
.section .text



# call in form of setIdt(base, limit)
.globl setIdt
setIdt:
	
	# set the limit storage
	mov 8(%esp), %ax
	mov %ax, idtr

	# set the base storage
	mov 4(%esp), %eax
	mov %eax, idtr + 2

	# sets the gdtr register
	lidt idtr

	ret


.globl getIDT
getIDT:
	sidt (%eax)
	ret



.globl divError
divError:
	pushal

	# prints that this is a division error
	mov $divString, %eax
	push %eax
	call terminal_writestring
	add $4, %esp

	popal
	jmp end
	
.globl doubleFault
doubleFault:
    cli
1:  hlt
    jmp 1b


# exceptions that have not yet been handled will halt the computer
.globl generalException
generalException:
	cli
1:	hlt
	jmp 1b



.global keyInterrupt
keyInterrupt:
	pushal

	# prints that this is a keyboard interrupt
	mov $keyboardInterrupt, %eax
	push %eax
	call terminal_writestring
	add $4, %esp

	popal
	jmp end









