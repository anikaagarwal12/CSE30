#include "Version.h"
#ifndef MYDELTICKET
#warning("WARNING - USING THE SOLUTION delticket.c NOT MY CODE")
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
#include "delticket.h"
#include "subs.h"

/*
 * delticket
 *      remove ticket (summons) from the database
 *      look up the summons for a vehicle and pay it (remove the ticket) 
 *
 *      Find the vehicle by the state and plate. if not found return -1
 *
 *      convert the summ string to a unsigned int using using strtosumid.
 *
 *      After you have the vehicle, find the summons on the ticket chain
 *      that matches the converted summons string 
 *           
 *      If found, delete it from the ticket chain. If the vehicle
 *      no longer has any tickets, then remove the vehicle from the hash chain
 *      Otherwise you must update the tot_fine and cnt_tickets fields in
 *      the struct vehicle so the are accurate after removing the summons
 *      Make sure to free() all space that was malloc()'d 
 *
 * Arguments:
 *  plate   plate id string to be found
 *  state   state id string to be found
 *  summ    summon id string to be found
 *
 * returns 0 if ok -1 if not found or error
 */

int
delticket(char *plate, char *state, char *summ)
{
	unsigned long summid;
	if (strtosumid(summ, &summid) != 0) 
		return -1;
	uint32_t hashval = hash(plate) % tabsz;
	struct vehicle *ptr = *(htable + hashval);
	struct vehicle *cptr = ptr;
	while (ptr != NULL) { 
		if (strcmp(plate, ptr->plate) == 0 && strcmp(state, ptr->state) == 0) { 
			break;
		}
		cptr = ptr;
		ptr = ptr->next;
	}
	if (ptr == NULL) 
		return -1; 
	struct ticket *cur = ptr->head;
	struct ticket *prev = ptr->head;
	// vehicle matches
	while (cur != NULL) {
		if (cur->summons == summid) 
			break;
		prev = cur;
		cur = cur->next;
	} 
	if (cur == NULL) 
		return -1;
	ptr->tot_fine -= fineTab[cur->code].fine;
	ptr->cnt_ticket--;
	if (cur == ptr->head) {
		// delete the ticket
		ptr->head = cur->next;
	} else { 
		prev->next = cur->next;
	}
	free(cur);
	if (ptr->head == NULL && cptr == ptr) {
		*(htable + hashval) = ptr->next;	
	}
	if (ptr->head == NULL) {
		cptr->next = ptr->next;
		free(ptr->state);
		ptr->state = NULL;
		free(ptr->plate);
		ptr->plate = NULL;
		free(ptr);	
		//if (cptr == *(htable + hashval))
		//	cptr = cptr->next; 
	}
 	//if (cptr == NULL)  
	//	*(htable + hashval) = NULL;
	return 0;

}
#endif
