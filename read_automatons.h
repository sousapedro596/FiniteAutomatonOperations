/*
	Automaton Data Types
*/

typedef struct {

	char *event_name; //the name of the event

	char *from_state;	//the state name from event occurs

	char *to_state; // event to this state name


	void *next; //next element of the linked list

} events;

typedef struct 
{
	//initial state of the automanton
	char *initial_state;


	//array of the marked states with size num_marked_states * each_state_name_size
	char **marked_states;
	int num_marked_states;


	//array of the states
	char **states;
	int num_states;

	
	//head of a linked list with all events of the automanton
	events *events_head;

	//number of the items on the list
	int number_of_events;
 
} automaton;


int read_automaton(automaton *ptr, char *filename);
int addState(automaton * automaton_ptr, int num_states, char * aux_string );

