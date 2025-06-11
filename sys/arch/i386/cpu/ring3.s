	.text
	.globl x86_ring3_switch
	.extern tss
	
x86_ring3_switch:
	cli
	mov $0x23, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	movl 4(%esp), %eax
	movl 8(%esp), %ebx

	pushl $0x23
	pushl %ebx
	pushl $0x202
	pushl $0x1B
	pushl %eax
	iret
