#pragma once

#include "Eye/AST/Statements/Statement.h"

namespace Eye
{
	namespace AST
	{
		/*
			BreakStatement
				: 'break' ';'
				;
		*/
		class BreakStatement : public Statement
		{
		public:
			BreakStatement(const EyeSource& source)
				: Statement(StatementType::BreakStatement, source)
			{
			}
		};
	}
}
