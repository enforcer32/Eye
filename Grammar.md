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
