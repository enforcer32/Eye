#include "Eye/Lexer/Lexer.h"

namespace EYE
{
	LexerResult Lexer::Tokenize(EyeInstance* eyeInstance)
	{
		m_EyeInstance = eyeInstance;
		return LexerResult::Successful;
	}
}
