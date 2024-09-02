#pragma once

#include "EYEAST/Statements/Statement.h"
#include "EYEAST/Expressions/Expression.h"
#include "EYEAST/Expressions/IdentifierExpression.h"

#include <memory>
#include <vector>

namespace Eye
{
	namespace AST
	{
		/*
			VariableDeclaration
				: IdentifierExpression OptionalVariableInitializer
				;

			VariableInitializer
				: '=' AssignmentExpression
				;
		*/
		class VariableDeclaration
		{
		public:
			VariableDeclaration(const std::shared_ptr<IdentifierExpression>& identifier, const std::shared_ptr<Expression>& initializer)
				: m_Identifier(identifier), m_Initializer(initializer)
			{
			}

			inline std::shared_ptr<IdentifierExpression> GetIdentifier() const { return m_Identifier; }
			inline std::shared_ptr<Expression> GetInitializer() const { return m_Initializer; }

		private:
			std::shared_ptr<IdentifierExpression> m_Identifier;
			std::shared_ptr<Expression> m_Initializer;
		};

		/*
			VariableStatement
				: OptionalTypeQualifierKeyword DatatypeKeyword VariableDeclarationList ';'
				;

			VariableDeclarationList
				: VariableDeclaration
				| VariableDeclarationList ',' VariableDeclaration
				;

			TypeQualifierKeyword
				: 'const'
				;

			DatatypeKeyword
				: 'int'
				| 'float'
				| 'str'
				| 'bool'
				;
		*/
		class VariableStatement : public Statement
		{
		public:
			VariableStatement(const std::shared_ptr<Lexer::Token>& typeQualifier, const std::shared_ptr<Lexer::Token>& dataType, const std::vector<std::shared_ptr<VariableDeclaration>>& variableDeclarationList)
				: Statement(StatementType::VariableStatement), m_TypeQualifier(typeQualifier), m_DataType(dataType), m_VariableDeclarationList(variableDeclarationList)
			{
			}

			inline std::shared_ptr<Lexer::Token> GetTypeQualifier() const { return m_TypeQualifier; }
			inline std::shared_ptr<Lexer::Token> GetDataType() const { return m_DataType; }
			inline const std::vector<std::shared_ptr<VariableDeclaration>>& GetVariableDeclarationList() const { return m_VariableDeclarationList; }

		private:
			std::shared_ptr<Lexer::Token> m_TypeQualifier;
			std::shared_ptr<Lexer::Token> m_DataType;
			std::vector<std::shared_ptr<VariableDeclaration>> m_VariableDeclarationList;
		};
	}
}
