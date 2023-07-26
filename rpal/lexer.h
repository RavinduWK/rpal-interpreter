#ifndef LEXER_H_
#define LEXER_H_

// Namespace usage directly in header files can lead to naming conflicts. Be cautious.
using namespace std;

// Define some global constants to control logging.
#define LEXLOGS 0
#define PARSERLOGS 0
#define STANDARDIZERLOGS 0
#define MAIN_DEBUG_LOGS 0

#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iostream>

// Include the "token.h" header file, assuming it contains the definition of the `token` class.
#include "token.h"

// The lexer class definition begins here.
class lexer {
public:
    // Constructor taking a pointer to an ifstream as input.
    lexer(std::ifstream*);
    
    // Virtual destructor. Consider defining the destructor's implementation in a source file.
    virtual ~lexer();

    // Public member function to get the next token from the source code.
    token* getNextToken();

    // Public member function to reset the lexer, useful for re-lexing the source code.
    void lexerReset();

private:
    // Private data members to store the input stream, line count, and character count.
    ifstream* sourceFile;
    int lineCount, charCount;

    // Private member functions to tokenize different parts of the source code.
    // These functions extract and return tokens as strings.
    string tokenIdentifier();
    string tokenInteger();
    string tokenStrings();
    string tokenSpaces();
    string tokenComment();
    string tokenOperator();
    string tokenPunction(); // Assuming a typo here, it should be `tokenPunctuation`.

    // Private helper functions to check character types.
    bool isPunction(char);
    bool isOperatorSymbol(char);
    bool isSpaces(char);
    bool isEOL(char); // Assuming End Of Line character check.
    bool isEOF(char); // Assuming End Of File character check.
    bool isCommentChar(char);

    // Private function to check if a given string is a keyword.
    bool isKeyword(string);
};

#endif /* LEXER_H_ */
