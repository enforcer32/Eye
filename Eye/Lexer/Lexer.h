#pragma once

#include "Eye/Common/Eye.h"

namespace EYE
{
	enum class LexerResult
	{
		Successful,
		Failed
	};

	class Lexer
	{
	public:
		LexerResult Tokenize(EyeInstance* eyeInstance);

	private:
		EyeInstance* m_EyeInstance;
	};
}
