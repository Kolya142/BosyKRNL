	.file	"paging.c"
	.text
	.type	get_hardware_flags, @function
get_hardware_flags:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$0, -4(%rbp)
	movl	-20(%rbp), %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L2
	orl	$1, -4(%rbp)
.L2:
	movl	-20(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L3
	orl	$4, -4(%rbp)
.L3:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	get_hardware_flags, .-get_hardware_flags
	.local	pd
	.comm	pd,4096,32
	.local	pt
	.comm	pt,4194304,32
	.globl	init_paging
	.type	init_paging, @function
init_paging:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -8(%rbp)
	jmp	.L6
.L7:
	movl	-8(%rbp), %eax
	sall	$12, %eax
	orl	$3, %eax
	movl	%eax, %ecx
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	pt(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	addl	$1, -8(%rbp)
.L6:
	cmpl	$1048575, -8(%rbp)
	jbe	.L7
	movl	$0, -4(%rbp)
	jmp	.L8
.L9:
	movl	-4(%rbp), %eax
	sall	$10, %eax
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	pt(%rip), %rax
	addq	%rdx, %rax
	orl	$3, %eax
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	pd(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	addl	$1, -4(%rbp)
.L8:
	cmpl	$1023, -4(%rbp)
	jbe	.L9
	leaq	pd(%rip), %rdx
#APP
# 28 "sys/arch/x86/cpu/paging.c" 1
	mov %rdx, %eax
mov %eax, %cr3
mov %cr0, %eax
or $0x80000000, %eax
mov %eax, %cr0

# 0 "" 2
#NO_APP
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	init_paging, .-init_paging
	.type	invlpg, @function
invlpg:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edx
#APP
# 41 "sys/arch/x86/cpu/paging.c" 1
	mov %edx, %eax
invlpg (%eax)
# 0 "" 2
#NO_APP
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	invlpg, .-invlpg
	.type	map_page, @function
map_page:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	-24(%rbp), %eax
	shrl	$22, %eax
	movl	%eax, -16(%rbp)
	movl	-24(%rbp), %eax
	shrl	$12, %eax
	andl	$1023, %eax
	movl	%eax, -12(%rbp)
	movl	-16(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	pd(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %eax
	andl	$4294963200, %eax
	movq	%rax, -8(%rbp)
	movl	-12(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movl	-20(%rbp), %eax
	orl	-28(%rbp), %eax
	movl	%eax, (%rdx)
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	invlpg
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	map_page, .-map_page
	.globl	paging
	.section	.data.rel.local,"aw"
	.align 32
	.type	paging, @object
	.size	paging, 32
paging:
	.long	4096
	.zero	4
	.quad	get_hardware_flags
	.zero	8
	.quad	map_page
	.ident	"GCC: (GNU) 14.2.1 20250207"
	.section	.note.GNU-stack,"",@progbits
