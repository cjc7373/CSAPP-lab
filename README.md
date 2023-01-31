# CSAPP
This repo contains my own tracks during my studying of CSAPP.

## Resources
Textbook: Computer Systems: A Programmer's Perspective, 3/E (CS:APP3e)

Course home page: http://www.cs.cmu.edu/~213/schedule.html

Lab meterials are from [CSAPP student website](http://csapp.cs.cmu.edu/3e/labs.html).

Lectures are either [2015 fall (in CMU site)](https://scs.hosted.panopto.com/Panopto/Pages/Sessions/List.aspx#folderID=%22b96d90ae-9871-4fae-91e2-b1627b43e25e%22&sortColumn=1&sortAscending=true) or [2017 fall (in Youtube)](http://www.cs.cmu.edu/afs/cs/academic/class/15213-f17/www/schedule.html).

Homework solutions: https://dreamanddead.github.io/CSAPP-3e-Solutions/

## Course schedule
| Chapter | Start Time | Finish Time | Book Finished | Video Finished |
| -------- | -------- | -------------- | ----------- | -------------- |
| A Tour of Computer Systems | Long time ago | Long time ago | N/A | N/A |
| Representing and Manipulating Infomation | Long time ago | Long time ago | Y | Y |
| Machine-Level Representation of Programs | Long time ago | Not yet | N | N |
| Processor Architecture | - | - | - | - |

Lectures: (CMU site)
- [x] 2022-02-22 - Lecture 05: Machine-Level Programming I: Basics
- [x] 2022-02-23 - Lecture 06: Machine-Level Programming II: Control
- [x] 2022-02-24 - Recitation 4: Bomb Lab
- [x] 2022-03-07 - Lecture 07: Machine-Level Programming III: Procedures
- [x] 2022-06-17 - Lecture 08: Machine-Level Programming IV: Data
- [x] 2022-06-19 - Recitation 5: Attack Lab and Stacks
- [x] 2022-06-25 - Lecture 09: Machine-Level Programming V: Advanced Topics
- [ ] 2022-06-29 - Lecture 10: Program Optimization
    - need to review.. I haven't quite understood this chapter, especially instruction parallelism.
- [x] 2022-07-01 - Recitation 6: C Review
    - skimmed
- [x] 2022-07-22 Lecture 11: The Memory Hierarchy
    - easier than previous chapters, maybe I've had some foundations..
- [x] 2022-08-03 Lecture 12: Cache Memories
- [x] 2022-08-16 Recitation 7: Cache Lab and Blocking
- [x] 2022-12-13 Lecture 13: Linking
- [x] 2023-01-02 Lecture 14: ECF: Exceptions & Processes
- Not Playable, Recitation 8: Exam Review
- [x] 2023-01-20 Lecture 15: Exceptional Control Flow: Signals and Nonlocal Jumps
- [x] 2023-01-24 Lecture 16: System Level I/O
- [] Recitation 9: Shell Lab, Processes, and Signals, and I/O

## Lab schedule
| Name | Start Time | Finish Time |
| ---- | ---------- | ----------- |
| Data Lab | 2021-12-15 | Not yet |
| Bomb Lab | 2022-02-25 | 2022-06-19 |
| Attack Lab | 2022-06-19 | 2022-06-23 |
| Cache Lab | 2022-06-22 | 2022-08-16 (Part A) |

- Bomb lab phase 6 skipped
- Attack lab phase 5 skipped

## Pitfalls and notes
- All assembly files are generated with `gcc -Og -S file.c -o file.o`
- In `test/procedure_call_perf_test/profile.py`, I reproduced the example shown in the Program Optimization class.

## Lab Write-up
Lab readme and writeups are very useful!
### Data lab
See the comments in `datalab/bits.c`.
Run `./driver.pl` to run the test suite.

- in some functions, dlc requires all the variables be declared in the beginning of the function, or `parse error` will be raised.
- btest.c has a warning in gcc :)

### Bomb lab
Should learn some GDB...
e.g. set breakpoints, single-step through assembly code, inspect register and memory states.

Bomb lab is so much fun!

Make use of the GDB TUI!

- phase_6: we need to understand the data structure through the assembly code..
    - read six numbers
    - every number should <= 6
    - every number should not equal
    - the first number should be 6?
    - what the hell is 0x6032d0 nodeX?

### Attack lab
touch1 is in 0x4017c0

getbuf:
```asm
=> 0x00000000004017a8 <+0>:     sub    $0x28,%rsp
   0x00000000004017ac <+4>:     mov    %rsp,%rdi
   0x00000000004017af <+7>:     call   0x401a40 <Gets>
   0x00000000004017b4 <+12>:    mov    $0x1,%eax
   0x00000000004017b9 <+17>:    add    $0x28,%rsp
   0x00000000004017bd <+21>:    ret    
```
stack frame size is 0x28 (40B)

Why %rbp is frame pointer? https://stackoverflow.com/questions/41912684/what-is-the-purpose-of-the-rbp-register-in-x86-64-assembler

In level2, we cannot put instructions below 0x5561dca0 (%rsp at the beginning of `getbuf`),
because these areas will be pushed some data like touch2 address and cookie.

Level3 is similar to level2, in spite of passing a pointer than an integer.
Note we need to set the end of the string '\0'.

I got a pitfall that if I added %rsp in the end, the data below %rsp may be lost..

It is useful to draw stack diagrams.

## Cache lab
Part A:

A cache simulator built from scratch! That's quite a bit work.
I should write not only a command line parser, also data structures like doubly linked list (used in LRU cache).

It seems that we don't actually implement write action, so I'll skip it.

> memory accesses are aligned properly, such that a single
memory access never crosses block boundaries. By making this assumption, you can ignore the
request sizes in the valgrind traces

The write-up says the simulator should work for arbitrary s, E, and b. But since address is 64 bits, I'm not considering the case if s, E, or b exceeds 64. 

---

Part B:

## Shell lab
> Typing ctrl-c (ctrl-z) should cause a SIGINT (SIGTSTP) signal to be sent to the current foreground job, as well as any descendents of that job (e.g., any child processes that it forked).

Who gets the signal if I press Ctrl+C, the shell or the foreground progress?
