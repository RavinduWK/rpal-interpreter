#include "lexer.h"

using namespace std;

lexer::lexer(std::ifstream* source) {
	sourceFile = source; //change to buffer
	lineCount = 1;
	charCount = 1;
}

lexer::~lexer() {
}

void lexer::lexerReset(){
	sourceFile->clear();
	sourceFile->seekg(0, ios::beg);
}

bool lexer::isPunction(char c){
  if('(' == c || ')' == c || ';' == c || ',' == c)
    return true;
  else
    return false;
}

bool lexer::isOperatorSymbol(char c){
	 if ('+' == c || '-' == c || '*' == c || '<' == c || '>' == c || '*' == c || '&' == c || '.' == c
	    || '@' == c|| '/' == c|| ':'== c || '=' == c|| '~' == c|| '|'== c || '$'== c || '!' == c
	    || '#'== c || '%'== c || '^'== c || '_'== c || '['== c || ']'== c || '{'== c || '}'== c
	    || '"'== c || '`'== c || '?'== c)
	        return true;
	    else
	        return false;
}

bool lexer::isCommentChar(char c){
	if (39 == c)  // char is '/'
		return true;
	else
		return false;
}

string lexer::tokenIdentifier(){
	string string_token= "";
	char next_peek;
	char next_char;
	do {
		sourceFile->get(next_char);
		charCount++;
		string_token += next_char;
		next_peek = sourceFile->peek();
	}while (!(EOF == next_peek) && (isalpha(next_peek) || isdigit(next_peek) || (95 == next_peek)));
	return string_token;
}

string lexer::tokenInteger(){
	string string_token= "";
	char next_peek;
	char next_char;
	do {
		sourceFile->get(next_char);
		charCount++;
		string_token += next_char;
		next_peek = sourceFile->peek();
	}while (!(EOF == next_peek) && isdigit(next_peek));
	return string_token;
}

string lexer::tokenStrings(){
	string string_token= "";
	char next_peek;
	char next_char;
	do{
		sourceFile->get(next_char);
		charCount++;
		string_token += next_char;
		next_peek = sourceFile->peek();
		if (next_char == '\\'){
		    if ((next_peek == 't' || next_peek == 'n' || next_peek == '\\' || next_peek == '\''))
		    {
		        continue; //Valid escape sequence
		    } else {
		        printf ("Invalid escape sequence\n");
		        exit(0);
		    }
		}
	} while (!(EOF == next_peek) && !(39 == next_peek));
	sourceFile->get(next_char);
	string_token += next_char;
	return string_token;
}

string lexer::tokenSpaces(){
	string string_token= "";
	char next_peek;
	char next_char;
	do{
		sourceFile->get(next_char);
		charCount++;
		if (10 == next_char || 13 == next_char){
			charCount = 1;
			lineCount++;
		}
		string_token += next_char;
		next_peek = sourceFile->peek();
	} while (!(EOF == next_peek) && isspace(next_peek));
	return string_token;
}

string lexer::tokenComment(){
	string string_token= "";
	char next_peek;
	char next_char;
	sourceFile->get(next_char);
	charCount++;
	string_token += next_char;
	next_peek = sourceFile->peek();
	if (47 == next_peek){
		sourceFile->get(next_char);
		string_token += next_char;
		do{
			sourceFile->get(next_char);
			string_token += next_char;
			next_peek = sourceFile->peek();
		} while (!(EOF == next_peek) && !(10 == next_peek || 13 == next_peek));
		return string_token;
	} else {
		return string_token;
	}
}

string lexer::tokenOperator(){
	string string_token= "";
	char next_peek;
	char next_char;
	do{
		sourceFile->get(next_char);
		charCount++;
		string_token += next_char;
		next_peek = sourceFile->peek();
	} while (!(EOF == next_peek) && isOperatorSymbol(next_peek));
	return string_token;
}

//This function is called by the read method in parser to fetch the new token.
//As per the rpal lexicon, the first character is used to determine which rule applies,
//a specialized function is called based on the rule that is applicable and
//subsequent characters are read till the newly read character differs from the selected rule.
//This marks the end of token, at which point it is passed to the parser.
token* lexer::getNextToken(){
	token* tok = new token();
	string tokenizedLex;
	int next_char;
	char readNext;
	next_char = sourceFile->peek();
	if (isalpha(next_char)){
		if (LEXLOGS) printf ("This is an identifier\n");
		tokenizedLex = tokenIdentifier();
        tok->tokType = TOK_IDENTIFIER;
	} else if (isdigit(next_char)) {
		if (LEXLOGS) printf ("This is an integer\n");
		tokenizedLex = tokenInteger();
		tok->tokType = TOK_INTEGER;
	} else if (39 == next_char){
		if (LEXLOGS) printf ("This is a string\n");
		tokenizedLex = tokenStrings();
		tok->tokType = TOK_STRING;
	} else if (isspace(next_char)){
		if (LEXLOGS) printf ("This is an space\n");
		tokenizedLex = tokenSpaces();
		tok->tokType = TOK_DELETE;
	} else if (isPunction(next_char)){
		if (LEXLOGS) printf ("This is a punction\n");
		sourceFile->get(readNext);
		charCount++;
		tokenizedLex = readNext;
		tok->tokType = TOK_PUNCTION;
	} else if (47 == next_char) {
		tokenizedLex = tokenComment();
		if (!tokenizedLex.compare("/")){
			if (LEXLOGS) printf ("This is an operator\n");
			tok->tokType = TOK_OPERATOR;
		} else{
			if (LEXLOGS) printf ("This is a comment\n");
			tok->tokType = TOK_DELETE;
		}
	} else if (isOperatorSymbol(next_char)){
		if (LEXLOGS) printf ("This is an operator\n");
		tokenizedLex = tokenOperator();
		tok->tokType = TOK_OPERATOR;
	} else if (EOF == next_char) {
		if (LEXLOGS) printf ("EOF reached\n");
		tok->tokType = TOK_EOF;
	}
	tok->tokValue = tokenizedLex;
	tok->charCount = charCount;
	tok->lineCount = lineCount;
	if (LEXLOGS) printf ("Lexer returning token type = %d, charCount = %d, lineCount = %d, value = %s\n",
			tok->tokType, tok->charCount, tok->lineCount, tok->tokValue.c_str());
	return tok;
}
