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
				: DatatypeKeyword VariableDeclarationList ';'
				;

			VariableDeclarationList
				: VariableDeclaration
				| VariableDeclarationList ',' VariableDeclaration
				;

			DatatypeKeyword
				: 'auto'
				| 'int'
				| 'float'
				| 'str'
				| 'bool'
				;
		*/
		class VariableStatement : public Statement
		{
		public:
			VariableStatement(Lexer::Token dataType, const std::vector<std::shared_ptr<VariableDeclaration>>& variableDeclarationList)
				: Statement(StatementType::VariableStatement), m_DataType(dataType), m_VariableDeclarationList(variableDeclarationList)
			{
			}

			inline Lexer::Token GetDataType() const { return m_DataType; }
			inline const std::vector<std::shared_ptr<VariableDeclaration>>& GetVariableDeclarationList() const { return m_VariableDeclarationList; }

		private:
			Lexer::Token m_DataType;
			std::vector<std::shared_ptr<VariableDeclaration>> m_VariableDeclarationList;
		};
	}
}
