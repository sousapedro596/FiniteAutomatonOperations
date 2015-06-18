#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_automatons.h"






int latex_print( automaton * automaton_ptr){

	FILE *fp;

	fp = fopen("automato.tex", "w");


	char * header = "\\documentclass{article}\n\\usepackage{tikz}\n\\usetikzlibrary{automata,positioning}\n\\begin{document}\n\\begin{tikzpicture}[shorten >=1pt,node distance=2cm,on grid,auto]\n\n";
	char * footer = "\\end{tikzpicture}\n\\end{document}\n ";

	fwrite(header, sizeof(char), strlen(header),fp );



	


	fwrite(footer, sizeof(char), strlen(footer), fp);
	fclose(fp);


	return 1;
}