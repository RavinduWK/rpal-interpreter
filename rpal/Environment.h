#ifndef RPAL_COMPILER_ENVIRONMENT_H_
#define RPAL_COMPILER_ENVIRONMENT_H_

#include <map>
#include <string>
#include "Control.h"

using namespace std;

class Environment {
public:
    int id;                 // An integer representing the identifier of this environment.
    Environment *parent;    // A pointer to the parent environment.

    void assignParent(Environment* );    // Method to set the parent environment of this environment.
    Control* lookup(string);            // Method to look up a symbol in the symbol table.
    void prettyPrint();                 // Method to print the contents of the symbol table.
    
    Environment(int);                   // Constructor to create a new environment with the given 'id'.
    virtual ~Environment();             // Destructor for the Environment class.

    map<string, Control *> symbolTable; // A map to store symbols and their corresponding Control objects.
};

#endif /* RPAL_COMPILER_ENVIRONMENT_H_ */
