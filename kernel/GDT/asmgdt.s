gdtr: 
	.word 0 # 16-bit limit
	.long 0 # 32-bit base



# call in form of setgdt(limit, base)
.globl setgdt
setgdt:
	
	# set the limit storage
	mov 8(%esp), %ax
	mov %ax, gdtr

	# set the base storage
	mov 4(%esp), %eax
	mov %eax, gdtr + 2

	# sets the gdtr register
	lgdt gdtr

	ret

.globl getgdt
getgdt:
	sgdt (%eax)
	ret



.globl flushGdt
flushGdt:
	lgdt gdtr
	ljmp $0x08, $completeFlush


.global completeFlush
completeFlush:
	    mov $0x10, %ax
	    mov %ax, %ds
	    mov %ax, %es
	    mov %ax, %fs
	    mov %ax, %gs
	    mov %ax, %ss
	    ret



