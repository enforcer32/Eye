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
			VariableStatement(const EyeSource& source, const std::shared_ptr<Token>& typeQualifier, const std::shared_ptr<Token>& dataType, const std::vector<std::shared_ptr<VariableDeclaration>>& variableDeclarationList)
				: Statement(StatementType::VariableStatement, source), m_TypeQualifier(typeQualifier), m_DataType(dataType), m_VariableDeclarationList(variableDeclarationList)
			{
			}

			inline std::shared_ptr<Token> GetTypeQualifier() const { return m_TypeQualifier; }
			inline std::shared_ptr<Token> GetDataType() const { return m_DataType; }
			inline const std::vector<std::shared_ptr<VariableDeclaration>>& GetVariableDeclarationList() const { return m_VariableDeclarationList; }

		private:
			std::shared_ptr<Token> m_TypeQualifier;
			std::shared_ptr<Token> m_DataType;
			std::vector<std::shared_ptr<VariableDeclaration>> m_VariableDeclarationList;
		};
	}
}
