/*
 * Filename: boot0.S
 * Description:
 *  - Sets up the machine registers (including the stack pointers) properly
 *    for execution in 16-bit mode.
 *  - Utilizes the BIOS interrupt mechanism to output messages to the screen.
 *  - Reads the second stage bootloader from the disk into appropriate location.
 *    (boot1 is put just after MBR and before the first partition, i.e. from
 *    sector 2 to sector 63.)
 *  - Correctly transfers execution to the loaded second stage bootloader.
 */

	 .set BOOT0, 0x7c00		# load address
	 .set BOOT1, 0x7e00		# start address of boot1
	 
	.globl start
start:

    /* assemble the file in 16-bit mode *

    /**
      * Clear the interrupts flag, disabling the interrupts.
      * Clear the direction flag, to configure auto-increment mode.
      */
	 cli
	 cld
	 
	.code16


/*******************************************************************************
*   YOUR 16-bit CODE
*******************************************************************************/

	xorw    %ax,%ax             # Set %ax to zero
	movw    %ax,%ds             # -> Data Segment
	movw    %ax,%es             # -> Extra Segment
	movw    %ax,%ss             # -> Stack Segment
	movw    %ax,%fs
	movw    %ax,%gs
	 
	xorl	%eax, %eax
	movb	%dl, %al
	movl	%eax, BOOT0
	movw	$BOOT0, %bp
	movw	$BOOT0, %sp 	 
	 	 
set_video_mode:
	movw	$0x03, %ax
	int	$0x10

	movw	$STARTUP_MSG, %si
	call	putstr

load_boot1:

	pushl	$0x0			# set the start
	pushl	$0x1			# LBA address
	pushw	%es			# set the buffer address
	pushw	$BOOT1			# to 0x7e00
	pushw	$62			# set the number of sectors to be read
	pushw	$0x10			# set the size of DAP
	movw	%sp, %si		# set the DAP address
	movw	$0x4200, %ax		# ah = 0x42, al = 0x00
	int	$0x13			# read sectors
	jc	load_fail		# encouter errors

	jmp	BOOT1			# jump to boot1

load_fail:
	movw	$LOAD_FAIL_MSG, %si
	call	putstr 	 

spin:
	hlt

putstr:
	pusha
	movb	$0xe, %ah
putstr.1:
	lodsb
	cmp	$0, %al
	je	putstr.2
	int	$0x10
	jmp	putstr.1
putstr.2:
	popa
	ret


/*******************************************************************************
*   DATA STRUCTURES
*******************************************************************************/

STARTUP_MSG:
    .ascii    "Start boot0 ...\r\n\0"

LOAD_FAIL_MSG:
    .ascii    "Error during loading boot1.\r\n\0"

