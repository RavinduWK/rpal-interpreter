#include <string>
#ifndef TOKEN_H_
#define TOKEN_H_

// Enum representing different types of tokens
enum tokenType {
    TOK_DEFAULT = 0,        // Default token type (undefined or not determined)
    TOK_KEYWORD = 1,        // Token represents a keyword
    TOK_IDENTIFIER = 2,     // Token represents an identifier (variable, function name, etc.)
    TOK_OPERATOR = 3,       // Token represents an operator
    TOK_WHITESPACE = 4,     // Token represents whitespace (spaces, tabs, etc.)
    TOK_COMMENT = 5,        // Token represents a comment
    TOK_STRING = 6,         // Token represents a string literal
    TOK_INTEGER = 7,        // Token represents an integer literal
    TOK_PUNCTION = 8,       // Token represents punctuation marks
    TOK_EOF = 9,            // Token represents the end of the file (EOF)
    TOK_DELETE = 10,        // Token is flagged for deletion (used during tokenization)
    TOK_ERROR,              // Token represents an error (e.g., invalid character)
    TOK_ANY                 // Token represents any token (used in certain matching scenarios)
};

// Token class representing a lexical token
class token {

public:
    token();                // Constructor for the token class
    virtual ~token();       // Destructor for the token class

    int tokType;            // Type of the token (from the tokenType enum)
    std::string tokValue;   // Value of the token (actual characters matched)
    int lineCount;          // Line number where the token is found
    int charCount;          // Character count in the current line where the token starts
};

#endif /* TOKEN_H_ */

