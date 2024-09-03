#include "Version.h"

#ifndef MYRDBUF_S
    .section .note.GNU-stack,"",%progbits
    .end
#else

    // version 1.1 05/08/2024
    .arch   armv6
    .arm
    .fpu    vfp
    .syntax unified

    // global constants
    #include "cipher.h"

    .extern fread
    .text

    //////////////////////////////////////////////////////
    // int rdbuf(FILE *in, FILE *book, int cnt, unsigned char *inbuf,
    //          unsigned char *bookbuf)
    // OBSERVE this has 5 arguments!
    //
    // This function reads up to cnt bytes into inbuf from FILE *in such
    // as bytes = fread(). bytes is the actual number of bytes read.
    // Then read the same number of bytes from the FILE *book into the
    // buffer bookbuf.
    // 
    //  Arguments
    //  in       pointer of type FILE where the input data is read from
    //  fobook   pointer of type FILE where the bookfile is read from
    //  cnt      max number of bytes to read into inbuf
    //  inbuf    buffer where the input data is read into
    //  bookbuf  buffer where the bookfile data is read into
    // 
    //  Returns
    //  0        when EOF is reached on the in
    //  bytes    number of bytes actually read
    //  RETRN_FAIL
    //           when the read on bookbuf does not return bytes
    //////////////////////////////////////////////////////

    .type   rdbuf, %function
    .global rdbuf
    // determine how many registers to save and set FP_OFF
    .equ    FP_OFF, 28


   // preserved register use table fill this in to help you
   //
   // r4 FILE *in
   // r5 FILE *fpbook
   // r6 int cnt
   // r7 unsigned char *inbuf
   // r8 unsigned char *bookbuf
   // r9 
   // arg5 can be accessed using fp_OFF + 4 
 
rdbuf:
    // set up stack frame
	push {r4-r9, fp, lr}
	add fp, sp, FP_OFF
	mov r4, r0
	mov r5, r1
	mov r6, r2
	mov r7, r3
	ldr r8, [fp, 4] // moving the fifth argument that is in the caller funcs' stack
	
     // fread() from FILE *in into inbuf
	mov r0, r7
	mov r1, 1
	mov r2, r6
	mov r3, r4 
	bl fread
	
	cmp r0, 0
	beq .Ldone // how do i return 0?????
	mov r9, r0
     // now fread() the same number of bytes from the bookfp
	mov r0, r8
	mov r1, 1
	mov r2, r9
	mov r3, r5
	bl fread

	cmp r9, r0
	bne .La
	mov r0, r9
	b .Ldone
.La:
	mov r0, RETRN_FAIL  
     // as was read from the input FILE *in into bookbuf
     // if bytes read from bookfile is not the same as read into inbuf,
     // then return RETRN_FAIL;

     // return the number of bytes read

.Ldone:
    // remove stack frame
	sub sp, fp, FP_OFF
	pop {r4-r9, fp, lr}
    bx      lr

    .size   rdbuf, (. - rdbuf)
    .section .note.GNU-stack,"",%progbits
.end
#endif
