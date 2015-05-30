#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_automatons.h"
#include "linked_lists.h"



/*pointer to the last item of the linked list*/
events * ll_getlastItem(events *events_head){

	events * current = events_head;

	while(current->next != NULL)
		current = current->next;

	return current;
}

events * ll_getNextItem(events *events_head){

	if(events_head->next != NULL)
		return events_head->next;
	else
		return NULL; 
}

/*
	If the states exists it return a pointer to is name, 
	otherwise it returns NULL
*/

char * stateExists(char * state, automaton *automaton_ptr ){

	int i = 0;

	//if(state == NULL || automaton_ptr == NULL || automaton_ptr->states[0] == NULL)
	//	return NULL;

	while(i < automaton_ptr->num_states){
		if(!strcmp(state, automaton_ptr->states[i])){
				return automaton_ptr->states[i];
		}
		i++;
	}

	return NULL;

}


int addEvent(automaton  *automaton_ptr, char * event_name, char * from, char *to){

	events * temp_event = malloc(sizeof(events));
	char   * error_state;

	/* Check if States in Events are the of the ones previous defined*/
	if((from = stateExists(from, automaton_ptr))==NULL ){
		error_state = from;
		goto state_not_found;
	}

	if((to = stateExists(to, automaton_ptr))==NULL){
		error_state=to;
		goto state_not_found;
	}

	/*Allocate the right amount of space for each variable*/

	// if((temp_event->event_name = malloc(strlen(event_name)*sizeof(char))) == NULL )
	// 	goto out_of_memory;
	// if((temp_event->from_state = malloc(strlen(from)*sizeof(char))) == NULL)
	// 	goto out_of_memory;
	// if((temp_event->to_state = malloc(strlen(to)*sizeof(char))) == NULL )
	// 	goto out_of_memory;	

	/* Copy the pointer of the new incomming data to the events struct*/
	temp_event->event_name = event_name;
	temp_event->from_state = from;
	temp_event->to_state = to;

	/* Important!!! especialy because this item is to be 
	stored at the end of the linked list*/
	temp_event->next = NULL; 

	
	addEvent2List(temp_event, automaton_ptr);

	return 0;


	/*
		Error Handling 
	*/

	state_not_found:
		printf("addEvent:The state '%s' presented in _EVENTS is not found on _STATE\n", error_state);
		//free(event_name);
		//free(from);
		//free(to);
		free(temp_event);
		return -1;
}


/*Add item (event) at the end of the linked list */
int addEvent2List( events *temp_event, automaton *automaton_ptr)
{	
	events * current = automaton_ptr->events_head;


	/*Just to handle first element with different name in first structure*/
	if(automaton_ptr->events_head == NULL){
	 	automaton_ptr->events_head = temp_event;
		return 0;
	}

	/*Iterate over existing items to reach the end*/
	current = ll_getlastItem(current);

	/*assign the pointer of the the temporary struct
	to previous last item of the linked list*/

	current->next = temp_event;
	
	//free(temp_event);

	return 0;
}


int printEvents(automaton *automaton_ptr){

	if(automaton_ptr == NULL)
		return -1;

	events * current = automaton_ptr->events_head;


	while(current!=NULL){
		printf("(%s) - %s -> (%s)\n",current->from_state, current->event_name, current->to_state);
		current = current->next;
	}
	
	printf("\n");

	return 0;
}

int printStates(automaton * automaton_ptr ){
	
	if(automaton_ptr == NULL)
		return -1;
	
	
	int i = 0;

	
	while(i<automaton_ptr->num_states){
		printf("STATES:%s\n", automaton_ptr->states[i]);
		i++;	
	}

	printf("\n");

	return 0;
}
int printInitial(automaton * automaton_ptr){

	if(automaton_ptr == NULL)
		return -1;

	printf("INITIAL = %s\n",automaton_ptr->initial_state );

	printf("\n");

	return 0;
}

int printFinals(automaton * automaton_ptr){

	if(automaton_ptr == NULL)
		return -1;

	int i=0;

	while(i<automaton_ptr->num_marked_states){
		printf("FINAL = %s\n",automaton_ptr->marked_states[i] );
		i++;
	}

	printf("\n");
	
	return 0;
}


int ll_freeAllAutomaton(automaton * automaton_ptr){

	if(automaton_ptr == NULL)
		return -1;

	events * current = automaton_ptr->events_head;
	events * pointer = automaton_ptr->events_head;
	int i=0;
	
	while(current != NULL){

		pointer = current;
		current = current->next;
		
		free(pointer->event_name);		
		free(pointer);
	}

	while(i<automaton_ptr->num_states ){

		free(automaton_ptr->states[i]);
	 	i++;
	}

	free(automaton_ptr->marked_states);
	free(automaton_ptr->states);
 	free(automaton_ptr);

 	return 0;
 }