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
	;

ExpressionStatement
	: Expression ';'
	;

BlockStatement
	: '{' OptionalStatementList '}'
	;

Expression
	: Literal
	: AdditiveBinaryExpression
	;

Literal
	: NumericLiteral
	| StringLiteral
	;

BinaryExpression
	: Literal Operator Literal
	;

AdditiveBinaryExpression
	: Expression '+' Literal
	: Expression '-' Literal
	;

NumericLiteral
	: NUMBER
	;

StringLiteral
	: STRING
	;
