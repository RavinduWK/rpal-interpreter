#include "token.h"

// Constructor for the token class
token::token() {
    tokType = 0;        // Initialize token type to 0 (assuming an undefined type)
    tokValue = "";      // Initialize token value to an empty string
    lineCount = 0;      // Initialize lineCount to 0 (assuming an undefined line number)
    charCount = 0;      // Initialize charCount to 0 (assuming an undefined character count)

    // Note: Other data members of the token class may have been initialized
    // in the implementation file or have default values based on their data types.
}

// Destructor for the token class
token::~token() {
    // The destructor does not contain any specific actions since
    // there are no dynamically allocated resources to deallocate.
    // The memory management for data members is handled automatically.
    // However, if there were dynamically allocated resources (e.g., memory,
    // file handles, etc.) in the token class, they should be freed here.
}

