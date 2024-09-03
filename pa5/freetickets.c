#include "Version.h"
#ifndef MYFREETICKETS
#warning("WARNING - USING THE SOLUTION freetickets.c NOT MY CODE")
#else
#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"
#include "freetickets.h"

/*
 * freetickets
 *      tears down the database freeing all allocated memory
 *      count the number of tickets and vehicles freed in
 *      the database 
 *      prints the counts before returning
 */
void
freetickets(void)
{
	unsigned long tcnt = 0UL;
  	unsigned long vcnt = 0UL;
	for (unsigned long i = 0; i<tabsz; i++) { 
		struct vehicle *ptr = *(htable + i); 
		while (ptr != NULL) {
			struct vehicle *cptr = ptr->next;
			struct ticket *curr_ticket = ptr->head;
			while (curr_ticket != NULL) { 
				struct ticket *ccurr_ticket = curr_ticket->next;
				tcnt++;
				free(curr_ticket);
				curr_ticket = ccurr_ticket; 	
			}
			vcnt++;
			free(ptr->plate);
			ptr->plate = NULL;
			free(ptr->state);
			ptr->state = NULL; 
			free(ptr);
			ptr = NULL;
			ptr = cptr;
		}
		*(htable + i) = NULL;
	// set htable to NULL
	}
    printf("Total vehicles freed: %lu\n", vcnt);
    printf("Total tickets freed: %lu\n", tcnt);
    return;
}
#endif
