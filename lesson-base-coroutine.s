	.file	"lesson-base-coroutine.cpp"
# GNU C++20 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O0 -std=c++20 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZNSt7__n486116coroutine_handleIvE12from_addressEPv,"axG",@progbits,_ZNSt7__n486116coroutine_handleIvE12from_addressEPv,comdat
	.weak	_ZNSt7__n486116coroutine_handleIvE12from_addressEPv
	.type	_ZNSt7__n486116coroutine_handleIvE12from_addressEPv, @function
_ZNSt7__n486116coroutine_handleIvE12from_addressEPv:
.LFB2287:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# __a, __a
# /usr/include/c++/11/coroutine:107:       constexpr static coroutine_handle from_address(void* __a) noexcept
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp86
	movq	%rax, -8(%rbp)	# tmp86, D.130707
	xorl	%eax, %eax	# tmp86
# /usr/include/c++/11/coroutine:109: 	coroutine_handle __self;
	movq	$0, -16(%rbp)	#, __self._M_fr_ptr
# /usr/include/c++/11/coroutine:110: 	__self._M_fr_ptr = __a;
	movq	-24(%rbp), %rax	# __a, tmp84
	movq	%rax, -16(%rbp)	# tmp84, __self._M_fr_ptr
# /usr/include/c++/11/coroutine:111: 	return __self;
	movq	-16(%rbp), %rax	# __self, D.130629
# /usr/include/c++/11/coroutine:112:       }
	movq	-8(%rbp), %rdx	# D.130707, tmp87
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp87
	je	.L3	#,
	call	__stack_chk_fail@PLT	#
.L3:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2287:
	.size	_ZNSt7__n486116coroutine_handleIvE12from_addressEPv, .-_ZNSt7__n486116coroutine_handleIvE12from_addressEPv
	.section	.text._ZNKSt7__n486116coroutine_handleIvE6resumeEv,"axG",@progbits,_ZNKSt7__n486116coroutine_handleIvE6resumeEv,comdat
	.align 2
	.weak	_ZNKSt7__n486116coroutine_handleIvE6resumeEv
	.type	_ZNKSt7__n486116coroutine_handleIvE6resumeEv, @function
_ZNKSt7__n486116coroutine_handleIvE6resumeEv:
.LFB2291:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/11/coroutine:126:       void resume() const { __builtin_coro_resume(_M_fr_ptr); }
	movq	-8(%rbp), %rax	# this, tmp84
	movq	(%rax), %rax	# this_4(D)->_M_fr_ptr, _1
	movq	(%rax), %rdx	# MEM[(void (*<Tf2>) (void *) *)_1], _2
# /usr/include/c++/11/coroutine:126:       void resume() const { __builtin_coro_resume(_M_fr_ptr); }
	movq	%rax, %rdi	# _1,
	call	*%rdx	# _2
# /usr/include/c++/11/coroutine:126:       void resume() const { __builtin_coro_resume(_M_fr_ptr); }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2291:
	.size	_ZNKSt7__n486116coroutine_handleIvE6resumeEv, .-_ZNKSt7__n486116coroutine_handleIvE6resumeEv
	.section	.text._ZNKSt7__n486113suspend_never11await_readyEv,"axG",@progbits,_ZNKSt7__n486113suspend_never11await_readyEv,comdat
	.align 2
	.weak	_ZNKSt7__n486113suspend_never11await_readyEv
	.type	_ZNKSt7__n486113suspend_never11await_readyEv, @function
_ZNKSt7__n486113suspend_never11await_readyEv:
.LFB2325:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/11/coroutine:324:     constexpr bool await_ready() const noexcept { return true; }
	movl	$1, %eax	#, _1
# /usr/include/c++/11/coroutine:324:     constexpr bool await_ready() const noexcept { return true; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2325:
	.size	_ZNKSt7__n486113suspend_never11await_readyEv, .-_ZNKSt7__n486113suspend_never11await_readyEv
	.section	.text._ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE,"axG",@progbits,_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE,comdat
	.align 2
	.weak	_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE
	.type	_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE, @function
_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE:
.LFB2326:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.58157, D.58157
# /usr/include/c++/11/coroutine:326:     constexpr void await_suspend(coroutine_handle<>) const noexcept {}
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2326:
	.size	_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE, .-_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE
	.section	.text._ZNKSt7__n486113suspend_never12await_resumeEv,"axG",@progbits,_ZNKSt7__n486113suspend_never12await_resumeEv,comdat
	.align 2
	.weak	_ZNKSt7__n486113suspend_never12await_resumeEv
	.type	_ZNKSt7__n486113suspend_never12await_resumeEv, @function
_ZNKSt7__n486113suspend_never12await_resumeEv:
.LFB2327:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/11/coroutine:328:     constexpr void await_resume() const noexcept {}
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2327:
	.size	_ZNKSt7__n486113suspend_never12await_resumeEv, .-_ZNKSt7__n486113suspend_never12await_resumeEv
	.section	.rodata
	.align 4
	.type	_ZN9__gnu_cxxL21__default_lock_policyE, @object
	.size	_ZN9__gnu_cxxL21__default_lock_policyE, 4
_ZN9__gnu_cxxL21__default_lock_policyE:
	.long	2
	.align 8
	.type	_ZNSt8__detailL25__platform_wait_alignmentE, @object
	.size	_ZNSt8__detailL25__platform_wait_alignmentE, 8
_ZNSt8__detailL25__platform_wait_alignmentE:
	.quad	4
	.align 4
	.type	_ZNSt8__detailL25__atomic_spin_count_relaxE, @object
	.size	_ZNSt8__detailL25__atomic_spin_count_relaxE, 4
_ZNSt8__detailL25__atomic_spin_count_relaxE:
	.long	12
	.align 4
	.type	_ZNSt8__detailL19__atomic_spin_countE, @object
	.size	_ZNSt8__detailL19__atomic_spin_countE, 4
_ZNSt8__detailL19__atomic_spin_countE:
	.long	16
	.section	.text._ZN6Result12promise_typeC2Ev,"axG",@progbits,_ZN6Result12promise_typeC5Ev,comdat
	.align 2
	.weak	_ZN6Result12promise_typeC2Ev
	.type	_ZN6Result12promise_typeC2Ev, @function
_ZN6Result12promise_typeC2Ev:
.LFB4718:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:16:     }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4718:
	.size	_ZN6Result12promise_typeC2Ev, .-_ZN6Result12promise_typeC2Ev
	.weak	_ZN6Result12promise_typeC1Ev
	.set	_ZN6Result12promise_typeC1Ev,_ZN6Result12promise_typeC2Ev
	.section	.text._ZN6Result12promise_typeD2Ev,"axG",@progbits,_ZN6Result12promise_typeD5Ev,comdat
	.align 2
	.weak	_ZN6Result12promise_typeD2Ev
	.type	_ZN6Result12promise_typeD2Ev, @function
_ZN6Result12promise_typeD2Ev:
.LFB4721:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:19:     }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4721:
	.size	_ZN6Result12promise_typeD2Ev, .-_ZN6Result12promise_typeD2Ev
	.weak	_ZN6Result12promise_typeD1Ev
	.set	_ZN6Result12promise_typeD1Ev,_ZN6Result12promise_typeD2Ev
	.section	.text._ZN6Result12promise_type15initial_suspendEv,"axG",@progbits,_ZN6Result12promise_type15initial_suspendEv,comdat
	.align 2
	.weak	_ZN6Result12promise_type15initial_suspendEv
	.type	_ZN6Result12promise_type15initial_suspendEv, @function
_ZN6Result12promise_type15initial_suspendEv:
.LFB4723:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:21:       return {};
	nop	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:22:     }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4723:
	.size	_ZN6Result12promise_type15initial_suspendEv, .-_ZN6Result12promise_type15initial_suspendEv
	.section	.text._ZN6Result12promise_type13final_suspendEv,"axG",@progbits,_ZN6Result12promise_type13final_suspendEv,comdat
	.align 2
	.weak	_ZN6Result12promise_type13final_suspendEv
	.type	_ZN6Result12promise_type13final_suspendEv, @function
_ZN6Result12promise_type13final_suspendEv:
.LFB4724:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:25:       return {};
	nop	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:26:     }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4724:
	.size	_ZN6Result12promise_type13final_suspendEv, .-_ZN6Result12promise_type13final_suspendEv
	.section	.text._ZN6Result12promise_type17get_return_objectEv,"axG",@progbits,_ZN6Result12promise_type17get_return_objectEv,comdat
	.align 2
	.weak	_ZN6Result12promise_type17get_return_objectEv
	.type	_ZN6Result12promise_type17get_return_objectEv, @function
_ZN6Result12promise_type17get_return_objectEv:
.LFB4725:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:29:       return {};
	nop	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:30:     }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4725:
	.size	_ZN6Result12promise_type17get_return_objectEv, .-_ZN6Result12promise_type17get_return_objectEv
	.section	.text._ZN6Result12promise_type11return_voidEv,"axG",@progbits,_ZN6Result12promise_type11return_voidEv,comdat
	.align 2
	.weak	_ZN6Result12promise_type11return_voidEv
	.type	_ZN6Result12promise_type11return_voidEv, @function
_ZN6Result12promise_type11return_voidEv:
.LFB4726:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:32:     }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4726:
	.size	_ZN6Result12promise_type11return_voidEv, .-_ZN6Result12promise_type11return_voidEv
	.section	.text._ZN6Result12promise_type19unhandled_exceptionEv,"axG",@progbits,_ZN6Result12promise_type19unhandled_exceptionEv,comdat
	.align 2
	.weak	_ZN6Result12promise_type19unhandled_exceptionEv
	.type	_ZN6Result12promise_type19unhandled_exceptionEv, @function
_ZN6Result12promise_type19unhandled_exceptionEv:
.LFB4727:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:40:     }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4727:
	.size	_ZN6Result12promise_type19unhandled_exceptionEv, .-_ZN6Result12promise_type19unhandled_exceptionEv
	.text
	.globl	_Z4funcNSt7__n486116coroutine_handleIvEE
	.type	_Z4funcNSt7__n486116coroutine_handleIvEE, @function
_Z4funcNSt7__n486116coroutine_handleIvEE:
.LFB4728:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# coroutine_handle, coroutine_handle
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:50:   coroutine_handle.resume();
	leaq	-8(%rbp), %rax	#, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZNKSt7__n486116coroutine_handleIvE6resumeEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:52: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4728:
	.size	_Z4funcNSt7__n486116coroutine_handleIvEE, .-_Z4funcNSt7__n486116coroutine_handleIvEE
	.section	.text._ZN7Awaiter11await_readyEv,"axG",@progbits,_ZN7Awaiter11await_readyEv,comdat
	.align 2
	.weak	_ZN7Awaiter11await_readyEv
	.type	_ZN7Awaiter11await_readyEv, @function
_ZN7Awaiter11await_readyEv:
.LFB4729:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:57:     return false;
	movl	$0, %eax	#, _1
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:58:   }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4729:
	.size	_ZN7Awaiter11await_readyEv, .-_ZN7Awaiter11await_readyEv
	.section	.text._ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE,"axG",@progbits,_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE,comdat
	.align 2
	.weak	_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE
	.type	_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE, @function
_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE:
.LFB4730:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# coroutine_handle, coroutine_handle
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:67:     func(coroutine_handle);
	movq	-16(%rbp), %rax	# coroutine_handle, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_Z4funcNSt7__n486116coroutine_handleIvEE	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:68:   }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4730:
	.size	_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE, .-_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE
	.section	.text._ZN7Awaiter12await_resumeEv,"axG",@progbits,_ZN7Awaiter12await_resumeEv,comdat
	.align 2
	.weak	_ZN7Awaiter12await_resumeEv
	.type	_ZN7Awaiter12await_resumeEv, @function
_ZN7Awaiter12await_resumeEv:
.LFB4731:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:71:     return value;
	movq	-8(%rbp), %rax	# this, tmp84
	movl	(%rax), %eax	# this_2(D)->value, _3
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:72:   }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4731:
	.size	_ZN7Awaiter12await_resumeEv, .-_ZN7Awaiter12await_resumeEv
	.text
	.globl	_Z9Coroutinev
	.type	_Z9Coroutinev, @function
_Z9Coroutinev:
.LFB4732:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4732
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	$0, -24(%rbp)	#, _Coro_frameptr
	movb	$0, -26(%rbp)	#, _Coro_promise_live
	movb	$0, -25(%rbp)	#, _Coro_gro_live
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movl	$56, %eax	#, _1
	movq	%rax, %rdi	# _1,
.LEHB0:
	call	_Znwm@PLT	#
.LEHE0:
	movq	%rax, -24(%rbp)	# _12, _Coro_frameptr
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp91
	movb	$1, 34(%rax)	#, _Coro_frameptr_13->_Coro_frame_needs_free
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp92
	leaq	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.actor(%rip), %rdx	#, tmp93
	movq	%rdx, (%rax)	# tmp93, _Coro_frameptr_13->_Coro_resume_fn
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp94
	leaq	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.destroy(%rip), %rdx	#, tmp95
	movq	%rdx, 8(%rax)	# tmp95, _Coro_frameptr_13->_Coro_destroy_fn
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp96
	addq	$16, %rax	#, _2
	movq	%rax, %rdi	# _2,
	call	_ZN6Result12promise_typeC1Ev	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movb	$1, -26(%rbp)	#, _Coro_promise_live
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp97
	addq	$16, %rax	#, _3
	movq	%rax, %rdi	# _3,
	call	_ZN6Result12promise_type17get_return_objectEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp98
	movw	$0, 32(%rax)	#, _Coro_frameptr_13->_Coro_resume_index
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp99
	movq	%rax, %rdi	# tmp99,
.LEHB1:
	call	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.actor	#
.LEHE1:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	jmp	.L32	#
.L30:
	endbr64	
	movq	%rax, %rdi	# _4,
	call	__cxa_begin_catch@PLT	#
	cmpb	$0, -26(%rbp)	#, _Coro_promise_live
	je	.L28	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp101
	addq	$16, %rax	#, _5
	movq	%rax, %rdi	# _5,
	call	_ZN6Result12promise_typeD1Ev	#
.L28:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp102
	movq	%rax, %rdi	# tmp102,
	call	_ZdlPv@PLT	#
.LEHB2:
	call	__cxa_rethrow@PLT	#
.LEHE2:
.L31:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	%rax, %rbx	#, tmp103
	call	__cxa_end_catch@PLT	#
	movq	%rbx, %rax	# tmp103, D.130709
	movq	%rax, %rdi	# D.130709,
.LEHB3:
	call	_Unwind_Resume@PLT	#
.LEHE3:
.L32:
	movl	%ebx, %eax	# <retval>,
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4732:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
	.align 4
.LLSDA4732:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT4732-.LLSDATTD4732
.LLSDATTD4732:
	.byte	0x1
	.uleb128 .LLSDACSE4732-.LLSDACSB4732
.LLSDACSB4732:
	.uleb128 .LEHB0-.LFB4732
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB4732
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L30-.LFB4732
	.uleb128 0x1
	.uleb128 .LEHB2-.LFB4732
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L31-.LFB4732
	.uleb128 0
	.uleb128 .LEHB3-.LFB4732
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE4732:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT4732:
	.text
	.size	_Z9Coroutinev, .-_Z9Coroutinev
	.type	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.actor, @function
_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.actor:
.LFB4733:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4733
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)	# frame_ptr, frame_ptr
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp159
	movq	%rax, -24(%rbp)	# tmp159, D.130711
	xorl	%eax, %eax	# tmp159
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp120
	movzwl	32(%rax), %eax	# frame_ptr_42(D)->_Coro_resume_index, _1
	andl	$1, %eax	#, _2
	testw	%ax, %ax	# _2
	je	.L34	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp121
	movzwl	32(%rax), %eax	# frame_ptr_42(D)->_Coro_resume_index, _3
	movzwl	%ax, %eax	# _3, _4
	cmpl	$7, %eax	#, _4
	je	.L43	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	cmpl	$7, %eax	#, _4
	jg	.L36	#,
	cmpl	$5, %eax	#, _4
	je	.L42	#,
	cmpl	$5, %eax	#, _4
	jg	.L36	#,
	cmpl	$1, %eax	#, _4
	je	.L64	#,
	cmpl	$3, %eax	#, _4
	je	.L41	#,
.L36:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	ud2	
.L34:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp122
	movzwl	32(%rax), %eax	# frame_ptr_42(D)->_Coro_resume_index, _5
	movzwl	%ax, %eax	# _5, _6
	cmpl	$6, %eax	#, _6
	je	.L52	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	cmpl	$6, %eax	#, _6
	jg	.L45	#,
	cmpl	$4, %eax	#, _6
	je	.L51	#,
	cmpl	$4, %eax	#, _6
	jg	.L45	#,
	testl	%eax, %eax	# _6
	je	.L47	#,
	cmpl	$2, %eax	#, _6
	je	.L50	#,
	jmp	.L45	#
.L47:
	movq	-40(%rbp), %rbx	# frame_ptr, tmp123
	movq	-40(%rbp), %rax	# frame_ptr, tmp124
	movq	%rax, %rdi	# tmp124,
	call	_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv	#
	movq	%rax, 24(%rbx)	# tmp125, frame_ptr_42(D)->_Coro_self_handle
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp126
	movb	$0, 35(%rax)	#, frame_ptr_42(D)->_Coro_initial_await_resume_called
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp127
	addq	$16, %rax	#, _7
	movq	%rax, %rdi	# _7,
	call	_ZN6Result12promise_type15initial_suspendEv	#
	movq	-40(%rbp), %rax	# frame_ptr, tmp128
	addq	$36, %rax	#, _8
	movq	%rax, %rdi	# _8,
	call	_ZNKSt7__n486113suspend_never11await_readyEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	xorl	$1, %eax	#, retval.0_47
	testb	%al, %al	# retval.0_47
	jne	.L49	#,
	jmp	.L50	#
.L45:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	ud2	
.L49:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp129
	movw	$2, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp130
	leaq	36(%rax), %rbx	#, _10
	movq	-40(%rbp), %rax	# frame_ptr, tmp131
	addq	$24, %rax	#, _11
	movq	%rax, %rdi	# _11,
	call	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv	#
	movq	%rax, %rsi	# D.130590,
	movq	%rbx, %rdi	# _10,
	call	_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	jmp	.L53	#
.L41:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	jmp	.L40	#
.L50:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp132
	movb	$1, 35(%rax)	#, frame_ptr_42(D)->_Coro_initial_await_resume_called
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp133
	addq	$36, %rax	#, _12
	movq	%rax, %rdi	# _12,
	call	_ZNKSt7__n486113suspend_never12await_resumeEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:76:   int b = 22;
	movq	-40(%rbp), %rax	# frame_ptr, tmp134
	movl	$22, 40(%rax)	#, frame_ptr_42(D)->b_1_2
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp135
	movl	$1000, 48(%rax)	#, frame_ptr_42(D)->Aw0_2_3.value
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:78:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp136
	addq	$48, %rax	#, _13
	movq	%rax, %rdi	# _13,
	call	_ZN7Awaiter11await_readyEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:78:   co_await Awaiter{.value = 1000};
	xorl	$1, %eax	#, retval.2_56
	testb	%al, %al	# retval.2_56
	je	.L51	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:78:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp137
	movw	$4, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:78:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp138
	leaq	48(%rax), %rbx	#, _15
	movq	-40(%rbp), %rax	# frame_ptr, tmp139
	addq	$24, %rax	#, _16
	movq	%rax, %rdi	# _16,
	call	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv	#
	movq	%rax, %rsi	# D.130595,
	movq	%rbx, %rdi	# _15,
.LEHB4:
	call	_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE	#
.LEHE4:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:78:   co_await Awaiter{.value = 1000};
	jmp	.L53	#
.L42:
	jmp	.L40	#
.L51:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:78:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp140
	addq	$48, %rax	#, _17
	movq	%rax, %rdi	# _17,
	call	_ZN7Awaiter12await_resumeEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:80:   int a  = 22;
	movq	-40(%rbp), %rax	# frame_ptr, tmp141
	movl	$22, 44(%rax)	#, frame_ptr_42(D)->a_1_2
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:82:   co_return;
	movq	-40(%rbp), %rax	# frame_ptr, tmp142
	addq	$16, %rax	#, _18
	movq	%rax, %rdi	# _18,
	call	_ZN6Result12promise_type11return_voidEv	#
.L59:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp143
	movq	$0, (%rax)	#, frame_ptr_42(D)->_Coro_resume_fn
	movq	-40(%rbp), %rax	# frame_ptr, tmp144
	addq	$16, %rax	#, _24
	movq	%rax, %rdi	# _24,
	call	_ZN6Result12promise_type13final_suspendEv	#
	movq	-40(%rbp), %rax	# frame_ptr, tmp145
	addq	$52, %rax	#, _25
	movq	%rax, %rdi	# _25,
	call	_ZNKSt7__n486113suspend_never11await_readyEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	xorl	$1, %eax	#, retval.4_74
	testb	%al, %al	# retval.4_74
	je	.L52	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp146
	movw	$6, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp147
	leaq	52(%rax), %rbx	#, _27
	movq	-40(%rbp), %rax	# frame_ptr, tmp148
	addq	$24, %rax	#, _28
	movq	%rax, %rdi	# _28,
	call	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv	#
	movq	%rax, %rsi	# D.130602,
	movq	%rbx, %rdi	# _27,
	call	_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	jmp	.L53	#
.L43:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	jmp	.L40	#
.L52:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp149
	addq	$52, %rax	#, _29
	movq	%rax, %rdi	# _29,
	call	_ZNKSt7__n486113suspend_never12await_resumeEv	#
	jmp	.L40	#
.L64:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	nop	
.L40:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp150
	addq	$16, %rax	#, _30
	movq	%rax, %rdi	# _30,
	call	_ZN6Result12promise_typeD1Ev	#
	movq	-40(%rbp), %rax	# frame_ptr, tmp151
	movzbl	34(%rax), %eax	# frame_ptr_42(D)->_Coro_frame_needs_free, _31
	movzbl	%al, %eax	# _31, _32
	testl	%eax, %eax	# _32
	je	.L65	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp152
	movq	%rax, %rdi	# tmp152,
	call	_ZdlPv@PLT	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	jmp	.L65	#
.L53:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	jmp	.L65	#
.L62:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	%rax, %rdi	# _20,
	call	__cxa_begin_catch@PLT	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp154
	movzbl	35(%rax), %eax	# frame_ptr_42(D)->_Coro_initial_await_resume_called, _21
	xorl	$1, %eax	#, _22
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	testb	%al, %al	# _22
	je	.L58	#,
.LEHB5:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	call	__cxa_rethrow@PLT	#
.LEHE5:
.L58:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp155
	movq	$0, (%rax)	#, frame_ptr_42(D)->_Coro_resume_fn
	movq	-40(%rbp), %rax	# frame_ptr, tmp156
	movw	$0, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
	movq	-40(%rbp), %rax	# frame_ptr, tmp157
	addq	$16, %rax	#, _23
	movq	%rax, %rdi	# _23,
	call	_ZN6Result12promise_type19unhandled_exceptionEv	#
.LEHB6:
	call	__cxa_end_catch@PLT	#
.LEHE6:
	jmp	.L59	#
.L63:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:83: };
	movq	%rax, %rbx	#, tmp158
	call	__cxa_end_catch@PLT	#
	movq	%rbx, %rax	# tmp158, D.130710
	movq	%rax, %rdi	# D.130710,
.LEHB7:
	call	_Unwind_Resume@PLT	#
.LEHE7:
.L65:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	nop	
	movq	-24(%rbp), %rax	# D.130711, tmp160
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp160
	je	.L61	#,
	call	__stack_chk_fail@PLT	#
.L61:
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4733:
	.section	.gcc_except_table
	.align 4
.LLSDA4733:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT4733-.LLSDATTD4733
.LLSDATTD4733:
	.byte	0x1
	.uleb128 .LLSDACSE4733-.LLSDACSB4733
.LLSDACSB4733:
	.uleb128 .LEHB4-.LFB4733
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L62-.LFB4733
	.uleb128 0x1
	.uleb128 .LEHB5-.LFB4733
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L63-.LFB4733
	.uleb128 0
	.uleb128 .LEHB6-.LFB4733
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB4733
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
.LLSDACSE4733:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT4733:
	.text
	.size	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.actor, .-_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.actor
	.type	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.destroy, @function
_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.destroy:
.LFB4734:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# frame_ptr, frame_ptr
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:75: Result Coroutine() {
	movq	-8(%rbp), %rax	# frame_ptr, tmp84
	movzwl	32(%rax), %eax	# frame_ptr_4(D)->_Coro_resume_index, _1
	orl	$1, %eax	#, _1
	movl	%eax, %edx	# _1, _2
	movq	-8(%rbp), %rax	# frame_ptr, tmp85
	movw	%dx, 32(%rax)	# _2, frame_ptr_4(D)->_Coro_resume_index
	movq	-8(%rbp), %rax	# frame_ptr, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.actor	#
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4734:
	.size	_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.destroy, .-_Z9CoroutinePZ9CoroutinevE19_Z9Coroutinev.Frame.destroy
	.globl	_Z4testv
	.type	_Z4testv, @function
_Z4testv:
.LFB4735:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4735
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	$0, -24(%rbp)	#, _Coro_frameptr
	movb	$0, -26(%rbp)	#, _Coro_promise_live
	movb	$0, -25(%rbp)	#, _Coro_gro_live
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movl	$56, %eax	#, _1
	movq	%rax, %rdi	# _1,
.LEHB8:
	call	_Znwm@PLT	#
.LEHE8:
	movq	%rax, -24(%rbp)	# _12, _Coro_frameptr
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp91
	movb	$1, 34(%rax)	#, _Coro_frameptr_13->_Coro_frame_needs_free
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp92
	leaq	_Z4testPZ4testvE14_Z4testv.Frame.actor(%rip), %rdx	#, tmp93
	movq	%rdx, (%rax)	# tmp93, _Coro_frameptr_13->_Coro_resume_fn
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp94
	leaq	_Z4testPZ4testvE14_Z4testv.Frame.destroy(%rip), %rdx	#, tmp95
	movq	%rdx, 8(%rax)	# tmp95, _Coro_frameptr_13->_Coro_destroy_fn
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp96
	addq	$16, %rax	#, _2
	movq	%rax, %rdi	# _2,
	call	_ZN6Result12promise_typeC1Ev	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movb	$1, -26(%rbp)	#, _Coro_promise_live
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp97
	addq	$16, %rax	#, _3
	movq	%rax, %rdi	# _3,
	call	_ZN6Result12promise_type17get_return_objectEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp98
	movw	$0, 32(%rax)	#, _Coro_frameptr_13->_Coro_resume_index
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp99
	movq	%rax, %rdi	# tmp99,
.LEHB9:
	call	_Z4testPZ4testvE14_Z4testv.Frame.actor	#
.LEHE9:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	jmp	.L75	#
.L73:
	endbr64	
	movq	%rax, %rdi	# _4,
	call	__cxa_begin_catch@PLT	#
	cmpb	$0, -26(%rbp)	#, _Coro_promise_live
	je	.L71	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp101
	addq	$16, %rax	#, _5
	movq	%rax, %rdi	# _5,
	call	_ZN6Result12promise_typeD1Ev	#
.L71:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-24(%rbp), %rax	# _Coro_frameptr, tmp102
	movq	%rax, %rdi	# tmp102,
	call	_ZdlPv@PLT	#
.LEHB10:
	call	__cxa_rethrow@PLT	#
.LEHE10:
.L74:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	%rax, %rbx	#, tmp103
	call	__cxa_end_catch@PLT	#
	movq	%rbx, %rax	# tmp103, D.130712
	movq	%rax, %rdi	# D.130712,
.LEHB11:
	call	_Unwind_Resume@PLT	#
.LEHE11:
.L75:
	movl	%ebx, %eax	# <retval>,
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4735:
	.section	.gcc_except_table
	.align 4
.LLSDA4735:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT4735-.LLSDATTD4735
.LLSDATTD4735:
	.byte	0x1
	.uleb128 .LLSDACSE4735-.LLSDACSB4735
.LLSDACSB4735:
	.uleb128 .LEHB8-.LFB4735
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB9-.LFB4735
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L73-.LFB4735
	.uleb128 0x1
	.uleb128 .LEHB10-.LFB4735
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L74-.LFB4735
	.uleb128 0
	.uleb128 .LEHB11-.LFB4735
	.uleb128 .LEHE11-.LEHB11
	.uleb128 0
	.uleb128 0
.LLSDACSE4735:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT4735:
	.text
	.size	_Z4testv, .-_Z4testv
	.type	_Z4testPZ4testvE14_Z4testv.Frame.actor, @function
_Z4testPZ4testvE14_Z4testv.Frame.actor:
.LFB4736:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4736
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)	# frame_ptr, frame_ptr
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp159
	movq	%rax, -24(%rbp)	# tmp159, D.130714
	xorl	%eax, %eax	# tmp159
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp120
	movzwl	32(%rax), %eax	# frame_ptr_42(D)->_Coro_resume_index, _1
	andl	$1, %eax	#, _2
	testw	%ax, %ax	# _2
	je	.L77	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp121
	movzwl	32(%rax), %eax	# frame_ptr_42(D)->_Coro_resume_index, _3
	movzwl	%ax, %eax	# _3, _4
	cmpl	$7, %eax	#, _4
	je	.L86	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	cmpl	$7, %eax	#, _4
	jg	.L79	#,
	cmpl	$5, %eax	#, _4
	je	.L85	#,
	cmpl	$5, %eax	#, _4
	jg	.L79	#,
	cmpl	$1, %eax	#, _4
	je	.L107	#,
	cmpl	$3, %eax	#, _4
	je	.L84	#,
.L79:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	ud2	
.L77:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp122
	movzwl	32(%rax), %eax	# frame_ptr_42(D)->_Coro_resume_index, _5
	movzwl	%ax, %eax	# _5, _6
	cmpl	$6, %eax	#, _6
	je	.L95	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	cmpl	$6, %eax	#, _6
	jg	.L88	#,
	cmpl	$4, %eax	#, _6
	je	.L94	#,
	cmpl	$4, %eax	#, _6
	jg	.L88	#,
	testl	%eax, %eax	# _6
	je	.L90	#,
	cmpl	$2, %eax	#, _6
	je	.L93	#,
	jmp	.L88	#
.L90:
	movq	-40(%rbp), %rbx	# frame_ptr, tmp123
	movq	-40(%rbp), %rax	# frame_ptr, tmp124
	movq	%rax, %rdi	# tmp124,
	call	_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv	#
	movq	%rax, 24(%rbx)	# tmp125, frame_ptr_42(D)->_Coro_self_handle
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp126
	movb	$0, 35(%rax)	#, frame_ptr_42(D)->_Coro_initial_await_resume_called
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp127
	addq	$16, %rax	#, _7
	movq	%rax, %rdi	# _7,
	call	_ZN6Result12promise_type15initial_suspendEv	#
	movq	-40(%rbp), %rax	# frame_ptr, tmp128
	addq	$36, %rax	#, _8
	movq	%rax, %rdi	# _8,
	call	_ZNKSt7__n486113suspend_never11await_readyEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	xorl	$1, %eax	#, retval.6_47
	testb	%al, %al	# retval.6_47
	jne	.L92	#,
	jmp	.L93	#
.L88:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	ud2	
.L92:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp129
	movw	$2, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp130
	leaq	36(%rax), %rbx	#, _10
	movq	-40(%rbp), %rax	# frame_ptr, tmp131
	addq	$24, %rax	#, _11
	movq	%rax, %rdi	# _11,
	call	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv	#
	movq	%rax, %rsi	# D.130646,
	movq	%rbx, %rdi	# _10,
	call	_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	jmp	.L96	#
.L84:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	jmp	.L83	#
.L93:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp132
	movb	$1, 35(%rax)	#, frame_ptr_42(D)->_Coro_initial_await_resume_called
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp133
	addq	$36, %rax	#, _12
	movq	%rax, %rdi	# _12,
	call	_ZNKSt7__n486113suspend_never12await_resumeEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:86:   int b = 11;
	movq	-40(%rbp), %rax	# frame_ptr, tmp134
	movl	$11, 40(%rax)	#, frame_ptr_42(D)->b_1_2
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp135
	movl	$1000, 48(%rax)	#, frame_ptr_42(D)->Aw0_2_3.value
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:88:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp136
	addq	$48, %rax	#, _13
	movq	%rax, %rdi	# _13,
	call	_ZN7Awaiter11await_readyEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:88:   co_await Awaiter{.value = 1000};
	xorl	$1, %eax	#, retval.8_56
	testb	%al, %al	# retval.8_56
	je	.L94	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:88:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp137
	movw	$4, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:88:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp138
	leaq	48(%rax), %rbx	#, _15
	movq	-40(%rbp), %rax	# frame_ptr, tmp139
	addq	$24, %rax	#, _16
	movq	%rax, %rdi	# _16,
	call	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv	#
	movq	%rax, %rsi	# D.130651,
	movq	%rbx, %rdi	# _15,
.LEHB12:
	call	_ZN7Awaiter13await_suspendENSt7__n486116coroutine_handleIvEE	#
.LEHE12:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:88:   co_await Awaiter{.value = 1000};
	jmp	.L96	#
.L85:
	jmp	.L83	#
.L94:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:88:   co_await Awaiter{.value = 1000};
	movq	-40(%rbp), %rax	# frame_ptr, tmp140
	addq	$48, %rax	#, _17
	movq	%rax, %rdi	# _17,
	call	_ZN7Awaiter12await_resumeEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:90:   int a  = 33;
	movq	-40(%rbp), %rax	# frame_ptr, tmp141
	movl	$33, 44(%rax)	#, frame_ptr_42(D)->a_1_2
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:92:   co_return;
	movq	-40(%rbp), %rax	# frame_ptr, tmp142
	addq	$16, %rax	#, _18
	movq	%rax, %rdi	# _18,
	call	_ZN6Result12promise_type11return_voidEv	#
.L102:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp143
	movq	$0, (%rax)	#, frame_ptr_42(D)->_Coro_resume_fn
	movq	-40(%rbp), %rax	# frame_ptr, tmp144
	addq	$16, %rax	#, _24
	movq	%rax, %rdi	# _24,
	call	_ZN6Result12promise_type13final_suspendEv	#
	movq	-40(%rbp), %rax	# frame_ptr, tmp145
	addq	$52, %rax	#, _25
	movq	%rax, %rdi	# _25,
	call	_ZNKSt7__n486113suspend_never11await_readyEv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	xorl	$1, %eax	#, retval.10_74
	testb	%al, %al	# retval.10_74
	je	.L95	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp146
	movw	$6, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp147
	leaq	52(%rax), %rbx	#, _27
	movq	-40(%rbp), %rax	# frame_ptr, tmp148
	addq	$24, %rax	#, _28
	movq	%rax, %rdi	# _28,
	call	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv	#
	movq	%rax, %rsi	# D.130658,
	movq	%rbx, %rdi	# _27,
	call	_ZNKSt7__n486113suspend_never13await_suspendENS_16coroutine_handleIvEE	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	jmp	.L96	#
.L86:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	jmp	.L83	#
.L95:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp149
	addq	$52, %rax	#, _29
	movq	%rax, %rdi	# _29,
	call	_ZNKSt7__n486113suspend_never12await_resumeEv	#
	jmp	.L83	#
.L107:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	nop	
.L83:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp150
	addq	$16, %rax	#, _30
	movq	%rax, %rdi	# _30,
	call	_ZN6Result12promise_typeD1Ev	#
	movq	-40(%rbp), %rax	# frame_ptr, tmp151
	movzbl	34(%rax), %eax	# frame_ptr_42(D)->_Coro_frame_needs_free, _31
	movzbl	%al, %eax	# _31, _32
	testl	%eax, %eax	# _32
	je	.L108	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp152
	movq	%rax, %rdi	# tmp152,
	call	_ZdlPv@PLT	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	jmp	.L108	#
.L96:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	jmp	.L108	#
.L105:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	%rax, %rdi	# _20,
	call	__cxa_begin_catch@PLT	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-40(%rbp), %rax	# frame_ptr, tmp154
	movzbl	35(%rax), %eax	# frame_ptr_42(D)->_Coro_initial_await_resume_called, _21
	xorl	$1, %eax	#, _22
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	testb	%al, %al	# _22
	je	.L101	#,
.LEHB13:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	call	__cxa_rethrow@PLT	#
.LEHE13:
.L101:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	-40(%rbp), %rax	# frame_ptr, tmp155
	movq	$0, (%rax)	#, frame_ptr_42(D)->_Coro_resume_fn
	movq	-40(%rbp), %rax	# frame_ptr, tmp156
	movw	$0, 32(%rax)	#, frame_ptr_42(D)->_Coro_resume_index
	movq	-40(%rbp), %rax	# frame_ptr, tmp157
	addq	$16, %rax	#, _23
	movq	%rax, %rdi	# _23,
	call	_ZN6Result12promise_type19unhandled_exceptionEv	#
.LEHB14:
	call	__cxa_end_catch@PLT	#
.LEHE14:
	jmp	.L102	#
.L106:
	endbr64	
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:93: };
	movq	%rax, %rbx	#, tmp158
	call	__cxa_end_catch@PLT	#
	movq	%rbx, %rax	# tmp158, D.130713
	movq	%rax, %rdi	# D.130713,
.LEHB15:
	call	_Unwind_Resume@PLT	#
.LEHE15:
.L108:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	nop	
	movq	-24(%rbp), %rax	# D.130714, tmp160
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp160
	je	.L104	#,
	call	__stack_chk_fail@PLT	#
.L104:
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4736:
	.section	.gcc_except_table
	.align 4
.LLSDA4736:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT4736-.LLSDATTD4736
.LLSDATTD4736:
	.byte	0x1
	.uleb128 .LLSDACSE4736-.LLSDACSB4736
.LLSDACSB4736:
	.uleb128 .LEHB12-.LFB4736
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L105-.LFB4736
	.uleb128 0x1
	.uleb128 .LEHB13-.LFB4736
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L106-.LFB4736
	.uleb128 0
	.uleb128 .LEHB14-.LFB4736
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB15-.LFB4736
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
.LLSDACSE4736:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT4736:
	.text
	.size	_Z4testPZ4testvE14_Z4testv.Frame.actor, .-_Z4testPZ4testvE14_Z4testv.Frame.actor
	.type	_Z4testPZ4testvE14_Z4testv.Frame.destroy, @function
_Z4testPZ4testvE14_Z4testv.Frame.destroy:
.LFB4737:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# frame_ptr, frame_ptr
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:85: Result test() {
	movq	-8(%rbp), %rax	# frame_ptr, tmp84
	movzwl	32(%rax), %eax	# frame_ptr_4(D)->_Coro_resume_index, _1
	orl	$1, %eax	#, _1
	movl	%eax, %edx	# _1, _2
	movq	-8(%rbp), %rax	# frame_ptr, tmp85
	movw	%dx, 32(%rax)	# _2, frame_ptr_4(D)->_Coro_resume_index
	movq	-8(%rbp), %rax	# frame_ptr, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_Z4testPZ4testvE14_Z4testv.Frame.actor	#
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4737:
	.size	_Z4testPZ4testvE14_Z4testv.Frame.destroy, .-_Z4testPZ4testvE14_Z4testv.Frame.destroy
	.globl	main
	.type	main, @function
main:
.LFB4738:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:96:   Coroutine();
	call	_Z9Coroutinev	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:97:   test();
	call	_Z4testv	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:98:   getchar();
	call	getchar@PLT	#
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:99:   return 0;
	movl	$0, %eax	#, _5
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:100: }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4738:
	.size	main, .-main
	.section	.text._ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv,"axG",@progbits,_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv,comdat
	.align 2
	.weak	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv
	.type	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv, @function
_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv:
.LFB5375:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/11/coroutine:218:       { return coroutine_handle<>::from_address(address()); }
	movq	-8(%rbp), %rax	# this, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv	#
	movq	%rax, %rdi	# _1,
	call	_ZNSt7__n486116coroutine_handleIvE12from_addressEPv	#
# /usr/include/c++/11/coroutine:218:       { return coroutine_handle<>::from_address(address()); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE5375:
	.size	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv, .-_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEEcvNS0_IvEEEv
	.section	.text._ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv,"axG",@progbits,_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv,comdat
	.weak	_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv
	.type	_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv, @function
_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv:
.LFB5376:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# __a, __a
# /usr/include/c++/11/coroutine:209:       constexpr static coroutine_handle from_address(void* __a) noexcept
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp86
	movq	%rax, -8(%rbp)	# tmp86, D.130715
	xorl	%eax, %eax	# tmp86
# /usr/include/c++/11/coroutine:211: 	coroutine_handle __self;
	movq	$0, -16(%rbp)	#, __self._M_fr_ptr
# /usr/include/c++/11/coroutine:212: 	__self._M_fr_ptr = __a;
	movq	-24(%rbp), %rax	# __a, tmp84
	movq	%rax, -16(%rbp)	# tmp84, __self._M_fr_ptr
# /usr/include/c++/11/coroutine:213: 	return __self;
	movq	-16(%rbp), %rax	# __self, D.130614
# /usr/include/c++/11/coroutine:214:       }
	movq	-8(%rbp), %rdx	# D.130715, tmp87
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp87
	je	.L117	#,
	call	__stack_chk_fail@PLT	#
.L117:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE5376:
	.size	_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv, .-_ZNSt7__n486116coroutine_handleIN6Result12promise_typeEE12from_addressEPv
	.section	.text._ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv,"axG",@progbits,_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv,comdat
	.align 2
	.weak	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv
	.type	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv, @function
_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv:
.LFB5670:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/11/coroutine:207:       constexpr void* address() const noexcept { return _M_fr_ptr; }
	movq	-8(%rbp), %rax	# this, tmp84
	movq	(%rax), %rax	# this_2(D)->_M_fr_ptr, _3
# /usr/include/c++/11/coroutine:207:       constexpr void* address() const noexcept { return _M_fr_ptr; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE5670:
	.size	_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv, .-_ZNKSt7__n486116coroutine_handleIN6Result12promise_typeEE7addressEv
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB6276:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movl	%edi, -4(%rbp)	# __initialize_p, __initialize_p
	movl	%esi, -8(%rbp)	# __priority, __priority
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:100: }
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L122	#,
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:100: }
	cmpl	$65535, -8(%rbp)	#, __priority
	jne	.L122	#,
# /usr/include/c++/11/iostream:74:   static ios_base::Init __ioinit;
	leaq	_ZStL8__ioinit(%rip), %rax	#, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZNSt8ios_base4InitC1Ev@PLT	#
	leaq	__dso_handle(%rip), %rax	#, tmp83
	movq	%rax, %rdx	# tmp83,
	leaq	_ZStL8__ioinit(%rip), %rax	#, tmp84
	movq	%rax, %rsi	# tmp84,
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax	#, tmp86
	movq	%rax, %rdi	# tmp85,
	call	__cxa_atexit@PLT	#
.L122:
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:100: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE6276:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z4funcNSt7__n486116coroutine_handleIvEE, @function
_GLOBAL__sub_I__Z4funcNSt7__n486116coroutine_handleIvEE:
.LFB6299:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# /home/shenglish/workspace/CppCoroutines/lesson-base-coroutine.cpp:100: }
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE6299:
	.size	_GLOBAL__sub_I__Z4funcNSt7__n486116coroutine_handleIvEE, .-_GLOBAL__sub_I__Z4funcNSt7__n486116coroutine_handleIvEE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z4funcNSt7__n486116coroutine_handleIvEE
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
