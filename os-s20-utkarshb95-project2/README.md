# os-s20: Project 2: Process Management and Trap Handling

## Building the image:
```
$ make clean
$ make [SOL=1]
```
These two commands will do all the steps required to build an image file. The make clean step will delete all the
compiled binaries from past runs. After the image has been created, use one of the following execution modes:

## Executing WITH QEMU VGA Monitor
```
$ make qemu
```
Use Ctrl-a x to exit from qemu.

## Executing WITHOUT QEMU VGA Monitor
```
$ make qemu-nox
```

## Executing with GDB and QEMU VGA Monitor
```
$ make qemu-gdb
```

## Running User Processes
A new monitor task startuser, once run, it
starts the idle process implemented in user/idle/idle.c, which in turn spawns three user processes defined in
user/pingpong/ping.c, user/pingpong/pong.c, and user/pingpong/ding.c, at the user level, with full
memory isolation and protection.
A sample output for startuser is shown below.
```
$> help
help - Display this list of commands
kerninfo - Display information about the kernel
startuser - Start the user idle process
$> startuser
[D] kern/lib/monitor.c:45: process idle 1 is created.
Start user-space ...
idle
ping in process 4.
pong in process 5.
ding in process 6.
ping started.
ping: the value at address e0000000: 0
ping: writing the value 100 to the address e0000000
pong started.
pong: the value at address e0000000: 0
pong: writing the value 200 to the address e0000000
ding started.
ding: the value at address e0000000: 0
ding: writing the value 300 to the address e0000000
ping: the new value at address e0000000: 100
pong: the new value at address e0000000: 200
ding: the new value at address e0000000: 300
```
The three processes ping, pong and ding start with PID’s 4, 5 and 6. Each process writes a different value at the same
virtual memory address e0000000 and reads back from the same location. We see that each process reads back its own
value, showing that the page-based virtual memory implemented in project 1 is working and indeed provides an illusion
that each process owns the entire 4GB of the memory.
