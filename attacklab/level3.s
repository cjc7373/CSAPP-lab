pushq   $0x4018fa
subq	$14, %rsp
movabsq	$7018357788218898741, %rax
movq	%rax, (%rsp)
mov     %rsp, %rdi
add    $14,%rsp
ret
