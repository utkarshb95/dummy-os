# os-s20: Project 1: Memory Management

## Building and running the image
```
$ make clean
$ make TEST=1
```
Use this command to run unit tests to verify the working status of your code.

## ALTERNATIVE: Building and running the image with provided solutions
To use already provided compiled solutions. Use the SOL flag as shown below for this.
```
$ make clean
$ make TEST=1 SOL=1
```

### Normal Execution
## Building the image
```
$ make clean
$ make
```

## ALTERNATIVE: Building the image with provided solutions
```
$ make clean
$ make SOL=1
```
These two commands will do all the steps required to build an image file. The make clean step will delete all the
compiled binaries from past runs. After the image has been created, use one of the following execution modes:

## Executing WITH QEMU VGA Monitor
```
$ make qemu
```
You can use Ctrl-a x to exit from the qemu.

## Executing WITHOUT QEMU VGA Monitor
```
$ make qemu-nox
```
## Executing with GDB and QEMU VGA Monitor
```
$ make qemu-gdb
```
## Executing with GDB without QEMU VGA Monitor
```
$ make qemu-nox-gdb
```
