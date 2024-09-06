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
			IterationStatement(IterationStatementType iterationType, const Utility::EyeSource& source)
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
			WhileStatement(const Utility::EyeSource& source, const std::shared_ptr<Expression>& condition, const std::shared_ptr<Statement>& body)
				: IterationStatement(IterationStatementType::WhileStatement, source), m_Condition(condition), m_Body(body)
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
			DoWhileStatement(const Utility::EyeSource& source, const std::shared_ptr<Expression>& condition, const std::shared_ptr<Statement>& body)
				: IterationStatement(IterationStatementType::DoWhileStatement, source), m_Condition(condition), m_Body(body)
			{
			}

			inline std::shared_ptr<Expression> GetCondition() const { return m_Condition; }
			inline std::shared_ptr<Statement> GetBody() const { return m_Body; }

		private:
			std::shared_ptr<Expression> m_Condition;
			std::shared_ptr<Statement> m_Body;
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
			ForStatement(const Utility::EyeSource& source, const std::shared_ptr<void>& initializer, ForInitializerType initializerType, const std::shared_ptr<Expression>& condition, const std::shared_ptr<Expression>& update, const std::shared_ptr<Statement>& body)
				: IterationStatement(IterationStatementType::ForStatement, source), m_Initializer(initializer), m_InitializerType(initializerType), m_Condition(condition), m_Update(update), m_Body(body)
			{
			}

			template<typename T>
			inline std::shared_ptr<T> GetInitializer() const
			{
				static_assert(std::is_same_v<T, VariableStatement> || std::is_same_v<T, Expression>, "EYEAST->IterationStatement->ForStatement->Error GetInitializer() Invalid Typename");
				return std::static_pointer_cast<T>(m_Initializer);
			}

			inline ForInitializerType GetInitializerType() const { return m_InitializerType; }
			inline std::shared_ptr<Expression> GetCondition() const { return m_Condition; }
			inline std::shared_ptr<Expression> GetUpdate() const { return m_Update; }
			inline std::shared_ptr<Statement> GetBody() const { return m_Body; }

		private:
			std::shared_ptr<void> m_Initializer;
			ForInitializerType m_InitializerType;
			std::shared_ptr<Expression> m_Condition;
			std::shared_ptr<Expression> m_Update;
			std::shared_ptr<Statement> m_Body;
		};
	}
}
