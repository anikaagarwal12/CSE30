#include "Version.h"

#if defined(MYRDBUF_S)
#warning("using rdbuf.S")
#elif !defined(MYRDBUF_C)
#warning("using solution rdbuf")
#else
#warning("using my Crdbuf.c")

#include <stdio.h>
#include "cipher.h"
#include "rdbuf.h"

// version 1.2 05/11/2024

/*
 * rdbuf
 *
 * This function reads up to cnt bytes into inbuf from FILE *in such 
 * as bytes = fread(). bytes is the actual number of bytes read. 
 * Then read the same number of bytes from the FILE *book into the
 * buffer bookbuf.
 *
 * Arguments
 * in       pointer of type FILE where the input data is read from
 * fpbook   pointer of type FILE where the bookfile is read from
 * cnt      max number of bytes to read into inbuf
 * inbuf    buffer where the input data is read into
 * bookbuf  buffer where the bookfile data is read into
 *
 * Returns
 * 0        when EOF is reached on the in
 * bytes    number of bytes actually read
 * RETRN_FAIL
 *          when the read on bookbuf does not return bytes
 */

int
rdbuf(FILE *in, FILE *fpbook, int cnt, unsigned char *inbuf, unsigned char *bookbuf)
{
	//int bytes; /* use in a register no local variables on the stack needed */
	size_t ibytes;
	ibytes = fread(inbuf, 1,(size_t) cnt,in); // what if in doesn't contain a multiple of cnt bytes?
    /*
     * read from FILE *in into inbuf
     * argument cnt should be really a size_t but on ARM32 it is an int
     */
	if (ibytes == 0) 
		return 0; // How do i report EOF?
	size_t bbytes; 
	bbytes =fread(bookbuf, 1, ibytes, fpbook);

    /*
     * now read the same number of bytes from fpbook
     * as was read from the input FILE *in and store in bookbuf
     * if bytes read from bookfile is not the same as read into inbuf,
     * then return RETRN_FAIL;
     */
	if (ibytes != bbytes) 
		return RETRN_FAIL;
    /*
     * return the number of bytes read
     */
    return ibytes;
}
#endif
