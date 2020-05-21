# Test_for_GL
General information.
To complete the task, the following equipment was used - raspberry Pi 3 A + with the latest version of raspbian booster OS. Gcc compiler (on command line)
example - gcc -o extract extract.c






Task 1: The Stairway
One Giant wants to climb the Magical Tower stairway. He knows he could step over each K-th stair. An Old Troll is asking the Giant how many stairs will he step in total if there are N stairs in the stairway. Write a program, that will help Giant answer the Old Troll.
The program accepts N and K as *command-line arguments* (not stdin) and returns the total number of stairs the Giant steps to stdout.

Example:
[giant@laptop ~]$	./steps 100 0
100
[giant@laptop ~]$	./steps 10 2
4
[giant@laptop ~]$	./steps 11 2
4
[giant@laptop ~]$	./steps 12 2
4
[giant@laptop ~]$	./steps 13 2
5
[giant@laptop ~]$	./steps 986 16
58


!!!In this task, a check is performed on the number of input parameters, as well as on the correspondence of the input parameters to integers.!!!

Task 2: The Bridge
The Greedy King wants to collect tribute for each span of the Magical Bridge the merchants pass. He wants to install special wired sensors on each of the spans, with communication cables leading directly to the Treasury Department base station located at one bank of the river. He asked the Mighty Wizard to calculate the total length of the cables. But Mighty Wizard knows that there will be no enough cables in the whole Kingdom and it's better to use wireless solutions. Help him convince the Greedy King.
Write a program that will help the Mighty Wizard to calculate the total length of the cables required. A program accepts two *command-line arguments*, N - the total number of spans the Magical Bridge has, and the second argument D - the distance between the spans (all spans are distributed evenly and the distance from the bank of the river to the first span is also D), and returns the total length of the cables.

Example:
[king@govpc ~]$	./cables 18 6
1026
[king@govpc ~]$	./cables 100 3
15150

Task 4: Extractor
Below  is  described  a  simple  TAR-like  FS  image  format,  especially  useful  for  highly-constrained
embedded devices. Each FS image is a file, containing other files and directories inside without any
compression.
The task is to create FS image extractor, that will unpack an .img file to some directory.
Example:
Here we extract 'image1.img' FS image to 'somedir' directory
[usr@pc ~]$ ./extract image1.img somedir
[usr@pc ~]$ ls -hal somedir
total 84K
drwxr-xr-x 2 usr users 4.0K may 14 15:02 .
drwxr-xr-x 6 usr users 4.0K may 14 16:00 ..
-rw-r--r-- 1 usr users  71K may 14 14:58 picture-registrar.jpg
-rw-r--r-- 1 usr users  209 may 14 14:58 zen.txt





