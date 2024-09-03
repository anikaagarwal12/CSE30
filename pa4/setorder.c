/*
 * setorder
 *
 * usage:   argv array passed to main(): command name + arg list
 *          each argument is a column number of a column that will be output
 *          (1) convert each argument to an integer using strtol()
 *          and check the conversion as described in the PA writeup. If 
 *          there is an error, print an error message and return -1
 *          (2) Each converted value is checked to be in the range 1 to maxcol
 *          print an error message and return -1 if not
 *          (3) The converted value is adjusted to be an array offset value
 *          and is stored in the array coltab in the same order the args are
 *          listed in argv.
 *          (4) If the number of args is greater than maxcol print an error
 *          message and return -1
 *          (5) Otherwise all ok, return the number of entries in indxtab
 *
 * arguments:
 * argv     argv array of pointers to strings as passed to main()
 * coltab   points at an int array. Each entry specifies an input row
 *          column to be output. The order the columns appear in coltab
 *          is the order of the columns in the output row
 * tabsz    the size (number of elements) in the array coltab
 * maxcol   number of columns in a row (no arg can be greater than this value)
 *
 * Return values:
 *           -1 if if any error is detected
 *           otherwise return the number of entries stored in indxtab
 *
 * error messages:
 *	     this function writes e`rror messages to stderr
 */

#include "version.h"
#ifndef MYSETORDER
#warning("WARNING - USING THE SOLUTION setorder.c NOT MY CODE")
#else
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "setorder.h"
//#define EXIT_FAILURE 
int number; 
int setorder(char **argv, int *coltab, int tabsz, int maxcol)
{
// need some condition that terminates collecting data from stdin.
// length of argv
int *coltab_curr = coltab;
char **ptrargv = argv;
ptrargv = ptrargv + 1; // incrementing the pointer by 1 at the startto point at the first number directly 
int count = 0;
while (*ptrargv != NULL && count < tabsz) { 
	errno = 0;
	long val;
	char *endptr;	
		val = (int) strtol (*ptrargv, &endptr, 10);
		if ((errno != 0) || (*endptr != '\0') || (val < 1)|| (val > maxcol)) {
			fprintf(stderr, "%s: improper argument: %s\n", *argv, *ptrargv);
			return -1; 
		} 
		if ((val >= 1) && (val <= maxcol)) { 
			*coltab_curr = val-1;
			coltab_curr++; 
		} 
		count++;
		ptrargv++;	 
	
	if (count >= tabsz-1) { 
		fprintf(stderr, "%s: too many arguments %d max\n", *argv, tabsz);
		fprintf(stderr, "usage: %s col [col ...]\n", *argv);
		return -1;
	}
}	

if (coltab_curr == coltab) { 
	fprintf(stderr, "%s: at least one column must be specified\n", *argv);
	fprintf(stderr, "usage: %s col [col ...]\n", *argv);
	return -1;
	
}
return count; 


/*
 * the error messages for use in this file
 * fprintf(stderr, "%s: improper argument: %s\n", *argv, *ptrargv);
 * fprintf(stderr, "%s: at least one column must be specified\n", *argv);
 * fprintf(stderr, "%s: too many arguments %d max\n", *argv, tabsz);
 * fprintf(stderr, "usage: %s col [col ...]\n", *argv);
 */

}
#endif // do not delete this line
