int is_deterministic(automaton  *automaton_ptr);
void make_deterministic(automaton  *automaton_ptr, automaton *new_deter_automaton);
char * join_states(char * state1, char * state2);
