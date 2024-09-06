#pragma once

#include "EYEAST/Statements/Statement.h"

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
			BreakStatement(const Utility::EyeSource& source)
				: Statement(StatementType::BreakStatement, source)
			{
			}
		};
	}
}
