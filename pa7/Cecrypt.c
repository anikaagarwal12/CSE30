#include "Version.h"

#if defined(MYECRYPT_S)
#warning("using my ecrypt.S")
#elif !defined(MYECRYPT_C)
#warning("using solution ecrypt")
#else
#warning("using my Cecrypt.c")

// version 1.1 05/08/2024
#include <stdio.h>
#include "cipher.h"

// encrypts  inbuf with bookbuf; updating inbuf
int
ecrypt(unsigned char *inbuf, unsigned char *bookbuf, int cnt)
{
	if (cnt <= 0)
		return 0;
for (int i = 0; i<cnt; i++) {
	unsigned char acopy = *inbuf;
	unsigned char bcopy = *inbuf;
	unsigned char final; // is this going to include nulls?
	// your code here
	// ABCDEFGH
	acopy = (*inbuf & 0xf) << 4; // EFGH0000
	bcopy = (*inbuf & 0xf0) >>4; //0000ABCD
	acopy = ((acopy & 0xc0) >> 2) | ((acopy & 0x30) << 2); //00EF | GH00 --> GHEF 
	bcopy = ((bcopy & 0xc) >> 2) | ((bcopy & 0x3) << 2); //00AB | CD00 --> CDAB
	acopy = ((acopy & 0x80) >> 1) | ((acopy & 0x40) << 1) | ((acopy & 0x20) >>1) | ((acopy & 0x10) << 1); // 0G00 | H000 | 0E | F0 -->HGFE  
	bcopy = ((bcopy & 0x8) >> 1) | ((bcopy & 0x4) << 1) | ((bcopy & 0x2) >>1) | ((bcopy & 0x1) <<1); // DCBA
	final = acopy | bcopy;

	// xoring
	*inbuf = final ^ *bookbuf;
	inbuf++;
	bookbuf++;
}
	return cnt;
}
#endif
