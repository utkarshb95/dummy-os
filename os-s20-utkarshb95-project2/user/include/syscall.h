#ifndef _USER_SYSCALL_H_
#define _USER_SYSCALL_H_

#include <lib/syscall.h>

#include <debug.h>
#include <gcc.h>
#include <proc.h>
#include <types.h>
#include <x86.h>

/** Description:
  * This file contains the user library functions for a user process to initiate a system call.
  * A system call is issued using the software interrupt number 0x30.
  * %eax register holds the system call number.
  * %ebx, %ecx, %edx, %esi, and %edi can hold the arguments required by the system call.
  */

static gcc_inline void
sys_puts(const char *s, size_t len)
{
	asm volatile("int %0" :
		     : "i" (T_SYSCALL),
		       "a" (SYS_puts),
		       "b" (s),
		       "c" (len)
		     : "cc", "memory");
}

/** TASK 1:
  * * Use inline assembly to perform a spawn system call.
  *	  This system call will load a new program from memory. Since we do not have a 
  *   filesystem yet, we will pass in an index to the elf [exec] to be loaded as a parameter
  *   to this system call.
  *   - This takes two arguments: [exec] and [quota]
  *   - After the syscall is handled, it returns two values through registers: 
  * 	  [error number] => either E_SUCC on success or E_INVAL_PID if the new program cannot be loaded.
  *     [return value] => the new child process id of E_SUCC or NUM_IDS (if failure/E_INVAL_PID)
  *   - Return the pid if syscall is successful else return -1.
  */
static gcc_inline pid_t
sys_spawn(uintptr_t exec, unsigned int quota)
{
	// TODO
  unsigned int a, b;

  asm volatile(
    "int %2" 
    :
    "=a" (a),
    "=b" (b)
    :
    "i" (T_SYSCALL),
    "a" (SYS_spawn),
    "b" (exec),
    "c" (quota)
    :
    "cc",
    "memory"
  );

  if(a == NUM_IDS)
    return -1;

  return b;
}

/** TASK 2:
  * * Use inline assembly to perform a yield system call. 
  *	  This system call will voluntarily yield the CPU to the next process in the ready queue.
  *   - This doesn't take any arguments and doesn't return anything.
  */
static gcc_inline void
sys_yield(void)
{
	// TODO
  asm volatile(
    "int %0"
    :
    :
    "i" (T_SYSCALL),
    "a" (SYS_yield)
    :
    "cc",
    "memory"
  );
}

#endif
