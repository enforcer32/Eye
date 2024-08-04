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
	: LogicalORExpression
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

LogicalANDExpression
	: EqualityExpression '&&' LogicalANDExpression
	| EqualityExpression
	;

LogicalORExpression
	: LogicalANDExpression '||' LogicalORExpression
	| LogicalORExpression
	;

LHSExpression
	: PrimaryExpression
	;

Identifier
	: IDENTIFIER
	;

PrimaryExpression
	: Literal
	| ParenthesizedExpression
	| Identifier
	;

UnaryExpression
	: LHSExpression
	| UnaryOperator UnaryExpression
	;

AdditiveBinaryExpression
	: MultiplicativeBinaryExpression
	| AdditiveBinaryExpression AdditiveOperator MultiplicativeBinaryExpression
	;

MultiplicativeBinaryExpression
	: UnaryExpression
	| MultiplicativeBinaryExpression MultiplicativeOperator UnaryExpression
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

AdditiveOperator
	: '+'
	| '-'
	;

MultiplicativeOperator
	: '*'
	| '/'
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

LogicalOperator
	: '&&'
	| '||'
	;

UnaryOperator
	: '1'
	| '+'
	| '-'
	;
