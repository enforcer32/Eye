#pragma once

#include "EYEAST/Statements/Statement.h"
#include "EYEAST/Expressions/Expression.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		enum class IterationStatementType
		{
			WhileStatement,
			DoWhileStatement,
			ForStatement,
		};

		/*
			IterationStatement
				: WhileStatement
				| DoWhileStatement
				| ForStatement
				;
		*/
		class IterationStatement : public Statement
		{
		public:
			IterationStatement(IterationStatementType iterationType)
				: Statement(StatementType::IterationStatement), m_IterationType(iterationType)
			{
			}

			inline IterationStatementType GetIterationType() const { return m_IterationType; }

		private:
			IterationStatementType m_IterationType;
		};

		/*
			WhileStatement
				: 'while' '(' Expression ')' Statement
				;
		*/
		class WhileStatement : public IterationStatement
		{
		public:
			WhileStatement(const std::shared_ptr<Expression>& condition, const std::shared_ptr<Statement>& body)
				: IterationStatement(IterationStatementType::WhileStatement), m_Condition(condition), m_Body(body)
			{
			}

			inline std::shared_ptr<Expression> GetCondition() const { return m_Condition; }
			inline std::shared_ptr<Statement> GetBody() const { return m_Body; }

		private:
			std::shared_ptr<Expression> m_Condition;
			std::shared_ptr<Statement> m_Body;
		};

		/*
			DoWhileStatement
				: 'do' Statement 'while' '(' Expression ')' ';'
				;
		*/
		class DoWhileStatement : public IterationStatement
		{
		public:
			DoWhileStatement(const std::shared_ptr<Expression>& condition, const std::shared_ptr<Statement>& body)
				: IterationStatement(IterationStatementType::DoWhileStatement), m_Condition(condition), m_Body(body)
			{
			}

			inline std::shared_ptr<Expression> GetCondition() const { return m_Condition; }
			inline std::shared_ptr<Statement> GetBody() const { return m_Body; }

		private:
			std::shared_ptr<Expression> m_Condition;
			std::shared_ptr<Statement> m_Body;
		};
	}
}
