#pragma once

namespace Eye
{
	namespace AST
	{
		enum class StatementType
		{
			ExpressionStatement,
			BlockStatement,
			VariableStatement,
			ControlStatement,
			IterationStatement,
			ContinueStatement,
			BreakStatement,
			FunctionStatement,
			ReturnStatement,
			StructStatement,
		};

		/*
			Statement
				: ExpressionStatement
				| BlockStatement
				| VariableStatement
				| ControlStatement
				| IterationStatement
				| ContinueStatement
				| BreakStatement
				| FunctionStatement
				| ReturnStatement
				| StructStatement
				;
		*/
		class Statement
		{
		public:
			inline StatementType GetType() const { return m_Type; }

		protected:
			Statement(StatementType type)
				: m_Type(type)
			{
			}

		private:
			StatementType m_Type;
		};
	}
}
