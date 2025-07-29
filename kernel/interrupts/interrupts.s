.section .data
#idtr:
#	.word 0 # 16 bit limit
#	.long 0 # 32 bit base

divString: .asciz "Division error handler"





.section .text
.align 8
idtr:
    .word 0x07FF
    .long 0xC0412000   # your IDT base


# call in form of setIdt(base, limit)
.globl setIdt
setIdt:
	
	# set the limit storage
#	mov 8(%esp), %ax
#	mov %ax, idtr

	# set the base storage
#	mov 4(%esp), %eax
#	mov %eax, idtr + 2

	# sets the gdtr register
	lidt idtr

	ret


.globl getIDT
getIDT:
	sidt (%eax)
	ret



.globl divError
divError:

	# prints that this is a division error
#	mov $divString, %eax
#	push %eax
#	call terminal_writestring
	#add $4, %esp

	#jmp end

	cli
	1:  hlt
    	jmp 1b
	
.globl doubleFault
doubleFault:
    cli
1:  hlt
    jmp 1b

