#include <fstream>
#include <iostream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream *sourceCodeFile;
  LexicalAnalyzer *la;
  Token *nextToken;
  TokenCodes tc;
  sourceCodeFile = new ifstream();

  sourceCodeFile->open(argv[1], ifstream::in);
  if  (sourceCodeFile->is_open())
  {
    la = new LexicalAnalyzer(sourceCodeFile);
    do
    {
      nextToken = la->getNextToken();
      cout << *nextToken << endl;
      tc = nextToken->getTokenCode();
      delete nextToken;
    } while (tc != EOI);
    delete la;
    sourceCodeFile->close();
  }
  else
    cout << "ERROR - cannot open input file." << endl;

  return 0;
}