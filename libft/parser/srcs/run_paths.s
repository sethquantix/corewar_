	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_march_path
	.align	4, 0x90
_march_path:                            ## @march_path
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movq	%rcx, -40(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -64(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$0, -16(%rbp)
	je	LBB0_12
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	cmpq	$0, 8(%rax)
	jne	LBB0_4
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	-64(%rbp), %rcx
	movq	-16(%rbp), %rax
	movq	(%rax), %rdi
	movq	-24(%rbp), %rsi
	movq	-40(%rbp), %rdx
	callq	_build_expr_rule
	movl	%eax, -72(%rbp)         ## 4-byte Spill
	jmp	LBB0_5
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	leaq	-64(%rbp), %rcx
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdi
	movq	-24(%rbp), %rsi
	movq	-40(%rbp), %rdx
	callq	_build_expr_opts
	movl	%eax, -72(%rbp)         ## 4-byte Spill
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	-72(%rbp), %eax         ## 4-byte Reload
	movl	%eax, -68(%rbp)
	cmpq	$0, -56(%rbp)
	jne	LBB0_7
## BB#6:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-64(%rbp), %rax
	movq	%rax, -56(%rbp)
	jmp	LBB0_8
LBB0_7:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	%rax, -80(%rbp)         ## 8-byte Spill
	callq	_end_expr
	movq	-80(%rbp), %rdi         ## 8-byte Reload
	movq	%rdi, 24(%rax)
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	xorl	%eax, %eax
	movb	%al, %cl
	movq	$0, -64(%rbp)
	testb	$1, %cl
	jne	LBB0_11
## BB#9:                                ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$0, -68(%rbp)
	je	LBB0_11
## BB#10:
	leaq	-56(%rbp), %rdi
	callq	_parser_clear_expr
	movl	$-1, -4(%rbp)
	jmp	LBB0_16
LBB0_11:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	LBB0_1
LBB0_12:
	movq	-32(%rbp), %rax
	cmpq	$0, (%rax)
	je	LBB0_14
## BB#13:
	movq	-32(%rbp), %rax
	movq	(%rax), %rdi
	callq	_end_expr
	addq	$24, %rax
	movq	%rax, -88(%rbp)         ## 8-byte Spill
	jmp	LBB0_15
LBB0_14:
	movq	-32(%rbp), %rax
	movq	%rax, -88(%rbp)         ## 8-byte Spill
LBB0_15:
	movq	-88(%rbp), %rax         ## 8-byte Reload
	movq	%rax, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, (%rcx)
	movl	$0, -4(%rbp)
LBB0_16:
	movl	-4(%rbp), %eax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
_build_expr_rule:                       ## @build_expr_rule
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$176, %rsp
	leaq	-80(%rbp), %rax
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rcx
	movq	%rcx, -96(%rbp)
	movq	-16(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, -88(%rbp)
	movq	-96(%rbp), %rcx
	movq	%rcx, -72(%rbp)
	movq	-88(%rbp), %rcx
	movq	%rcx, -64(%rbp)
	movq	-24(%rbp), %rdi
	movq	-72(%rbp), %rsi
	movq	-64(%rbp), %rdx
	movq	%rax, %rcx
	callq	_err_stack_push
	movq	$0, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rdi
	movq	-8(%rbp), %rax
	movq	(%rax), %rsi
	callq	_parser_tab_find
	cmpl	$0, %eax
	jne	LBB1_2
## BB#1:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
LBB1_2:
	movq	-8(%rbp), %rax
	cmpq	$0, 24(%rax)
	je	LBB1_4
## BB#3:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdi
	movq	-16(%rbp), %rsi
	callq	_parser_check_tok
	movl	%eax, -140(%rbp)        ## 4-byte Spill
	jmp	LBB1_5
LBB1_4:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rdi
	movq	-16(%rbp), %rsi
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	callq	_march_path
	movl	%eax, -140(%rbp)        ## 4-byte Spill
LBB1_5:
	movl	-140(%rbp), %eax        ## 4-byte Reload
	movl	%eax, -36(%rbp)
	cmpl	$0, -36(%rbp)
	jne	LBB1_8
## BB#6:
	cmpq	$0, -48(%rbp)
	je	LBB1_8
## BB#7:
	movl	$40, %eax
	movl	%eax, %edi
	callq	_try
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	-48(%rbp), %rdi
	movq	%rdi, -136(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rdi
	movq	%rax, -152(%rbp)        ## 8-byte Spill
	callq	_ft_strdup
	xorl	%esi, %esi
	movl	$40, %ecx
	movl	%ecx, %edx
	leaq	-136(%rbp), %rdi
	movq	%rax, -128(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	$0, -104(%rbp)
	movq	-152(%rbp), %rax        ## 8-byte Reload
	movq	%rdi, -160(%rbp)        ## 8-byte Spill
	movq	%rax, %rdi
	movq	-160(%rbp), %rax        ## 8-byte Reload
	movl	%esi, -164(%rbp)        ## 4-byte Spill
	movq	%rax, %rsi
	callq	_memcpy
	movq	-48(%rbp), %rdi
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rdx
	subq	%rdx, %rax
	movl	-164(%rbp), %esi        ## 4-byte Reload
	movq	%rax, %rdx
	callq	_ft_strsub
	leaq	-48(%rbp), %rdi
	movq	%rax, -48(%rbp)
	callq	_ft_trim
	movq	-56(%rbp), %rdx
	movq	%rax, 16(%rdx)
	movq	-56(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rax, (%rdx)
LBB1_8:
	cmpq	$0, -80(%rbp)
	je	LBB1_11
## BB#9:
	movq	-64(%rbp), %rax
	movq	-80(%rbp), %rcx
	movq	(%rcx), %rcx
	cmpq	8(%rcx), %rax
	jae	LBB1_11
## BB#10:
	movq	_ft_del@GOTPCREL(%rip), %rsi
	movq	-80(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	callq	_ft_lstdel
LBB1_11:
	movl	-36(%rbp), %eax
	addq	$176, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
_build_expr_opts:                       ## @build_expr_opts
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-24(%rbp), %rcx
	movq	32(%rcx), %rcx
	movq	%rcx, -64(%rbp)
	movq	-24(%rbp), %rcx
	movq	$0, 32(%rcx)
	movq	$0, -56(%rbp)
	movl	$1, -36(%rbp)
	movq	-16(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, -48(%rbp)
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	xorl	%eax, %eax
	movb	%al, %cl
	cmpl	$0, -36(%rbp)
	movb	%cl, -65(%rbp)          ## 1-byte Spill
	je	LBB2_3
## BB#2:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-8(%rbp), %rax
	cmpq	$0, (%rax)
	setne	%cl
	movb	%cl, -65(%rbp)          ## 1-byte Spill
LBB2_3:                                 ##   in Loop: Header=BB2_1 Depth=1
	movb	-65(%rbp), %al          ## 1-byte Reload
	testb	$1, %al
	jne	LBB2_4
	jmp	LBB2_13
LBB2_4:                                 ##   in Loop: Header=BB2_1 Depth=1
	movq	-8(%rbp), %rax
	movq	(%rax), %rdi
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rcx
	callq	_build_expr_rule
	movl	%eax, -36(%rbp)
	cmpl	$0, %eax
	je	LBB2_6
## BB#5:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-48(%rbp), %rax
	movq	-16(%rbp), %rcx
	movq	%rax, (%rcx)
LBB2_6:                                 ##   in Loop: Header=BB2_1 Depth=1
	cmpl	$0, -36(%rbp)
	jne	LBB2_8
## BB#7:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-48(%rbp), %rax
	movq	-16(%rbp), %rcx
	cmpq	(%rcx), %rax
	jne	LBB2_10
LBB2_8:                                 ##   in Loop: Header=BB2_1 Depth=1
	cmpq	$0, -56(%rbp)
	je	LBB2_10
## BB#9:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-56(%rbp), %rdi
	callq	_ft_lstsize
	movq	-24(%rbp), %rdi
	movq	32(%rdi), %rdi
	movq	%rax, -80(%rbp)         ## 8-byte Spill
	callq	_ft_lstsize
	movq	-80(%rbp), %rdi         ## 8-byte Reload
	cmpq	%rax, %rdi
	jae	LBB2_11
LBB2_10:                                ##   in Loop: Header=BB2_1 Depth=1
	leaq	-56(%rbp), %rdi
	movq	_ft_del@GOTPCREL(%rip), %rsi
	callq	_ft_lstdel
	movq	-24(%rbp), %rsi
	movq	32(%rsi), %rsi
	movq	%rsi, -56(%rbp)
	movq	-24(%rbp), %rsi
	movq	$0, 32(%rsi)
	jmp	LBB2_12
LBB2_11:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	_ft_del@GOTPCREL(%rip), %rsi
	movq	-24(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rdi
	callq	_ft_lstdel
LBB2_12:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_1
LBB2_13:
	movq	-24(%rbp), %rdi
	movq	-64(%rbp), %rsi
	movq	-56(%rbp), %rdx
	movl	-36(%rbp), %ecx
	callq	_keep_stack
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.align	4, 0x90
_keep_stack:                            ## @keep_stack
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp9:
	.cfi_def_cfa_offset 16
Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp11:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movl	%ecx, -28(%rbp)
	cmpq	$0, -16(%rbp)
	je	LBB3_2
## BB#1:
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdi
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	callq	_ft_lstend
	movq	-40(%rbp), %rdi         ## 8-byte Reload
	movq	%rdi, 16(%rax)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdi
	movq	%rax, 32(%rdi)
LBB3_2:
	movl	-28(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
