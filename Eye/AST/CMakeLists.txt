file(GLOB_RECURSE ASTSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Program.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Program.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/Statement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/ExpressionStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/BlockStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/VariableStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/ControlStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/IterationStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/FunctionStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/ReturnStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/ContinueStatement.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Statements/BreakStatement.h"

	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/Expression.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/LiteralExpression.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/BinaryExpression.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/AssignmentExpression.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/IdentifierExpression.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/UnaryExpression.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/MemberExpression.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Expressions/CallExpression.h"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${ASTSources})
