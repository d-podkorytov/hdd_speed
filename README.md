# HDD Speed tests

======================================
## ABOUT

This is very old code, about 1991 I use it for testing speed of file operations.
It was my fist steps in C, dont judge me hard.

From time to time I port it to different OS.

History of development was something like
1.Linux
2.MSDOS
3.Novell NetWare v. 3.12
4.FreeBSD
5.Windows NT,Windows 2000, Win95 
6.SunOS Solaris
7.QNX
8.WinXP
 
This is sources hdd_speed for Linix.
Using on different OS probably will needs some cosmetic changes.
If I found it in old archives, I will to publish.

Also file size should be changed in source code.
In some versions size of file posible assign in argv[1] but not here.

================

## DEPENDENCIES

gcc make

## INSTALLATION

$make

## RUN TESTS AND SEE RESULTS

$./hdds.c.bin
Writing to test.hdds 
Size:2048.000 Mb Speed:233.811 Mbytes/sec      Exit 
Average speed 256.000 MBytes/sec 
 unlink  test.hdds 

$./hdd_rw.c.bin
Open file test.hdds 
Writing to test.hdds 
Size:1807.107 Mb Speed:245.383 Mbytes/sec      Writing finished 
Average write speed 256.000 MBytes/sec 
Reading from test.hdds 
Size:1961.210 Mb Speed:257.305 Mbytes/sec      Reading finished 
Average read speed 256.000 MBytes/sec 
Read 2147483647 bytes 
 unlink  test.hdds 

