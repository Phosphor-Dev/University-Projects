// PARSER RULES START HERE
 grammar Crux;

literal
: INTEGER
| TRUE
| FALSE
;

designator
: IDENTIFIER (OPEN_BRACKET expr0 CLOSE_BRACKET)?
;

type
: IDENTIFIER
;

op0
: GREATER_EQUAL
| LESSER_EQUAL
| NOT_EQUAL
| EQUAL
| GREATER_THAN
| LESS_THAN
;

op1
: ADD
| SUB
| OR
;

op2
: MUL
| DIV
| AND
;

expr0
: expr1 ( op0 expr1 )?
;

expr1
: expr2
| expr1 op1 expr2
;

expr2
: expr3
| expr2 op2 expr3
;

expr3
: NOT expr3
| OPEN_PAREN expr0 CLOSE_PAREN
| designator
| callExpr
| literal
;

callExpr
: IDENTIFIER OPEN_PAREN exprList CLOSE_PAREN
;

exprList
: (expr0 (COMMA expr0)*)?
;

param //
: type IDENTIFIER
;

paramList
: (param (COMMA param)*)?
;

varDecl
: type IDENTIFIER SEMICOLON
;

arrayDecl
: type IDENTIFIER OPEN_BRACKET INTEGER CLOSE_BRACKET SEMICOLON
;

functionDefn
: type IDENTIFIER OPEN_PAREN paramList CLOSE_PAREN stmtBlock
;

decl
: varDecl
| arrayDecl
| functionDefn
;

declList
: decl*
;

////
assignStmt
: designator ASSIGN expr0 SEMICOLON
;

assignStmtNoSemi
: designator ASSIGN expr0
;

callStmt
: callExpr SEMICOLON
;

ifStmt
: IF expr0 stmtBlock ( ELSE stmtBlock )?
;

forStmt
: FOR OPEN_PAREN assignStmt expr0 SEMICOLON assignStmtNoSemi CLOSE_PAREN stmtBlock
;

breakStmt
: BREAK SEMICOLON
;

returnStmt
: RETURN expr0 SEMICOLON
;

stmt
: varDecl
| callStmt
| assignStmt
| ifStmt
| forStmt
| breakStmt
| returnStmt
;

stmtList
: stmt*
;

stmtBlock
: OPEN_BRACE stmtList CLOSE_BRACE
;

program
: declList EOF
;


// LEXER RULES START HERE

//The following words are reserved types, but are recognized as IDENTIFIER tokens: void, bool, int.
AND: '&&';

OR: '||';

NOT: '!';

IF: 'if';

ELSE: 'else';

FOR: 'for';

BREAK: 'break';

TRUE: 'true';

FALSE: 'false';

RETURN: 'return';

/////////////////////////

SEMICOLON: ';';

OPEN_PAREN: '(';

CLOSE_PAREN: ')';

OPEN_BRACE: '{';

CLOSE_BRACE: '}';

OPEN_BRACKET: '[';

CLOSE_BRACKET: ']';

ADD: '+';

SUB: '-';

MUL: '*';

DIV: '/';

GREATER_EQUAL: '>=';

LESSER_EQUAL: '<=';

NOT_EQUAL: '!=';

EQUAL: '==';

GREATER_THAN: '>';

LESS_THAN: '<';

ASSIGN: '=';

COMMA: ',';

//////////////////////////////////

COMMENT: '//' ~[\r\n]* -> skip;

WHITESPACES: [ \t\r\n]+ -> skip;

/////////////////////////////////////////////////

INTEGER
: '0'
| [1-9] [0-9]*
;

IDENTIFIER
: [a-zA-Z] [a-zA-Z0-9_]*
;

