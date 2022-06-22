subq	$14, %rsp
movabsq	$7018357788218898741, %rax
movq	%rax, (%rsp)
movw	$0, 8(%rsp)
mov     %rsp, %rdi
pushq   $0x4018fa
ret
