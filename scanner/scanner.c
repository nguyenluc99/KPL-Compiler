/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"


extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/

void skipBlank() {
  // TODO
  readChar();
}

void skipComment() {
  // TODO
  char prev;
  if (currentChar == '*') { // (* and *)
    prev = currentChar;
    readChar();
    while ((currentChar != ')' || prev != '*') && currentChar != EOF) {
      prev = currentChar;
      readChar();
    }
  } else if (currentChar == '/') { // "//" case
    while (currentChar != '\n' && currentChar != EOF) readChar();
  }
  if (currentChar == EOF) error(ERR_ENDOFCOMMENT, lineNo, colNo);
  readChar();
}

Token* readIdentKeyword(void) {
  // TODO
  int length = 0;
  Token *token = makeToken(TK_IDENT, lineNo, colNo);
  while (charCodes[currentChar] == CHAR_LETTER || charCodes[currentChar] == CHAR_DIGIT) {
    token->string[length++] = currentChar;
    if (length > 15)  // MAX_IDENT_LEN = 15 
      error(ERR_IDENTTOOLONG, token->lineNo, token->colNo);
    readChar();
  }
  token->string[length] = '\0';
  TokenType tokenType = checkKeyword(token->string);
  if (tokenType != TK_NONE)  // is a keyword 
    token->tokenType = tokenType;
  return token;
}

int biggerThanMax(char* stringNumber) {
  int i;
  char stringMax[12];
  sprintf(stringMax, "%d", INT_MAX);

  for (i = 0; i < 10; i++){
    if (stringMax[i] != stringNumber[i]) 
      return (stringNumber[i] > stringMax[i]) ? 1 : 0;
  }
  return 0;
}

Token* readNumber(void) {
  // TODO
  int length = 0;
  Token *token = makeToken(TK_NUMBER, lineNo, colNo);
  while (charCodes[currentChar] == CHAR_DIGIT && currentChar != EOF ) {
    token->string[length++] = currentChar;
    if (length > 10) {
      printf("LARGE STRING length 11 IS %s\n", token->string);
      error(ERR_NUMBERTOOLARGE, token->lineNo, token->colNo);
    }
    readChar();
  }
  token->string[length] = '\0';
  if (length == 10 && biggerThanMax(token->string)) {
      printf("LARGE STRING length 10 IS %s\n", token->string);
      error(ERR_NUMBERTOOLARGE, token->lineNo, token->colNo);
  } else {
    token->value = atoi(token->string);
    return token;
  }
}

Token* readConstChar(void) {
  // TODO
}

Token* getToken(void) {
  Token *token;
  int ln, cn;

  if (currentChar == EOF) 
    return makeToken(TK_EOF, lineNo, colNo);

  switch (charCodes[currentChar]) {
  case CHAR_SPACE: skipBlank(); return getToken();
  case CHAR_LETTER: return readIdentKeyword();
  case CHAR_DIGIT: return readNumber();
  case CHAR_PLUS: 
    token = makeToken(SB_PLUS, lineNo, colNo);
    readChar(); 
    return token;
    // ....
    // TODO
    // ....
  // case CHAR_MINUS:
  // case CHAR_TIMES:
  // case CHAR_SLASH:
  // case CHAR_LT:
  // case CHAR_GT:
  // case CHAR_EXCLAIMATION:
  // case CHAR_EQ:
  // case CHAR_COMMA:
  // case CHAR_PERIOD:
  // case CHAR_COLON:
  case CHAR_SEMICOLON:
    token = makeToken(SB_COLON, lineNo, colNo);
    readChar();
    return token;
  // case CHAR_SINGLEQUOTE:
  case CHAR_LPAR:
    readChar();
    if (currentChar == '*') {
      skipComment();
    }
    return getToken();
  // case CHAR_RPAR:
  // case CHAR_UNKNOWN:
  default:
    token = makeToken(TK_NONE, lineNo, colNo);
    error(ERR_INVALIDSYMBOL, lineNo, colNo);
    readChar(); 
    return token;
  }
}


/******************************************************************/

void printToken(Token *token) {

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType) {
  case TK_NONE: printf("TK_NONE\n"); break;
  case TK_IDENT: printf("TK_IDENT(%s)\n", token->string); break;
  case TK_NUMBER: printf("TK_NUMBER(%s)\n", token->string); break;
  case TK_CHAR: printf("TK_CHAR(\'%s\')\n", token->string); break;
  case TK_EOF: printf("TK_EOF\n"); break;

  case KW_PROGRAM: printf("KW_PROGRAM\n"); break;
  case KW_CONST: printf("KW_CONST\n"); break;
  case KW_TYPE: printf("KW_TYPE\n"); break;
  case KW_VAR: printf("KW_VAR\n"); break;
  case KW_INTEGER: printf("KW_INTEGER\n"); break;
  case KW_CHAR: printf("KW_CHAR\n"); break;
  case KW_ARRAY: printf("KW_ARRAY\n"); break;
  case KW_OF: printf("KW_OF\n"); break;
  case KW_FUNCTION: printf("KW_FUNCTION\n"); break;
  case KW_PROCEDURE: printf("KW_PROCEDURE\n"); break;
  case KW_BEGIN: printf("KW_BEGIN\n"); break;
  case KW_END: printf("KW_END\n"); break;
  case KW_CALL: printf("KW_CALL\n"); break;
  case KW_IF: printf("KW_IF\n"); break;
  case KW_THEN: printf("KW_THEN\n"); break;
  case KW_ELSE: printf("KW_ELSE\n"); break;
  case KW_WHILE: printf("KW_WHILE\n"); break;
  case KW_DO: printf("KW_DO\n"); break;
  case KW_FOR: printf("KW_FOR\n"); break;
  case KW_TO: printf("KW_TO\n"); break;

  case SB_SEMICOLON: printf("SB_SEMICOLON\n"); break;
  case SB_COLON: printf("SB_COLON\n"); break;
  case SB_PERIOD: printf("SB_PERIOD\n"); break;
  case SB_COMMA: printf("SB_COMMA\n"); break;
  case SB_ASSIGN: printf("SB_ASSIGN\n"); break;
  case SB_EQ: printf("SB_EQ\n"); break;
  case SB_NEQ: printf("SB_NEQ\n"); break;
  case SB_LT: printf("SB_LT\n"); break;
  case SB_LE: printf("SB_LE\n"); break;
  case SB_GT: printf("SB_GT\n"); break;
  case SB_GE: printf("SB_GE\n"); break;
  case SB_PLUS: printf("SB_PLUS\n"); break;
  case SB_MINUS: printf("SB_MINUS\n"); break;
  case SB_TIMES: printf("SB_TIMES\n"); break;
  case SB_SLASH: printf("SB_SLASH\n"); break;
  case SB_LPAR: printf("SB_LPAR\n"); break;
  case SB_RPAR: printf("SB_RPAR\n"); break;
  case SB_LSEL: printf("SB_LSEL\n"); break;
  case SB_RSEL: printf("SB_RSEL\n"); break;
  }
}

int scan(char *fileName) {
  Token *token;

  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  token = getToken();
  while (token->tokenType != TK_EOF) {
    printToken(token);
    free(token);
    token = getToken();
  }

  free(token);
  closeInputStream();
  return IO_SUCCESS;
}

/******************************************************************/

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("scanner: no input file.\n");
    return -1;
  }

  if (scan(argv[1]) == IO_ERROR) {
    printf("Can\'t read input file!\n");
    return -1;
  }
    
  return 0;
}


