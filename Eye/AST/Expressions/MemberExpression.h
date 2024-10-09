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
			MemberExpression(const EyeSource& source, std::unique_ptr<Expression> object, std::unique_ptr<Expression> property, bool computed)
				: Expression(ExpressionType::MemberExpression, source), m_Object(std::move(object)), m_Property(std::move(property)), m_Computed(computed)
			{
			}

			inline const Expression* GetObject() const { return m_Object.get(); }
			inline const Expression* GetProperty() const { return m_Property.get(); }
			inline bool IsComputed() const { return m_Computed; }

		private:
			std::unique_ptr<Expression> m_Object;
			std::unique_ptr<Expression> m_Property;
			bool m_Computed;
		};
	}
}
