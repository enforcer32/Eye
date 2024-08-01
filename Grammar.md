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

Expression
	: AssignmentExpression
	;

AssignmentExpression
	: AdditiveBinaryExpression
	| LHSExpression '=' AssignmentExpression
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
	;

NumericLiteral
	: NUMBER
	;

StringLiteral
	: STRING
	;
