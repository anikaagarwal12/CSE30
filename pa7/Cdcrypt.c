#include "Version.h"

#if defined(MYDCRYPT_S)
#warning("using my dcrypt.S")
#elif !defined(MYDCRYPT_C)
#warning("using solution decrypt")
#else
#warning("using my Cdcrypt.c")

// version 1.1 05/08/2024
#include <stdio.h>
#include "cipher.h"

// decrypts inbuf with bookbuf; updating inbuf
int
dcrypt(unsigned char *inbuf, unsigned char *bookbuf, int cnt)
{
    if (cnt <= 0)
        return 0;
// your code here
for (int i = 0; i< cnt; i++){ 
	// undo xoring
	*inbuf = *inbuf ^ *bookbuf; 

	// reversing the bits
	unsigned char acopy = *inbuf; 
	unsigned char bcopy = *inbuf;
//	unsigned char final; 

	acopy = ((acopy & 0x80) >> 1) | ((acopy & 0x40) << 1) | ((acopy & 0x20) >> 1) | ((acopy & 0x10) << 1); 
	bcopy = ((bcopy & 0x8) >> 1) | ((bcopy & 0x4) << 1) | ((bcopy & 0x2) >> 1) | ((bcopy & 0x1) << 1); 
	acopy = ((acopy & 0xc0) >> 2) | ((acopy & 0x30) << 2); 
	bcopy = ((bcopy & 0xc) >> 2) | ((bcopy & 0x3) << 2); 
	acopy = (acopy & 0xf0) >>4; 
	bcopy = (bcopy & 0xf) << 4;
	
	*inbuf = acopy | bcopy;
	inbuf++;
	bookbuf++;
}
    return cnt;
}
#endif
