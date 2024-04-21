#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class LexicalAnalyzer
{
  private:
    char currentChar;
    int currentCharIndex;
    int currentTokenPosition;
    ifstream *sourceCodeFile;
    string line;
    string lexeme;
    TokenCodes tc; 
    TokenCodes tc2; 



    bool isEOI();
    void readNextLine();
    void getNextChar();
    void skipWhiteSpace();
    TokenCodes handleKeywordsAndIdentifiers(); 
    TokenCodes handleNumericLiterals(); 
    TokenCodes handleOperators(); 

  public:
    LexicalAnalyzer(ifstream*);
    Token* getNextToken();
    int getCurrentTokenPosition();
};

#endif