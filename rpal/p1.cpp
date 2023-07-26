#include <stdio.h>
#include <string.h>
#include <fstream>
#include "lexer.h"
#include "parser.h"

using namespace std;

// Global variables and constants.
ifstream source; // Input file stream for reading source code.
int option = 0x0000; // Integer to store command line options in binary form.
enum cmdOpts{ // Enumeration for command line options represented as bit flags.
    OPT_L = 0x0001, // Option to print the source code.
    OPT_NOOUT = 0x0010, // Option to suppress output (not implemented).
    OPT_ST = 0x0100, // Option to print symbol table (not implemented).
    OPT_AST = 0x1000 // Option to print abstract syntax tree (AST).
};

bool isEvaluateProg = true; // Flag to determine if the program needs to be evaluated.

// Function to print the source code when option -l is used.
void printOptionL(){
    string line;
    getline(source, line);
    while (source.good()){
        printf ("%s\n", line.c_str());
        getline(source, line);
    }
    source.clear();
    source.seekg(0, ios::beg);
}

// Function to execute the lexer and parser.
void exec() {
    lexer* rpalLexer = new lexer(&source);
    parser* rpalParser = new parser(rpalLexer);
    if (option & OPT_L){
        printOptionL();
    }
    if(option & OPT_AST) {
        rpalParser->printAST();
    }
    if(option & OPT_ST) {
        rpalParser->printST();
        //printf ("Option -st Not Implemented. Current Valid options are: -l -ast\n");
    }
    if(option & OPT_NOOUT){
        printf ("Option -noout Not Implemented. Current Valid options are: -l -ast\n");
    }
    if (isEvaluateProg){
        //sprintf ("Evaluate program\n");
        rpalParser->evaluateProg();
    }
}

int main (int argc, char *argv[]){
    int i = 1;
    // Usage: rpal <Switches; Can be more than 1> <Filename; Always the last>
    if (argc >= 2){
        char* filename = argv[argc-1];
        if (MAIN_DEBUG_LOGS) printf ("Filename = %s\n", filename);
        source.open(filename);
        if (!source.good()){
            printf ("File \"%s\" not found\n", filename);
            return 0;
        }
        // Order of switches doesn't matter. More than one switch can be added. Not all are implemented in p1 though.
        while (i < argc - 1){
            if (strcmp(argv[i], "-ast") == 0){
                option |= OPT_AST; // Set the AST option bit.
                isEvaluateProg = false; // Disable program evaluation.
            } else if (strcmp(argv[i], "-st") == 0){
                option |= OPT_ST; // Set the symbol table option bit.
                isEvaluateProg = false; // Disable program evaluation.
            } else if (strcmp (argv[i], "-noout") == 0){
                option |= OPT_NOOUT; // Set the no-output option bit.
                isEvaluateProg = false; // Disable program evaluation.
            } else if (strcmp(argv[i], "-l") == 0){
                option |= OPT_L; // Set the print source code option bit.
                isEvaluateProg = false; // Disable program evaluation.
            } else {
                if (MAIN_DEBUG_LOGS) printf ("Invalid Option\n");
            }
            i++;
        }
        exec(); // Execute the lexer and parser.
        source.close(); // Close the input file stream.
    } else {
        printf ("[rpal Compiler \n Author: Sachin Edlabadkar]\n\n");
        printf ("Usage: ./p1 [-l] [-ast] [-noout] [-st] <filename>\n\n");
    }
}
