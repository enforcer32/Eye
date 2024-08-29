#pragma once

#include "EYEAST/Statements/Statement.h"
#include "EYEAST/Statements/BlockStatement.h"
#include "EYEAST/Expressions/IdentifierExpression.h"

#include <memory>
#include <vector>

namespace Eye
{
	namespace AST
	{
		/*
			FunctionParameterList
				: FunctionParameter
				| FunctionParameterList ',' FunctionParameter
				;
		
			FunctionParameter
				: DataTypeKeyword IdentifierExpression OptionalVariableInitializer
				;
		*/
		class FunctionParameter
		{
		public:
			FunctionParameter(Lexer::Token dataType, const std::shared_ptr<IdentifierExpression>& identifier, const std::shared_ptr<Expression>& initializer)
				: m_DataType(dataType), m_Identifier(identifier), m_Initializer(initializer)
			{
			}

			inline Lexer::Token GetDataType() const { return m_DataType; }
			inline std::shared_ptr<IdentifierExpression> GetIdentifier() const { return m_Identifier; }
			inline std::shared_ptr<Expression> GetInitializer() const { return m_Initializer; }

		private:
			Lexer::Token m_DataType;
			std::shared_ptr<IdentifierExpression> m_Identifier;
			std::shared_ptr<Expression> m_Initializer;
		};

		/*
			FunctionStatement
				: 'function' DataTypeKeyword Identifier '(' OptionalFunctionParameterList ')' BlockStatement
				;
		*/
		class FunctionStatement : public Statement
		{
		public:
			FunctionStatement(Lexer::Token returnType, const std::shared_ptr<IdentifierExpression>& identifier, const std::vector<std::shared_ptr<FunctionParameter>>& parameters, const std::shared_ptr<BlockStatement>& body)
				: Statement(StatementType::FunctionStatement), m_ReturnType(returnType), m_Identifier(identifier), m_Parameters(parameters), m_Body(body)
			{
			}

			inline Lexer::Token GetReturnType() const { return m_ReturnType; }
			inline std::shared_ptr<IdentifierExpression> GetIdentifier() const { return m_Identifier; }
			inline const std::vector<std::shared_ptr<FunctionParameter>>& GetParameters() const { return m_Parameters; }
			inline std::shared_ptr<BlockStatement> GetBody() const { return m_Body; }

		private:
			Lexer::Token m_ReturnType;
			std::shared_ptr<IdentifierExpression> m_Identifier;
			std::vector<std::shared_ptr<FunctionParameter>> m_Parameters;
			std::shared_ptr<BlockStatement> m_Body;
		};
	}
}
