#pragma once

#include "EYEAST/Statements/Statement.h"

namespace Eye
{
	namespace AST
	{
		/*
			ContinueStatement
				: 'continue' ';'
				;
		*/
		class ContinueStatement : public Statement
		{
		public:
			ContinueStatement(const Types::Location& source)
				: Statement(StatementType::ContinueStatement, source)
			{
			}
		};
	}
}
