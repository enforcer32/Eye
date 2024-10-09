#pragma once

#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Expressions/Expression.h"

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
			IterationStatement(IterationStatementType iterationType, const EyeSource& source)
				: Statement(StatementType::IterationStatement, source), m_IterationType(iterationType)
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
			WhileStatement(const EyeSource& source, std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body)
				: IterationStatement(IterationStatementType::WhileStatement, source), m_Condition(std::move(condition)), m_Body(std::move(body))
			{
			}

			inline const Expression* GetCondition() const { return m_Condition.get(); }
			inline const Statement* GetBody() const { return m_Body.get(); }

		private:
			std::unique_ptr<Expression> m_Condition;
			std::unique_ptr<Statement> m_Body;
		};

		/*
			DoWhileStatement
				: 'do' Statement 'while' '(' Expression ')' ';'
				;
		*/
		class DoWhileStatement : public IterationStatement
		{
		public:
			DoWhileStatement(const EyeSource& source, std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body)
				: IterationStatement(IterationStatementType::DoWhileStatement, source), m_Condition(std::move(condition)), m_Body(std::move(body))
			{
			}

			inline const Expression* GetCondition() const { return m_Condition.get(); }
			inline const Statement* GetBody() const { return m_Body.get(); }

		private:
			std::unique_ptr<Expression> m_Condition;
			std::unique_ptr<Statement> m_Body;
		};


		/*
			ForStatement
				: 'for' '(' OptionalForVariableInitializer ';' OptionalExpression ';' OptionalExpression ')' Statement
				;

			ForVariableInitializer
				: VariableStatement
				| Expression
				;
		*/
		enum class ForInitializerType
		{
			Null,
			VariableStatement,
			Expression
		};

		class ForStatement : public IterationStatement
		{
		public:
			ForStatement(const EyeSource& source, std::unique_ptr<void> initializer, ForInitializerType initializerType, std::unique_ptr<Expression> condition, std::unique_ptr<Expression> update, std::unique_ptr<Statement> body)
				: IterationStatement(IterationStatementType::ForStatement, source), m_Initializer(std::move(initializer)), m_InitializerType(initializerType), m_Condition(std::move(condition)), m_Update(std::move(update)), m_Body(std::move(body))
			{
			}

			template<typename T>
			inline const T* GetInitializer() const
			{
				static_assert(std::is_same_v<T, VariableStatement> || std::is_same_v<T, Expression>, "Eye->AST->IterationStatement->ForStatement->Error GetInitializer() Invalid Typename");
				return static_cast<T>(m_Initializer);
			}

			inline ForInitializerType GetInitializerType() const { return m_InitializerType; }
			inline const Expression* GetCondition() const { return m_Condition.get(); }
			inline const Expression* GetUpdate() const { return m_Update.get(); }
			inline const Statement* GetBody() const { return m_Body.get(); }

		private:
			std::unique_ptr<void> m_Initializer;
			ForInitializerType m_InitializerType;
			std::unique_ptr<Expression> m_Condition;
			std::unique_ptr<Expression> m_Update;
			std::unique_ptr<Statement> m_Body;
		};
	}
}
