/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  // TODO DONE
  Type* t = (Type*) malloc(sizeof(type));
  t->typeClass = type->typeClass;
  t->arraySize = type->arraySize;
  t->elementType = type->elementType;
  return t;
}

int compareType(Type* type1, Type* type2) {
  // TODO
  return 0;
}

void freeType(Type* type) {
  // TODO
  return 0;
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO DONE
  ConstantValue* cv = (ConstantValue*) malloc(sizeof(ConstantValue));
  cv->type = TP_INT;
  cv->intValue = i;
  return cv;
}

ConstantValue* makeCharConstant(char ch) {
  // TODO DONE
  ConstantValue* cv = (ConstantValue*) malloc(sizeof(ConstantValue));
  cv->type = TP_CHAR;
  cv->charValue = ch;
  return cv;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO DONE
  ConstantValue* cv = (ConstantValue*) malloc(sizeof(ConstantValue));
  cv->type = v->type;
  if (cv->type == TP_INT)
    cv->intValue = v->intValue;
  else if (cv->type == TP_CHAR)
    cv->charValue = v->charValue;
  return cv;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  // TODO DONE
  Object* obj = (Object*) malloc(sizeof(Object));
  obj->kind = OBJ_CONSTANT;
  strcpy(obj->name, name);
  obj->constAttrs = (ConstantAttributes*)malloc(sizeof(ConstantAttributes));
  obj->constAttrs->value = NULL;
  return obj;
}

Object* createTypeObject(char *name) {
  // TODO DONE
  Object* obj = (Object*) malloc(sizeof(Object));
  obj->kind = OBJ_TYPE;
  strcpy(obj->name, name);
  obj->typeAttrs = (TypeAttributes*)malloc(sizeof(TypeAttributes));
  obj->typeAttrs->value = NULL;
  return obj;
}
}

Object* createVariableObject(char *name) {
  // TODO DONE
  Object* obj = (Object*) malloc(sizeof(Object));
  obj->kind = OBJ_VAR;
  strcpy(obj->name, name);
  obj->varAttrs = (VarAttributes*)malloc(sizeof(VarAttributes));
  obj->varAttrs->value = NULL;
  return obj;
}

Object* createFunctionObject(char *name) {
  // TODO DONE
  Object* obj = (Object*) malloc(sizeof(Object));
  obj->kind = OBJ_FUNCTION;
  strcpy(obj->name, name);
  obj->functionAttrs = (FunctionAttributes*)malloc(sizeof(FunctionAttributes));
  obj->functionAttrs->value = NULL;
  return obj;
}

Object* createProcedureObject(char *name) {
  // TODO DONE
  Object* obj = (Object*) malloc(sizeof(Object));
  obj->kind = OBJ_PROCEDURE;
  strcpy(obj->name, name);
  obj->procedureAttrs = (ProcedureAttributes*)malloc(sizeof(ProcedureAttributes));
  obj->procedureAttrs->value = NULL;
  return obj;
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO HALF
  Object* obj = (Object*) malloc(sizeof(Object));
  obj->kind = OBJ_PARAMETER;
  strcpy(obj->name, name);
  obj->parameterAttrs = (ParameterAttributes*)malloc(sizeof(ParameterAttributes));
  obj->parameterAttrs->kind = kind;
  obj->parameterAttrs->function = owner;
  obj->parameterAttrs->type = NULL; // not clear
  return obj;
}
}

void freeObject(Object* obj) {
  // TODO
}

void freeScope(Scope* scope) {
  // TODO
}

void freeObjectList(ObjectNode *objList) {
  // TODO
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


