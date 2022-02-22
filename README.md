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

## Lab schedule
| Name | Start Time | Finish Time |
| ---- | ---------- | ----------- |
| Data Lab | 2021-12-15 | Not yet |
| Bomb Lab | Not yet | Not yet |

## Pitfalls
- Data lab
    - in some functions, dlc requires all the variables be declared in the beginning of the function, or `parse error` will be raised.
    - btest.c has a warning in gcc :)

## Write-up
### Data lab
See the comments in `datalab/bits.c`.

### Bomb lab
Should learn some GDB...
e.g. set breakpoints, single-step through assembly code, inspect register and memory states.
