#include "Version.h"
#ifndef MYINSTICKET
#warning("WARNING - USING THE SOLUTION insticket.c NOT MY CODE")
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
#include "insticket.h"
#include "subs.h"

/*
 * insertticket
 *      add a ticket (summons) to the database
 *
 *      YOU CANNOT USE CALLOC(), only malloc() is allowed.
 *
 *      if the vehicle (plate state) is not in the database then
 *      a new struct vehicle entry must be made for it in the hash table.
 *      New vehicle entries are made at the the FRONT of the collison chain
 *
 *      If the vehicle is already in the hash chain, you only need to add 
 *      a new ticket to the ticket chain for this summons.
 *
 *      Tickets are added to the ticket chain linked to the struct vehicle
 *      at the END of the ticket chain.
 *
 *      Also you must update the tot_fine and cnt_tickets in the struct vehicle
 *      to account for the new summons(ticket) just added
 *
 * Arguments
 *
 *  summ:
 *      summons id string to be added
 *      this string needs to be converted to a number to be stored in the
 *      database. This saves space and is faster to compare than a string         
 *      Conversion function is supplied. use example:
 *           unsigned long summid;
 *           if (strtosumid(summ, &summid, argv) != 0)
 *                  error handling
 *           new_ticket->summons = summid;
 *  plate:
 *      plate id string to be added
 *  state:
 *      state id string to be added
 *  code:
 *      summons code integer value used an an index into the fines table
 *      fineTab maps code number to text description & fine cost 
 *      you use this table to get the amount of the fine when calculating
 *      the tot_fine field in struct vehicle.
 *          example:
 *              struct vehicle *vhpt;
 *              vhpt->tot_fine += fineTab[code].fine;
 *
 * return
 *       0 if ok -1 for all errors
 */

int
insertticket(char *summ, char *plate, char *state, int code)
{
	uint32_t hashval; 
	unsigned long summid;
	struct vehicle *chain; // pointer to hashed bucket
	struct ticket *ticks; // double pointer for each vehicle
	hashval = hash(plate) % tabsz; 
	chain = *(htable + hashval);
	while (chain != NULL) {
		if ((strcmp(state, chain->state)==0) && (strcmp(plate, chain->plate)== 0)) { 
		struct ticket *cur = chain->head;
		if (strtosumid(summ, &summid) !=0) 
			return -1;
		while (cur->next !=NULL) {
//			int i = strtosumid(summ, &summid);
//			if (i!=0)
//				return -1; 	
			if (cur->summons == summid) { 
				fprintf(stderr,"%s: duplicate summons %lu\n", argv0, summid);
				return -1;
				// check for duplicate tickets by verifying summons.
			}  
			cur = cur->next;
		}
		if ((ticks = malloc (1 * sizeof(*ticks)))!=NULL) {
			ticks->summons = summid;
			ticks->code = code;
			ticks->next = NULL;
			cur->next = ticks;
			chain->tot_fine += fineTab[code].fine;
			chain->cnt_ticket++; 
			return 0;
		}
		//chain = chain->next;
	
		}
		chain = chain->next;
	}	
struct vehicle *newVeh;
struct vehicle *ptr = *(htable + hashval);
int i = strtosumid(summ, &summid);
if (i!=0) 
	return -1; 
if ((newVeh = malloc(1 * sizeof(struct vehicle)))!=NULL) {
	if ((newVeh->state = strdup(state)) == NULL) { 
		free(newVeh->state);
		free(newVeh);
		return -1; 
	}
	if ((newVeh->plate = strdup(plate)) ==NULL) { 
		free(newVeh->plate); 
		free(newVeh->state);
		free(newVeh);
		return -1;
	}
	if ((ticks = malloc (1 * sizeof(*ticks)))!=NULL)  {
		ticks->summons = summid;
		ticks->code = code;
		ticks->next = NULL;
				
		newVeh->head = ticks;
		*(htable + hashval) = newVeh;
		newVeh->next = ptr;
		newVeh->tot_fine = fineTab[code].fine;
		newVeh->cnt_ticket = 1;
	}
}

    return 0;
}

#endif
