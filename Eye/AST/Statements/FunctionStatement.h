#pragma once

#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Statements/BlockStatement.h"
#include "Eye/AST/Expressions/IdentifierExpression.h"

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
				: OptionalTypeQualifierKeyword DataTypeKeyword IdentifierExpression OptionalVariableInitializer
				;
		*/
		class FunctionParameter
		{
		public:
			FunctionParameter(std::unique_ptr<Token> typeQualifier, std::unique_ptr<Token> dataType, std::unique_ptr<IdentifierExpression> identifier, std::unique_ptr<Expression> initializer)
				: m_TypeQualifier(std::move(typeQualifier)), m_DataType(std::move(dataType)), m_Identifier(std::move(identifier)), m_Initializer(std::move(initializer))
			{
			}

			inline const Token* GetTypeQualifier() const { return m_TypeQualifier.get(); }
			inline const Token* GetDataType() const { return m_DataType.get(); }
			inline const IdentifierExpression* GetIdentifier() const { return m_Identifier.get(); }
			inline const Expression* GetInitializer() const { return m_Initializer.get(); }

		private:
			std::unique_ptr<Token> m_TypeQualifier;
			std::unique_ptr<Token> m_DataType;
			std::unique_ptr<IdentifierExpression> m_Identifier;
			std::unique_ptr<Expression> m_Initializer;
		};

		/*
			FunctionStatement
				: 'function' DataTypeKeyword Identifier '(' OptionalFunctionParameterList ')' BlockStatement
				;
		*/
		class FunctionStatement : public Statement
		{
		public:
			FunctionStatement(const EyeSource& source, std::unique_ptr<Token> returnType, std::unique_ptr<IdentifierExpression> identifier, const std::vector<std::unique_ptr<FunctionParameter>>& parameters, std::unique_ptr<BlockStatement> body)
				: Statement(StatementType::FunctionStatement, source), m_ReturnType(std::move(returnType)), m_Identifier(std::move(identifier)), m_Parameters(parameters), m_Body(std::move(body))
			{
			}

			inline const Token* GetReturnType() const { return m_ReturnType.get(); }
			inline const IdentifierExpression* GetIdentifier() const { return m_Identifier.get(); }
			inline const std::vector<std::unique_ptr<FunctionParameter>>& GetParameters() const { return m_Parameters; }
			inline const BlockStatement* GetBody() const { return m_Body.get(); }

		private:
			std::unique_ptr<Token> m_ReturnType;
			std::unique_ptr<IdentifierExpression> m_Identifier;
			std::vector<std::unique_ptr<FunctionParameter>> m_Parameters;
			std::unique_ptr<BlockStatement> m_Body;
		};
	}
}
