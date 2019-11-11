# pushswap

A stack sorting program.\
42 algorithm project:

| [subject in english](https://github.com/BNNJ/pushswap/blob/master/push_swap.en.pdf) | [subject in french](https://github.com/BNNJ/pushswap/blob/master/push_swap.fr.pdf) |

## behavior

Push_swap takes a list of integers as arguments, and outputs a list of instructions to sort the integers in ascending order to the standard output.

Checker reads the instructions from the standard input and applies them to the list of integers given as arguments, and verifies that the list is sorted afterward.

## constraints

To sort the inregers list, we're allowed two stacks A and B and a limited set of instructions:
- PA: pop the top of stack A and push it onto B
- PB: pop the top of stack B and push it onto A
- SA: swap the top two elements of A
- SB: swap the top two elements of B
- SS: perform SA and SB at the same time
- RA: take the top element of A and put it at the bottom
- RB: take the top element of B and put it at the bottom
- RR: perform RA and RB at the same time
- RRA: take the bottom element of A and put it on the top
- RRB: take the bottom element of B and put it on the top
- RRR: perform RRA and RRB at the same time

## compilation

In the program's root directory:
```console
foo@bar:~$ make
```

ATTENTION: This program uses sdl2 and sdl2_ttf libraries for its graphical interface!\
Make sure to install them before compiling.\
They're most likely available through your package manager:
```console 
arch@linux:~$ yay -S sdl2 sdl2_ttf
debian@based:~$ sudo apt-get install libsdl2-2.0 libsdl2-ttf
...
```

[sdl2 installation details](https://wiki.libsdl.org/Installation)


## usage

```console 
foo@bar:~$ ./push_swap [options] \<list of integers\>
foo@bar:~$ ./checker [options] \<list of integers\>
```
The list of integers can be passed as one or multiple arguments.

Example:
```console
foo@bar:~$ ./push_swap 1 3 "2 5" 4 7 | ./checker "1 3 2" 5 "4 7" arg="5 1 4 2 3"; ./push_swap $arg | ./checker $arg
```
**Useful tip**: Generate a randomized list with a simple script:
```console
foo@bar:~$ arg=\`ruby -e "puts (X..Y).to_a.shuffle.join(' ')"\`
```
Where X and Y are the lower and upper bounds of the list.
```console
foo@bar:~$ ruby -e "puts (0..99).to_a.shuffle.join(' ')"
```
will generate a list of 100 values, from 0 to 99, in a random order.

|push_swap options|effect|
|-----------------|------|
|-g| debug mode: prints additional information|
|-v| viewer mode: enables graphical representation of the sorting process|

|checker options|effect|
|---------------|------|
|-d| detailed output|
|-v| viewer mode|

|viewer controls| effect|
|---------------|-------|
|space| start/pause|
|enter| reset|
|escape| quit|
|left/right| step backward/forward|
|up/down| faster/slower|
