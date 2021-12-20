/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

static int searching = 0;

Object* lookupObject(char *name) {
  // TODO DONE
  Object * obj = NULL;
  static Scope * currentScope = NULL;
  if (searching == 0) {
    currentScope = symtab->currentScope;
    searching = 1;
  }
  while(currentScope != NULL) {
    obj = findObject(currentScope->objList, name);
    currentScope = currentScope->outer;
    if (obj != NULL)
      return obj;
  }
  if (obj == NULL) {
    obj = findObject(symtab->globalObjectList, name);
  }
  searching = 0;
  return obj;
}

void checkFreshIdent(char *name) {
  // TODO DONE
  Object* obj = findObject(symtab->currentScope->objList, name);
  if (obj != NULL) {
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
  }
}

Object* checkDeclaredIdent(char* name) {
  // TODO DONE
  searching = 0;
  Object *obj = lookupObject(name);
  searching = 0;

  if (obj == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredConstant(char* name) {
  // TODO DONE
  Object *obj = NULL;
  searching = 0;
  do {
    obj = lookupObject(name);
    if (obj != NULL && obj->kind ==  OBJ_CONSTANT) break;
  } while (obj != NULL);
  searching = 0;
  if (obj == NULL) 
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredType(char* name) {
  // TODO DONE
  Object *obj = NULL;
  searching = 0;
  do {
    obj = lookupObject(name);
    if (obj != NULL && obj->kind == OBJ_TYPE) break;
  } while (obj != NULL);
  searching = 0;
  if (obj == NULL) 
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredVariable(char* name) {
  // TODO DONE
  Object *obj = NULL;
  searching = 0;
  do {
    obj = lookupObject(name);
    if (obj != NULL && obj->kind == OBJ_VARIABLE) break;
  } while (obj != NULL);
  searching = 0;
  if (obj == NULL) 
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredFunction(char* name) {
  // TODO DONE
  Object *obj = NULL;
  searching = 0;
  do {
    obj = lookupObject(name);
    if (obj != NULL && obj->kind == OBJ_FUNCTION) break;
  } while (obj != NULL);
  searching = 0;
  if (obj == NULL) 
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredProcedure(char* name) {
  // TODO DONE
  Object *obj = NULL;
  searching = 0;
  do {
    obj = lookupObject(name);
    if (obj != NULL && obj->kind == OBJ_PROCEDURE) break;
  } while (obj != NULL);
  searching = 0;
  if (obj == NULL) 
    error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO DONE
  Object *obj = NULL;
  searching = 0;
  do {
    obj = lookupObject(name);
    if (obj != NULL && (obj->kind == OBJ_FUNCTION || obj->kind == OBJ_PARAMETER || obj->kind == OBJ_VARIABLE)) break;
  } while (obj != NULL);
  searching = 0;
  if (obj == NULL) 
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

