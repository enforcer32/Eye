#pragma once

#include <memory>

namespace Eye
{
	namespace AST
	{
		enum class StatementType
		{
			Expression,
			Block,
			Variable,
			Control,
			Iteration,
			Function,
			Return,
			Struct,
			StructBlock,
		};

		/*
			Statement
				: ExpressionStatement
				| BlockStatement
				| VariableStatement
				| ControlStatement
				| IterationStatement
				| FunctionStatement
				| ReturnStatement
				| StructStatement
				;
		*/
		class Statement
		{
		public:
			virtual ~Statement() = default;
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
