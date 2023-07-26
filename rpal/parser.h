#ifndef PARSER_H_
#define PARSER_H_
#include "lexer.h"
#include <stack>
#include "Standardizer.h"
#include "CSEMachine.h"

using namespace std;

class parser {
public:
    // Constructor that takes a lexer pointer as an argument
    parser(lexer*);

    // Functions to print the Abstract Syntax Tree (AST), Symbol Table (ST), and evaluate the program
    void printAST();
    void printST();
    void evaluateProg();

    // Destructor
    virtual ~parser();

private:
    // Private members
    lexer* lex;                  // Pointer to the lexer object
    stack<treeNode*> treeStack;  // Stack to hold the nodes of the abstract syntax tree
    token* nextToken;            // Pointer to the next token obtained from the lexer

    // Private functions representing different non-terminal symbols in the grammar
    void E();
    void Ew();
    void T();
    void Ta();
    void Tc();
    void B();
    void Bt();
    void Bs();
    void Bp();
    void A();
    void At();
    void Af();
    void Ap();
    void R();
    void Rn();
    void D();
    void Da();
    void Dr();
    void Db();
    void Vb();
    void Vl();

    // Main parsing function
    void parse();

    // Functions for standardizing the abstract syntax tree
    void standardize(treeNode*);

    // Functions for building the abstract syntax tree
    void buildTree(string, int);        // Builds a tree node with the given node name and specified number of child nodes
    void buildTree(string, int, int);   // Builds a tree node with the given node name, specified number of child nodes, and node type

    // Function for pretty printing the abstract syntax tree
    void treePrettyPrint(treeNode*, int);

    // Function to read the next token and check if it matches the expected token string
    void read(string);

    // Function to check if a given string is a keyword in the language
    bool isKeyword(string);

    // Function to convert a tree node to a string representation
    string to_s(treeNode*);
};

#endif /* PARSER_H_ */

