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
	: BinaryExpression
	;

Literal
	: NumericLiteral
	| StringLiteral
	;

BinaryExpression
	: Literal Operator Literal
	;

NumericLiteral
	: NUMBER
	;

StringLiteral
	: STRING
	;
