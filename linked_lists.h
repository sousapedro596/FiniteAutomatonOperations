int addEvent2List( events *temp_event, automaton *automaton_ptr);
int addEvent(automaton  *automaton_ptr, char * event_name, char * from, char *to);
int printEvents(automaton *automaton_ptr);
int printStates(automaton *automaton_ptr);
char * stateExists(char * state, automaton *automaton_ptr );
int ll_freeAllAutomaton(automaton * automaton_ptr);
int printInitial(automaton * automaton_ptr);
int printFinals(automaton * automaton_ptr);
events * ll_getNextItem(events *events_head);
