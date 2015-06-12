#define DEBUG

#define STATE 	"STATE"
#define EVENTS	"EVENTS"
#define SINIT	"SINIT"
#define SFINAL	"SFINAL"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_automatons.h"
#include "linked_lists.h"


// int fillString(){
	
// 	return 1;
// }


/*
	Reads from the file pointer position until finds a '\n'

	Returns:
		The pointer to a string with line readed
*/
// char * getLine(FILE *file_ptr){
// 	char aux_char,*string;
// 	int string_len=0;

// 	string = (char *) malloc(sizeof(char));

// 	while((aux_char=fgetc(file_ptr)) != '\n' ){

// 		string[string_len++] = aux_char;
// 		string = (char * ) realloc(string,(string_len+1)*sizeof(char));
// 	}
	
// 	//truncate the string
// 	string[string_len] = '\0';

// 	return string;
// }

/* 
	Reads the initial state of automaton and fills the
	automaton struct  (the file pointer need to be in 
	the beguinning of the initial state position)
	
	RETURN:
		returns the number of readed lines
*/
int readInitialState(FILE *file_ptr, automaton *automaton_ptr){

	char * aux_string    =	NULL;
	size_t len_aux_string=0;
	ssize_t readed_chars;
	
	if((readed_chars=getline(&aux_string, &len_aux_string,  file_ptr ))<1){
		printf("The _SINIT is not a valid state, check yout file!\n");
		free(aux_string);	
		return -1;
	}
	else
	{
		aux_string[readed_chars-1] = '\0';

		if((automaton_ptr->initial_state = stateExists(aux_string, automaton_ptr))==NULL){
			printf("readInitialState: The state '%s' does not exists", aux_string);
			free(aux_string);
			return -1;
		}
	}

	free(aux_string);
	//printf("%s\n", automaton_ptr->initial_state );

	/*One readed line*/
	return 1;
}

/* 
	Reads the final state of automaton and fills the
	automaton struct  (the file pointer need to be in 
	the beguinning of the final state position)
	
	RETURN:
		returns the number of readed lines
*/
int readFinalStates(FILE *file_ptr, automaton *automaton_ptr){

	char * aux_string    =	NULL;
	size_t len_aux_string=  0;
	ssize_t readed_chars;
	int    readed_lines	 =	0;  
	char *state_pointer;

	automaton_ptr->num_marked_states=0;
	free(automaton_ptr->marked_states);

	while((readed_chars = getline(&aux_string, &len_aux_string,  file_ptr ))>1){
		readed_lines++;

		aux_string[readed_chars-1] = '\0';
		
		if((state_pointer = stateExists(aux_string, automaton_ptr))!= NULL){
		//TO_DO: use addState() function instead!!!!!
			automaton_ptr->marked_states = realloc(automaton_ptr->marked_states,(readed_lines) * sizeof(char *));
			automaton_ptr->marked_states[automaton_ptr->num_marked_states] = state_pointer;
			automaton_ptr->num_marked_states++;
		
		}
		else {

			free(aux_string);
			free(state_pointer);
			printf("readFinalStates: The state '%s' does not exists", aux_string);
		}
		free(aux_string);
		aux_string = NULL;

	}

	free(aux_string);

	printf("%dmarked\n", automaton_ptr->num_marked_states);
	/*One readed line*/
	return 1;
}


/*
 Add a state to the automaton and increment the number of the states (num_states var)

*/
int addState(automaton * automaton_ptr, int num_states, char * aux_string ){

		if(!(automaton_ptr->states = realloc( automaton_ptr->states, sizeof(char *) * (num_states+1) )))
			return 0;
		//if(automaton_ptr->states);

		/*point the current states vector pointer to a allocated string from getline*/
		automaton_ptr->states[automaton_ptr->num_states] = aux_string;		
		
		automaton_ptr->num_states++;

		return 1;

}


int readStates(FILE *file_ptr, automaton *automaton_ptr){

	char * aux_string    =	NULL;
	int    readed_lines  =	0;
	size_t len_aux_string=0;
	ssize_t readed_chars;

	automaton_ptr->num_states = 0;

	while((readed_chars = getline(&aux_string, &len_aux_string,  file_ptr ))>1){
		
		readed_lines++;

		/*remove '\n' char (truncate the string)*/
		
		aux_string[readed_chars-1] = '\0';


//TO_DO: make functuon addState!!! (usefull if we don't want to add it from a file)

		/*Add one more position to states multidimensional vector*/
		//free(automaton_ptr->states);
//automaton_ptr->states = realloc( automaton_ptr->states, sizeof(char *) * readed_lines );
		//if(automaton_ptr->states);

		/*point the current states vector pointer to a allocated string from getline*/
//automaton_ptr->states[automaton_ptr->num_states] = aux_string;		
		
//automaton_ptr->num_states++;


	addState(automaton_ptr, automaton_ptr->num_states, aux_string );


		/* EXTREMELY IMPORTARNT  */
		/*After the first call of the getline if the 1st parameter is not NULL new space is not allocated
		and the string is overwritten */
		aux_string = NULL;
	}

	free(aux_string);

	return (readed_lines+1);
}

/*	
	Read Events from a File (the file pointer need to be in 
	the beguinning of the events description) and fill the automaton 
	struct passed by parameter 

	Return:
		The number of readed lines
*/

int readEvents(FILE *file_ptr, automaton *automaton_ptr){

	char *aux_string;
	int readed_lines = 0;
	size_t len_aux_string=0;
	ssize_t readed_chars;

	char delimiter[2] = " ";
	char * token;

	//set to zero the initial number of events (elements on the linked list)
	automaton_ptr->number_of_events = 0;


	int data_type=0; //0-> event name, 1-> from_state, 2-> to_state;

	char *event_name, *from_state, *to_state;

	while((readed_chars = getline(&aux_string, &len_aux_string,  file_ptr ))>1){
		readed_lines++;
		automaton_ptr->number_of_events++;
		aux_string[readed_chars-1] = '\0';

		/*
			Parse:
				event_name from_state to_state
		*/
		token = strtok( aux_string,delimiter);



		while( (token != NULL) && (data_type<3)){
			
			//printf(automaton_ptr->;
			
			switch(data_type){
				case 0:	/* event name */
					//printf("event name:%s size=%d", token, (int)strlen(token));	
					//event_name = /*(char *)*/ malloc( (strlen(token)+1)*sizeof(char));	
					//strcpy(event_name, token);
					//free(event_name);

					event_name = token;
				break;
				case 1: /* from_state */
					//printf("from state:%s size=%d ", token,(int) strlen(token));	
					//from_state = /*(char *) */malloc( (strlen(token)+1) * sizeof(char));
					//strcpy(from_state, token);
					from_state = token;
					//printf("from_state=%s size =%d\n", from_state, (int)strlen(from_state) );
				break;
				case 2: /* to_state */
					//printf("to state:%s\n", token);	
					//to_state = /*(char *)*/ malloc( (strlen(token)+1)*sizeof(char) );
					//strcpy(to_state, token);
					to_state = token;
				break;
			}


			token = strtok(NULL, delimiter);
			data_type++;
		}
		//reset the data_type to read by the order next time
		data_type=0;

		if(addEvent(automaton_ptr, event_name, from_state, to_state) == -1){
			
			/*Avoid Memory Leak when addEvents fails to add this event at the end of the list*/
			free(aux_string);
		}

		aux_string = NULL;
		

	}
	free(aux_string);
	free(token);
	//free(event_name);
	//free(to_state);
	//free(from_state);
	//printf("end%d", readed_lines);

	printf(" \n Number of events = %d\n", automaton_ptr->number_of_events);


	return readed_lines; // the last blank line (only '\n') doesn't count

}



/*
	Reads the automaton file
*/
int read_automaton(automaton *automaton_ptr, char * filename)
{
	FILE *fp;

	char data_header[20];
	int data_header_len=0;
	char read_char;

	int line_number=0;


	automaton_ptr->events_head = NULL;

	//char *string_aux;


	if((fp = fopen(filename,"r"))==NULL){
		printf("Error opening file\n");
		return -1;	
	};

	while((read_char = fgetc(fp)) != EOF){	

		//encontrar caracter de controlo para tipo de dados
		if(read_char == '_'){
			
			data_header_len = 0;
			
			//ler até ao fim da linha a procura de uma das palavras (STATE, EVENTS, SINITS, SFINAL)
			while((read_char = fgetc(fp)) != '\n')
			{
				//end if find a space before the end of the line or the buffer is full due to some file error
				if(read_char != ' '  && data_header_len < 20 )
					data_header[data_header_len++] = read_char;
			}

			//truncate the end of string 
			data_header[data_header_len] = '\0';

			#ifdef DEBUG
     		//printf("line %d - %s\n", line_number,data_header);
     		#endif	

     		/* If we are readind the Events  */
     		if(strcmp(data_header, EVENTS) == 0){
     			//printf("Found STATE\n");

     			
     			line_number += readEvents(fp, automaton_ptr);
     			//printf("%s\n", string_aux );
     		}

     		if(strcmp(data_header, STATE) == 0){
     			//printf("Found STATES\n");

     			line_number += readStates(fp, automaton_ptr);

     		}
     	
     		if(strcmp(data_header,SINIT) == 0){

     			line_number += readInitialState(fp, automaton_ptr);
     		}

     		if(strcmp(data_header, SFINAL) == 0){
				
				line_number +=  readFinalStates(fp, automaton_ptr);
     		}

		}



		//update the number of the lines
		if(read_char == '\n')
			line_number++;

	}
	fclose(fp);

	#ifdef DEBUG
	printf("Number_lines = %d\n",line_number );
	#endif
	return 0;
}


