#pragma once

#include "Eye/AST/Statements/Statement.h"

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
			ContinueStatement(const EyeSource& source)
				: Statement(StatementType::ContinueStatement, source)
			{
			}
		};
	}
}
