// #include <stdio.h>

// int main() {
//     printf("Hello\n");
//     return 0;
// }

// $ strace ./a.out
// execve("./a.out", ["./a.out"], 0x7fff5795ce10 /* 78 vars */) = 0
// arch_prctl(0x3001 /* ARCH_??? */, 0x7ffc4c2aedb0) = -1 EINVAL (Invalid
// argument) brk(NULL)                               = 0x15ab000 brk(0x15abd00)
// = 0x15abd00 arch_prctl(ARCH_SET_FS, 0x15ab380)      = 0
// set_tid_address(0x15ab650)              = 58182
// set_robust_list(0x15ab660, 24)          = 0
// rseq(0x15abca0, 0x20, 0, 0x53053053)    = 0
// prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024,
// rlim_max=RLIM64_INFINITY}) = 0 readlink("/proc/self/exe",
// "/home/cjc/Github/CSAPP-lab/a.out", 4096) = 32
// getrandom("\x76\x5d\xb2\x54\x20\xc7\x8a\x3b", 8, GRND_NONBLOCK) = 8
// brk(NULL)                               = 0x15abd00
// brk(0x15ccd00)                          = 0x15ccd00
// brk(0x15cd000)                          = 0x15cd000
// mprotect(0x4a3000, 16384, PROT_READ)    = 0
// newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x3), ...},
// AT_EMPTY_PATH) = 0 write(1, "Hello\n", 6Hello )                  = 6
// exit_group(0)                           = ?
// +++ exited with 0 +++

#include <unistd.h>

int main() {
    write(1, "Hello\n", 6);
    return 0;
}

// $ strace ./a.out
// execve("./a.out", ["./a.out"], 0x7ffc82435850 /* 78 vars */) = 0
// arch_prctl(0x3001 /* ARCH_??? */, 0x7ffee0abad10) = -1 EINVAL (Invalid
// argument) brk(NULL)                               = 0xa90000 brk(0xa90d00) =
// 0xa90d00 arch_prctl(ARCH_SET_FS, 0xa90380)       = 0
// set_tid_address(0xa90650)               = 58278
// set_robust_list(0xa90660, 24)           = 0
// rseq(0xa90ca0, 0x20, 0, 0x53053053)     = 0
// prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024,
// rlim_max=RLIM64_INFINITY}) = 0 readlink("/proc/self/exe",
// "/home/cjc/Github/CSAPP-lab/a.out", 4096) = 32
// getrandom("\xb4\xbf\x57\x97\x2d\x54\x96\x82", 8, GRND_NONBLOCK) = 8
// brk(NULL)                               = 0xa90d00
// brk(0xab1d00)                           = 0xab1d00
// brk(0xab2000)                           = 0xab2000
// mprotect(0x4a2000, 16384, PROT_READ)    = 0
// write(1, "Hello\n", 6Hello
// )                  = 6
// exit_group(0)                           = ?
// +++ exited with 0 +++
