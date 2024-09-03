#include "Version.h"

#ifndef MYMAIN_S
    .section .note.GNU-stack,"",%progbits
    .end
#else

    // version 1.3 05/11/2024 //
    .arch   armv6
    .arm
    .fpu    vfp
    .syntax unified

    // imports
    #include "main.h"
    #include "rdbuf.h"
    #include "setup.h"
    #include "cipher.h"
    .extern fwrite
    .extern stdin
    .extern stdout
    .extern stderr
    //
    // cipher [-d | -e] -b bookfile
    //
    // int main(int argc, char **argv)
    //

    .section .rodata
    // string literals for fprint
.Lrdmess:  .string "%s: read failed\n"
    .align 2
.Lwrmess:  .string "%s: write failed\n"

    .text
    .global main
    .type   main, %function
    //
    // complete the stack frame layout
    //
    .equ    FP_OFF,     32          // fp offset in main stack frame
	
    // use the same stack allocation order as in Cmain.c
	.equ FP_BOOK, FP_OFF + 4
	.equ INBUF, FP_BOOK + BUFSZ
	.equ BOOKBUF, INBUF + BUFSZ
	.equ FUNC_P, BOOKBUF + 4
	.equ ARGV0, FUNC_P + 4 // mov later cuz of initial value
    //
    // add your local variables here if you need them:
    //

    // NOTICE: Adjust PAD so the total size of frame (including 
    // preserved registers r4-r10, fp,lr) in bytes divides by 8 evenly
    // (8-byte aligned) keep the two buffers 8-byte aligned as well
    .equ    PAD, ARGV0 + 4             	    // Stack frame PAD
    .equ    OARG5, PAD + 4          	    // output arg5 must be at bottom
    .equ    FRMADD,OARG5-FP_OFF   // total space for locals + outarg5

    //
    // preserved register use table fill this in describing your use for each
    //
    // r4 argc
    // r5 argv
    // r6 
    // r7 count
    // r8 i
    // r9 
    // r10

main:
    push    {r4-r10, fp, lr}        // observe: odd number of regs saved
    add     fp, sp, FP_OFF
          // set frame pointer to frame base
	add sp, sp, -FRMADD
	mov r4, r0
	ldr r5, [r1]
	str r5, [fp, -ARGV0]
    // allocate space for locals and outgoing args below
	add r2, fp, -FUNC_P
	add r3, fp, -FP_BOOK
//	ldr r3, [r3]	    

    // call int setup(argc, argv, &func, &fpbook)
	bl setup
	cmp r0, RETRN_FAIL
	bne .Ldo
	mov r0, EXIT_FAILURE
	b .Ldone

.Ldo:
	mov r8, 1 
	// use for func and fpbook add r9, fp, FUNC_P
	// ldr r9, [fp, -ARGV0]
	
    // initialize the preserved registers and stack variables
    // for main loop
.Lwhile:
	ldr r0, =stdin
	ldr r0, [r0]
	ldr r1, [fp, -FP_BOOK]
	ldr r2, =BUFSZ
	add r3, fp, -INBUF 
 	add r9, fp, -BOOKBUF 
	str r9, [fp, -OARG5] //check	
	bl rdbuf
	mov r7, r0 // copying count
	cmp r0, RETRN_FAIL
	beq .Lerr
	cmp r0, 0
	beq .Ldif
	
	add r0, fp, -INBUF
	add r1, fp, -BOOKBUF
	mov r2, r7
	add r3, fp, -FUNC_P
//	ldr r3, [r3]
	blx r3
	cmp r0, r7
	bne .Lfclosefail

	add r0, fp, -INBUF
	mov r1, 1
	mov r2, r7
	ldr r3, =stdout
	ldr r3, [r3]
	ldr r6, =fwrite
	blx r6
	cmp r0, r7
	beq .Lfclosesuccess
	ldr r0, =stderr
	ldr r0, [r0]
	ldr r1, =.Lwrmess
	mov r2, r5
	bl fprintf

	ldr r0, [fp, -FP_BOOK]
	bl fclose
	mov r0,  EXIT_FAILURE
	b .Ldone
.Lfclosesuccess: 
	ldr r0, [fp, -FP_BOOK]
	bl fclose
	mov r0, EXIT_SUCCESS
	b .Ldone
.Lfclosefail:
	ldr r0, [fp, -FP_BOOK]
	bl fclose
	mov r0, EXIT_FAILURE
	b .Ldone
.Lerr:
	ldr r0, =stderr
	ldr r0, [r0]
	ldr r1, =.Lrdmess
	mov r2, r5
	bl fprintf
	
	ldr r0, [fp, -FP_BOOK]
	bl fclose
	mov r0, EXIT_FAILURE
	b .Ldone
.Ldif: 
	mov r0, EXIT_FAILURE
.Ldone:
    // set return value
    sub     sp, fp, FP_OFF
    pop     {r4-r10, fp, lr}
    bx      lr

    .size   main, (. - main)
    .section .note.GNU-stack,"",%progbits
.end
#endif
