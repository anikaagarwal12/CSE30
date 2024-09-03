#include "Version.h"

#ifndef MYECRYPT_S
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
    // int ecrypt(unsigned char *inbuf, unsigned char *bookbuf, int cnt)
    // encrypts  inbuf with bookbuf; updating inbuf
    //////////////////////////////////////////////////
    .global ecrypt
    .type   ecrypt, %function
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

ecrypt:
    push    {r4-r9, fp, lr}
    add     fp, sp, FP_OFF

    cmp     r2, 0               // if buffer is empty we are done
    ble     .Ldone
    mov r9, 0 // initializing i = 0
    // your code here
.Lfor: 
	cmp r9, r2
	bge .Ldone
	
	ldrb r4, [r0, r9] // copying inbuf into a
	ldrb r5, [r0, r9] // copying inbuf into b
	//acopy
	and r4, r4, 0xf // right side
	lsl r4, r4, 4 // left shift
	//bcopy
	and r5, r5, 0xf0 //left side
	lsr r5, r5, 4 // right shift
	//acopy2
	mov r6, r4 // copying left side
	and r4, r4, 0xc0 
	lsr r4, r4, 2
	and r6, r6, 0x30
	lsl r6, r6, 2
	orr r4, r4, r6
	//bcopy2
	mov r7, r5
	and r5, r5, 0xc
	lsr r5, r5, 2
	and r7, r7, 0x3
	lsl r7, r7, 2
	orr r5, r5, r7
	//acopy3
	mov r6, r4
	mov r7, r4
	mov r8, r4
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
	
	add r4, r4, r5 // do i need to use []
	ldrsb r6, [r1, r9]
	eor r4, r4, r6
	strb r4, [r0, r9]
	add r9, r9, 1
	//add r4, r4, 1 // incrementing bytes
	//add r5, r5, 1 // incrementing bytes 	

	b .Lfor
.Ldone:
	mov r0, r2 // is this how i return?

   // make sure to return cnt processed

    sub     sp, fp, FP_OFF
    pop     {r4-r9, fp, lr}
    bx      lr

    .size ecrypt, (. - ecrypt)
    .section .note.GNU-stack,"",%progbits
.end
#endif
