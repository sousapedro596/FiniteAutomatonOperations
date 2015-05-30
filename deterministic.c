#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "read_automatons.h"
#include "deterministic.h"
#include "linked_lists.h"



//return the index of the value in the state vector

int state_position(char **vector, int vector_size,  char  *value){
	int i =0;

	for(i=0; i<vector_size; i++)
		if(vector[i] == value)
			return i;

		return -1;
}


int event_name_position(char **vector , int vector_size, char *event_pointer){

	int i =0;

	for(i=0; i< vector_size;i++){
		//printf("%s --- %s\n", vector[i], event_pointer );
		if(strcmp(vector[i] ,event_pointer)==0){
			//printf("milagre");
			return i;
		}
	}

	return -1;
}


int is_deterministic(automaton  *automaton_ptr){
/*

ex:

		 		states	

		e    1  x  x  x  x
		v    x  2  1  1  3
		e    x  x  x  x  x
		n    x  x  3  2  x
		t    x  2  x  x  x
		s    x  x  x  x  x

	x = 0...

number of times the same event occurs from the same state to other states,
basicaly if there's a number greater than 1 the automata it's not deterministic

*/

	events * current = automaton_ptr->events_head;
	int number_unique_events=0;

	int deterministic_resume[ automaton_ptr->number_of_events][ automaton_ptr->num_states ];

	char *events_vect[automaton_ptr->number_of_events];
	int i=0,j =0, deterministic =1;


	/* Reset all to zeros */
	for(i=0; i <automaton_ptr->number_of_events;i++)
		for(j=0;j<automaton_ptr->num_states;j++)
			deterministic_resume[i][j]=0;
		




	// int *mat = (int *)malloc(rows * cols * sizeof(int));
	//								lines				            cols

	//state_vect  = malloc(  *  sizeof(int));
	//events_vect = malloc(automaton_ptr->number_of_events * sizeof(char  *));

/*
	create a vector with all unique event names!

*/


	/*
		TO_DO:for the first element... needs to be rewritten!!!	
	*/

	events_vect[number_unique_events] = current->event_name;
	number_unique_events++;
	//printf("\n%s", events_vect[0] );


	for(i =1; i< automaton_ptr->number_of_events; i++){
		
		current = ll_getNextItem(current);

		/* 
			if the result of "event_name_position()" was -1 it means that the element is not already
			on the unique vector names!
		*/
		if(event_name_position(events_vect, number_unique_events, current->event_name)==-1){
			
			events_vect[number_unique_events] = current->event_name;
//printf("\n%s", events_vect[number_unique_events] );
			
			number_unique_events++;
			
		}
		
	}



	//reset pointer to list head
	current = automaton_ptr->events_head;

//	aux_from_state = current->from_state;
//	aux_event_name = current->event_name;



	
	do{

		//Fill the table of states x events, if some of position is greater 
		//than one the automaton is non deterministic

		if((++deterministic_resume[event_name_position(events_vect, number_unique_events, current->event_name)][state_position(automaton_ptr->states, automaton_ptr->num_states, current->from_state )])>1)
		{
			//TO_CHECK: while loop can be "breaked" here if we find that it's not deterministic and filling all the table
			//is not necessary 
			deterministic=0;
		};

	} 
	while((current = ll_getNextItem(current))!=NULL);




/* print all (Start)*/
	#if 1==1
	printf("   ");
	for ( i = 0; i < automaton_ptr->num_states; ++i){
		printf("%s|", automaton_ptr->states[i] );

	}
	printf("\n");

	for(i=0; i <number_unique_events;i++){
		for(j=0;j<automaton_ptr->num_states;j++){

			if(j==0)
				printf("%s| ",events_vect[i] );


			printf(" %d ", deterministic_resume[i][j] );
		}
		printf("\n");
	}
	#endif

/* print all (End)*/


	return deterministic;
}




/*
	Join to states and deal with memory allocation
	TO_DO; Maybe using "inline" in this fuction is better	

*/
char * join_states(char * state1, char * state2){
	
	state1 = realloc(state1, strlen(state1)+strlen(state2) + 1);
	
	strcat(state1, state2);

	return state1;
}

/*
	check if a state is present in a state vector

	RETURN:
		-1 if not
		1 if is there

*/

int is_in_states(char * state, char * states, int size_states ){

	while(size_states--)
		if(!strcmp(state, states[size_states]))
			return 1;

	return -1;
}


/*
	Which is the next state if happens the "event on the 
	current state  

*/


char * where_it_goes(automaton automaton_ptr, char * states, char *_event_name )
{
	int i, j=0;
	events * current = automaton_ptr->events_head;
	char * result_state = NULL;



	while( states[j] != NULL ){

		for (i =0; i< automaton_ptr->number_of_events ;i++ ){

			//if is the same event and from the same state
			if((!strcmp(current->event_name, event) && (!strcmp(current->from_state, state))){

				//if the state is not the same
				if(strcmp(state, current->to_state )){
					result_state = realloc( strlen(current->to_state) * sizeof(char) );
					result_state = join_states(result_state, current->to_state);
				}
			}

			current = ll_getNextItem(current);
		}

		j++;
	}

	return * result_state;
}


/*
	Main function to turn the automata deterministci

*/
int make_deterministic(automaton  *automaton_ptr){

	//char * aux_new_event
	//automaton *new_automaton;

	//ptr = malloc(sizeof(automaton));

	int i,j;
	int new_states_counter;
	char ** new_states;
	events current = automaton_ptr->events_head;


	// matrix of new_states
	// TODO TO_DO Maybe write a function...
	new_states = malloc(sizeof(char *));
	new_states[0] = malloc(sizeof(char *));
	
	new_states[0][0] = malloc(sizeof(char) * strlen(automaton_ptr->initial_state));
	
	new_states_counter = 1;

	for(n =0; n < new_states_counter;n++) {
		
	};


	return 1;
}