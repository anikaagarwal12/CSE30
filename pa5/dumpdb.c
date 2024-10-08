#include "Version.h"
#ifndef MYDUMPDB
#warning("WARNING - USING THE SOLUTION dumpdb.c NOT MY CODE")
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
#include "subs.h"
#include "dumpdb.h"

/*
 * dumpindex
 *
 * dump the linked list chain on a single hash chain
 * print each vehicle on the chain using printvehicle()
 *
 * Arguments:
 *
 * index:
 *          hash table chain index number
 * cnt:
 *          a pointer to an output variable that contains the count
 *          of the total number of tickets on the hash chain
 *          set *cnt = 0UL if no tickets are found
 *
 * return:
 *          number of vehicles found on the hash chain
 *          total number of tickets in chain returned in output variable *cnt
 */
unsigned long
dumpchain(uint32_t index, unsigned long *cnt)
{
	unsigned long vehicleCount = 0;
	struct vehicle *ptr = *(htable + index);
	printf("Chain %u: \n", index);
	while (ptr!= NULL) {
		struct ticket *curr_ticket = ptr->head;
		while (curr_ticket != NULL) { 
			*cnt = *cnt + 1;
			curr_ticket = curr_ticket->next;
		}
		printvehicle(ptr);
		ptr = ptr->next;
		vehicleCount++;
	}
	return vehicleCount;
    //use printvehicle() to print each vehicle on the hash chain

}

/*
 * dumpdb
 *
 * dump the entire database one hash chain at a time from chain 0
 * in the hash table to the last entry in the table
 *
 * call dumpchain() to print each hash chain.
 *
 * Prints the total number of vehicles and tickets in the database
 *
 */
void
dumpdb(void)
{
    unsigned long vcnt = 0UL; // total vehicle count
    unsigned long tcnt = 0UL; // total ticket count

    
for (unsigned long i = 0; i <TABSZ; i++) {
    struct vehicle *ptr = *(htable + i); 
    if (ptr == NULL) { 
	continue; 
	} 
    vcnt += dumpchain(i,&tcnt);
} 
    // print the summaries
    printf("Total vehicles in database: %lu\n", vcnt);
    printf("Total tickets in database: %lu\n", tcnt);
    return;


}
#endif
