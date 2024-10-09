#pragma once

#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Expressions/Expression.h"
#include "Eye/AST/Expressions/IdentifierExpression.h"

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
			VariableDeclaration(std::unique_ptr<IdentifierExpression> identifier, std::unique_ptr<Expression> initializer)
				: m_Identifier(std::move(identifier)), m_Initializer(std::move(initializer))
			{
			}

			inline const IdentifierExpression* GetIdentifier() const { return m_Identifier.get(); }
			inline Expression* GetInitializer() const { return m_Initializer.get(); }

		private:
			std::unique_ptr<IdentifierExpression> m_Identifier;
			std::unique_ptr<Expression> m_Initializer;
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
			VariableStatement(const EyeSource& source, std::unique_ptr<Token> typeQualifier, std::unique_ptr<Token> dataType, std::vector<std::unique_ptr<VariableDeclaration>>&& variableDeclarationList)
				: Statement(StatementType::VariableStatement, source), m_TypeQualifier(std::move(typeQualifier)), m_DataType(std::move(dataType)), m_VariableDeclarationList(std::move(variableDeclarationList))
			{
			}

			inline const Token* GetTypeQualifier() const { return m_TypeQualifier.get(); }
			inline const Token* GetDataType() const { return m_DataType.get(); }
			inline const std::vector<std::unique_ptr<VariableDeclaration>>& GetVariableDeclarationList() const { return m_VariableDeclarationList; }

		private:
			std::unique_ptr<Token> m_TypeQualifier;
			std::unique_ptr<Token> m_DataType;
			std::vector<std::unique_ptr<VariableDeclaration>> m_VariableDeclarationList;
		};
	}
}
