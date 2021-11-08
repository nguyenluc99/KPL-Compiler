1:
Modify file example2.kpl so that it causes the error “Invalid statement”
2:
Block4 ::= FunDecls Block5 
Block4 ::= Block5
Block5 ::= ProcDecls Block6 
Block5 ::= Block6
FunDecls::= FunDecl FunDecls
FunDecls::= eps
ProcDecls::= ProcDecl  ProcDecls
ProcDecls ::= eps
Block6 ::= KW_BEGIN Statements KW_END
Modify relevant functions in your parser to match the new rules
