#pragma once

#include <EYETypes/Location.h>

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
				;
		*/
		class Statement
		{
		public:
			inline StatementType GetType() const { return m_Type; }
			inline const Types::Location& GetSource() const { return m_Source; }

		protected:
			Statement(StatementType type, const Types::Location& source)
				: m_Type(type), m_Source(source)
			{
			}

		private:
			StatementType m_Type;
			Types::Location m_Source;
		};
	}
}
