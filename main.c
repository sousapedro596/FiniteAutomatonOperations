#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "read_automatons.h"
#include "linked_lists.h"
#include "deterministic.h"
#include <gtk/gtk.h>

int run_automaton_code(int argc, char * argv[]){
	
#if 1==1

	automaton *ptr;

	ptr = malloc(sizeof(automaton));

	if(argc<2){
		printf("Enter the filename!\n");
		return -1;
	};		


	if(read_automaton(ptr,argv[1])==-1)
		return -1;


	if(is_deterministic(ptr))
		printf("The automaton is deterministic!\n");
	else
		printf("The automaton is not deterministic!\n");


	printEvents(ptr);
	printStates(ptr);
	printInitial(ptr);
	printFinals(ptr);
	ll_freeAllAutomaton(ptr);


#endif

// Tests

#if 1==0


	char * state1, * state2;


	state1 = malloc(5*sizeof(char));
	state2 = malloc(10*sizeof(char));


	strcpy(state1,"ola");
	printf("Ola\n");
	strcpy(state2,", bom dia!");

	state1 = join_states(state1, state2);


	printf("%s\n", state1 );


#endif



	return 0;





}


int main(int argc, char *argv[])
{
	run_automaton_code(argc, argv);

	//call_interface();

	return 0;
}


