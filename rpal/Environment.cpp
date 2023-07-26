#include "Environment.h"

Environment::Environment(int id) {
    // Constructor to create a new environment with the given 'id'
    // TODO: It would be beneficial to describe the significance of 'id' in the context of the program.
    this->id = id;
}

Environment::~Environment() {
    // Destructor for the Environment class
    // TODO: If there are any resources or memory allocated in this class, handle their cleanup here.
}

void Environment::assignParent(Environment* parent){
    // Sets the parent environment of the current environment.
    this->parent = parent;
    // TODO: Ensure proper handling of circular references or invalid parent assignments.
}

Control* Environment::lookup(string str) {
    // Lookup a symbol in the current environment or its parent environments.

    // Search for the symbol 'str' in the symbol table using an iterator
    map<string, Control*>::iterator it = symbolTable.find(str);

    // If the symbol is not found in the current environment, search in the parent environment.
    if(symbolTable.end() == it)
        return parent->lookup(str);
    else
        return (*it).second; // Return the corresponding Control object if the symbol is found.
}

void Environment::prettyPrint(){
    // Display the contents of the symbol table in a human-readable format.

    // Iterate through the symbol table
    map<string, Control*>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); it++ )
        cout << (*it).first << " => " << (*it).second->toStr() << endl;
    // TODO: Add comments or documentation to specify the expected output format and any specific ordering.
}

