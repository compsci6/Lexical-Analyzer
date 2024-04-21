#include <iostream>
#include <fstream>
#include <cctype>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf) 
{
  currentChar = '\n';
  currentCharIndex = 0;
  sourceCodeFile = scf;
  line = "\n";

}

bool LexicalAnalyzer::isEOI()  
{
  return (sourceCodeFile->eof() && (currentCharIndex == (line.length() - 1)));
}

void LexicalAnalyzer::readNextLine()  
{
  getline(*sourceCodeFile, line);
  line = line + "\n";
}

void LexicalAnalyzer::getNextChar()  
{
  if (currentCharIndex == (line.length() - 1))
  {
    readNextLine();
    currentCharIndex = -1;
  }

  currentCharIndex++;
  currentChar = line.at(currentCharIndex);
}


void LexicalAnalyzer::skipWhiteSpace() {
   
    while (!isEOI()){
    if (isspace(currentChar) || currentChar == '\n') {
        getNextChar();
        
    }else 
    break;
    }
    
}




TokenCodes LexicalAnalyzer::handleKeywordsAndIdentifiers() {
    
    
    if (isalpha(currentChar)) {
        
        lexeme = currentChar;
        getNextChar();
        while (isalpha(currentChar) || isdigit(currentChar)) {
            lexeme += currentChar;
            getNextChar();
        }
        
        if (lexeme == "if") {
            tc = IFSYM;
        } else if (lexeme == "else") {
            tc = ELSESYM;
        } 
        else if (lexeme == "bool") {
            tc = BOOLSYM;
            }
        else if (lexeme == "do") {
            tc = DOSYM;
            }
        else if (lexeme == "false") {
            tc = FALSESYM;
            }
        else if (lexeme == "float") {
            tc = FLOATSYM;
            }
        else if (lexeme == "for") {
            tc = FORSYM;
            }
        else if (lexeme == "int") {
            tc = INTSYM;
            }
        else if (lexeme == "printf") {
            tc = PRINTFSYM;
            }
        else if (lexeme == "return") {
            tc = RETURNSYM;
            }
        else if (lexeme == "scanf") {
            tc = SCANFSYM;
            }
        else if (lexeme == "true") {
            tc = TRUESYM;
            }
        else if (lexeme == "void") {
            tc = VOIDSYM;
            }
        else if (lexeme == "while") {
            tc = WHILESYM;
            }
        else {
            tc = IDENT;}
}
    
    return tc;  

}


TokenCodes LexicalAnalyzer::handleNumericLiterals() {
    
    lexeme = currentChar;
    getNextChar();
   
    while (isdigit(currentChar) || currentChar == '.') {
        lexeme += currentChar;
        getNextChar();
    }
    tc = NUMLIT;    
    return tc;
}




TokenCodes LexicalAnalyzer::handleOperators() {
    
  
   
    if(currentChar == '>'){
            lexeme = currentChar;
            tc = GTR;
            getNextChar();
            if(currentChar == '='){
                lexeme += currentChar;
                tc = GEQ;
                
            }
    }else if(currentChar == '='){
        lexeme = currentChar;
        tc = ASSIGN;
        getNextChar();
        if(currentChar == '='){
            lexeme += currentChar;
            tc = EQL;

        }
    }else if(currentChar == '!'){
        lexeme = currentChar;
            tc = NOT;
        getNextChar();
        if(currentChar == '='){
            lexeme += currentChar;
            tc = NEQ;

        }
    }else if(currentChar == '<'){
        lexeme = currentChar;
        tc = LSS;
        getNextChar();
        if(currentChar == '='){
            lexeme += currentChar;
            tc = LEQ;
        }

    }
    else if(currentChar == '|'){
        lexeme = currentChar;
        getNextChar();

        if(currentChar == '|'){
        lexeme += currentChar;
        tc = OR;

        }
    }else if(currentChar == '&'){
        lexeme = currentChar;
        getNextChar();}

            if(currentChar == '&'){
                lexeme += currentChar;
                tc = AND;}
    else if(currentChar == '+'){
        lexeme = currentChar;
        tc = PLUS;
    }else if(currentChar == '-'){
        lexeme = currentChar;
        tc = MINUS;
    }else if(currentChar == '*'){
        lexeme = currentChar;
        tc = TIMES;
    }else if(currentChar == '/'){
        lexeme = currentChar;
        tc = SLASH;
    }else if(currentChar == '%'){
        lexeme = currentChar;
        tc = MOD;
    }else if(currentChar == '('){
        lexeme = currentChar;
        tc = LPAREN;
    }else if(currentChar == ')'){
        lexeme = currentChar;
        tc = RPAREN;
    }else if(currentChar == '{'){
        lexeme = currentChar;
        tc = LBRACE;
    }else if(currentChar == '}'){
        lexeme = currentChar;
        tc = RBRACE;
    }else if(currentChar == ','){
        lexeme = currentChar;
        tc = COMMA;
    }else if(currentChar == ';'){
        lexeme = currentChar;
        tc = SEMICOLON;
    }else {
        lexeme = currentChar;
        tc = NAL;
    }

            
getNextChar();
return tc;
    
}


Token* LexicalAnalyzer::getNextToken() {
Token *t;
    
   skipWhiteSpace();
   if (isEOI()) {
       
        tc2 = EOI;
        lexeme = "end of input";
   }
    else if (isalpha(currentChar)) {
       
        tc2 = handleKeywordsAndIdentifiers();
        
    } else if (isdigit(currentChar)) {
        
        tc2 = handleNumericLiterals();
        
    } else{
        
        tc2 = handleOperators();
    }

  
    
    t = new Token(tc2,lexeme);
     
    
    return t;
}

