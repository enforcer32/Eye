Program
	: StatementList
	;

StatementList
	: Statement
	| StatementList Statement
	;

Statement
	: ExpressionStatement
	| BlockStatement
	| VariableStatement
	| IfStatement
	;

ExpressionStatement
	: Expression ';'
	;

BlockStatement
	: '{' OptionalStatementList '}'
	;

VariableStatement
	: 'auto' VariableDeclarationList ';'
	;

VariableDeclarationList
	: VariableDeclaration
	| VariableDeclarationList ',' VariableDeclaration
	;

VariableDeclaration
	: Identifier OptionalVariableInitializer
	;

VariableInitializer
	: '=' AssignmentExpression
	;

IfStatement
	: 'if' '(' Expression ')' Statement
	| 'if' '(' Expression ')' Statement 'else' Statement
	;

Expression
	: AssignmentExpression
	;

AssignmentExpression
	: EqualityExpression
	| LHSExpression AssignmentOperator AssignmentExpression
	;

RelationalExpression
	: AdditiveBinaryExpression
	| AdditiveBinaryExpression RelationalOperator RelationalExpression
	;

EqualityExpression
	: RelationalExpression EqualityOperator EqualityExpression
	| RelationalExpression
	;

LHSExpression
	: Identifier
	;

Identifier
	: IDENTIFIER
	;

PrimaryExpression
	: Literal
	| ParenthesizedExpression
	| LHSExpression
	;

AdditiveBinaryExpression
	: MultiplicativeBinaryExpression
	| AdditiveBinaryExpression '+' MultiplicativeBinaryExpression
	| AdditiveBinaryExpression '-' MultiplicativeBinaryExpression
	;

MultiplicativeBinaryExpression
	: PrimaryExpression
	| MultiplicativeBinaryExpression '*' PrimaryExpression
	| MultiplicativeBinaryExpression '/' PrimaryExpression
	;

ParenthesizedExpression
	: '(' Expression ')'
	;

Literal
	: NumericLiteral
	| StringLiteral
	| BooleanLiteral
	| NullLiteral
	;

NumericLiteral
	: NUMBER
	;

StringLiteral
	: STRING
	;

BooleanLiteral
	: BOOL
	;

NullLiteral
	: NULL
	;

AssignmentOperator
	: '='
	| '+='
	| '-='
	| '**='
	| '/='
	| '%='
	;

RelationalOperator
	: '<'
	| '<='
	| '>'
	| '>='
	;

EqualityOperator
	: '=='
	| '!=
	;
