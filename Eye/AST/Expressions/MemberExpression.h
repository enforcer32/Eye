#pragma once

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/Lexer/Token.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			MemberExpression
				: PrimaryExpression
				| MemberExpression '.' Identifier
				| MemberExpression '[' Expression ']'
				;
		*/
		class MemberExpression : public Expression
		{
		public:
			MemberExpression(const EyeSource& source, const std::shared_ptr<Expression>& object, const std::shared_ptr<Expression>& property, bool computed)
				: Expression(ExpressionType::MemberExpression, source), m_Object(object), m_Property(property), m_Computed(computed)
			{
			}

			inline std::shared_ptr<Expression> GetObject() const { return m_Object; }
			inline std::shared_ptr<Expression> GetProperty() const { return m_Property; }
			inline bool IsComputed() const { return m_Computed; }

		private:
			std::shared_ptr<Expression> m_Object;
			std::shared_ptr<Expression> m_Property;
			bool m_Computed;
		};
	}
}
