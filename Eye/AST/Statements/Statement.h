#pragma once

#include "Eye/Utility/EyeSource.h"

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
			inline const EyeSource& GetSource() const { return m_Source; }

		protected:
			Statement(StatementType type, const EyeSource& source)
				: m_Type(type), m_Source(source)
			{
			}

		private:
			StatementType m_Type;
			EyeSource m_Source;
		};
	}
}
