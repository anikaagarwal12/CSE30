#include "Version.h"

#if defined(MYMAIN_S)
#warning("using my main.S")
#elif !defined(MYMAIN_C)
#warning("using solution main")
#else
#warning("using my Cmain.c")

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "rdbuf.h"
#include "setup.h"
#include "cipher.h"

// version 1.1 05/08/2024

/*
 * cipher program
 * usage:  cipher [-d|-s) -b bookfile
 * cipher reads the data to be processed from standard input, either
 * encrypts (-e) or decrypts (-d) the data, and then writes the result
 * to standard output.
 */

int
main(int argc, char **argv)
{
    /*
     * local vars on stack these are given to help you write main.S later
     * it is suggested that you not change the order of the vars.
     */
    FILE *fpbook;                   // File * to bookfile
    unsigned char inbuf[BUFSZ];     // input buffer - same size as bookbuf
    unsigned char bookbuf[BUFSZ];   // output buffer - same size as inbuf
    int (*func)();                  // function pointer to ecrypt or dcrypt
    char *argv0 = *argv;            // saved argv[0] for fprintf()
    // end of required stack variables

    /*
     * call setup which does:
     * (1) parse the command line arguments, (2) func is set to point at either
     * ecrypt or dcrypt and open the book file
     */
    if (setup(argc, argv, &func, &fpbook) == RETRN_FAIL ) {
	fpbook = NULL;
	func = NULL;
        return EXIT_FAILURE;
	}
	
	int i = 1;
	int count;
	while (i) {
		count = rdbuf(stdin, fpbook, BUFSZ, inbuf, bookbuf); 	
		if (count == RETRN_FAIL) {
			fprintf(stderr, "%s: read failed\n", argv0);
			(void)fclose(fpbook);
			return EXIT_FAILURE;	
		} else if (count == 0)
			i = 0;
			return EXIT_FAILURE; //adding this after submission

	if (func(inbuf, bookbuf, count) != count) {
		(void)fclose(fpbook);
		return EXIT_FAILURE;
	}
	
	if ((int)fwrite(inbuf, 1, count, stdout) != count) { 
		fprintf(stderr, "%s: write failed\n", argv0);
		(void)fclose(fpbook);
		return EXIT_FAILURE;
	}
	} 	
		
	(void)fclose(fpbook);
    	return EXIT_SUCCESS;
}
#endif
