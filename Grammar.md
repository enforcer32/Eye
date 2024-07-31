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
	: AdditiveBinaryExpression
	;

PrimaryExpression
	: Literal
	| ParenthesizedExpression
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
