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
			ContinueStatement(const Utility::EyeSource& source)
				: Statement(StatementType::ContinueStatement, source)
			{
			}
		};
	}
}
