/*
 * splitrow
 * 
 * usage:   input a row in csv format, builds table of pointers to each field
 *          returns the number of columns found in the row.
 *
 * Operation:
 *          (1) traverse the input row passed in buf. Set each element in the array
 *          of pointers (ptable) to point at the start of each column.
 *          (2) Replace the delimiter that follows each column to be a '\0' to
 *          terminate that column (making it a string)
 *          (3) Make sure you do not go past cnt entries in the ptable (where
 *          cnt is the expected number of columns in the row).
 *
 *          When called with the header row, cnt is the number of elements of the
 *          array ptable. The return value from this function (the number of columns
 *          found in the row buffer) will be used to determine the correct number of
 *          columns in every subsequent row in the input.
 *
 * argument description:
 *
 *  buf     csv format row stored in an array of characters, '\0' terminated
 *  ptable  points at array of pointers, each element points at the first character
 *          of a column in the row
 *  cnt     expected number of cols in row. If buf contains more than this
 *          number of columns then return -1
 *  delim   the field delimiter also \n delimits the last column and the row            
 *
 * return values:
 *         -1 if row is missing a newline (fgets truncated buf) or the number
 *         of columns in the row is greater than cnt
 *         otherwise return the number of columns found in the input row buf
 *
 * error messages:
 *          this function does not write any error messages
 */

#include "version.h"
#ifndef MYSPLITROW
#warning("WARNING - USING THE SOLUTION splitrow.c NOT MY CODE")
#else
#include <stdio.h>
#include "splitrow.h"

int
splitrow(char *buf, char **ptable, int cnt, char delim)
{
int count = 1;
int i = 0;
*ptable = buf;
    // replace with your code 
while (*buf != '\0') { 		
	if (*buf == '\n') { 
		i = 1;
		*buf = '\0';
		break; 
	}

	if (*buf == delim && count < cnt) { 
		*buf = '\0'; 
		ptable = ptable + 1; 
		*ptable = buf+1;
		count++;
	}
	buf++; 

	if ((count > cnt)) { 
		return -1; 	
	}
}

if (i == 0) { 
	return -1;
}
return (count +1);
 
}
#endif // do not delete this line
