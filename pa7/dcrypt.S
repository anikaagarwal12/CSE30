#include "Version.h"

#ifndef MYDCRYPT_S
    .section .note.GNU-stack,"",%progbits
    .end
#else

    // version 1.1 05/08/2024
    .arch armv6
    .arm
    .fpu vfp
    .syntax unified

    #include "cipher.h"

    .text     // start of text segment

    //////////////////////////////////////////////////
    // int dcrypt(unsigned char *inbuf, unsigned char *bookbuf, int cnt)
    // decrypts inbuf using bookbuf; result in inbuf
    //////////////////////////////////////////////////
    .global dcrypt
    .type   dcrypt, %function
    .equ    FP_OFF, 28

   // r0 contains char *inbuf
   // r1 contains char *bookbuf
   // r2 contains cnt
   // r3 is ok to use
   //
   // preserved register use table
   //
   // r4
   // r5
   // r6
   // r7
   // r8
   // r9

dcrypt:
    push    {r4-r9, fp, lr}
    add     fp, sp, FP_OFF


    cmp     r2, 0               // if buffer is empty we are done
    ble     .Ldone
    mov r9, 0 //cnt var
    // your code here 
.Lfor:
	cmp r9, r2
	bge .Ldone

	// undo xoring
	ldrb r6, [r1, r9]
	ldrb r4, [r0, r9] //acopy start
	ldrb r5, [r0, r9] //bcopy start

	eor r4, r6, r4 // is this correct?
	eor r5, r6, r5
	//acopy3
	mov r6, r4 //second
	mov r7, r4 //third
	mov r8, r4 //fourth
	and r4, r4, 0x80
	lsr r4, r4, 1
	and r6, r6, 0x40
	lsl r6, r6, 1
	orr r4, r4, r6
	and r7, r7, 0x20
	lsr r7, r7, 1
	orr r4, r4, r7
	and r8, r8, 0x10
	lsl r8, r8, 1
	orr r4, r4, r8
	//bcopy3
	mov r6, r5
	mov r7, r5
	mov r8, r5
	and r5, r5, 0x8
	lsr r5, r5, 1
	and r6, r6, 0x4
	lsl r6, r6, 1
	orr r5, r5, r6
	and r7, r7, 0x2
	lsr r7, r7, 1
	orr r5, r5, r7
	and r8, r8, 0x1
	lsl r8, r8, 1
	orr r5, r5, r8
	//acopy2
	mov r6, r4
	and r4, r4, 0xc0
	lsr r4, r4, 2
	and r6, r6, 0x30
	lsl r6, r6, 2
	orr r4, r4, r6
	//bcopy2
	mov r6, r5
	and r5, r5, 0xc
	lsr r5, r5, 2
	and r6, r6, 0x3
	lsl r6, r6, 2
	orr r5, r5, r6
	//acopy
	and r4, r4, 0xf0
	lsr r4, r4, 4
	//bcopy
	and r5, r5, 0xf
	lsl r5, r5, 4
	
	orr r4, r4, r5
	strb r4, [r0, r9]
	add r9, r9, 1
	b .Lfor
.Ldone:
   // make sure to return cnt processed
	mov r0, r2
    sub     sp, fp, FP_OFF
    pop     {r4-r9, fp, lr}
    bx      lr

    .size dcrypt, (. - dcrypt)
    .section .note.GNU-stack,"",%progbits
.end
#endif
