#include "Eye/Common/Eye.h"
#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Util/FileIO.h"
#include "Eye/Util/Logger.h"

namespace EYE
{
	EyeResult Eye::Run(const EyeProperties& properties)
	{
		m_Properties = properties;

		// Setup
		m_EyeInstance = new EyeInstance;
		m_EyeInstance->InFilePath = m_Properties.FilePath;
		m_EyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(m_Properties.FilePath));

		// Lexer
		Lexer lexer;
		if (lexer.Tokenize(m_EyeInstance) != LexerResult::Successful)
		{
			EYE_LOG_ERROR("EYEParser Failed!");
			return EyeResult::Failed;
		}
		//lexer.DebugPrintTokens();

		// Parser
		Parser parser;
		if (parser.Parse(m_EyeInstance) != ParserResult::Successful)
		{
			EYE_LOG_ERROR("EYEParser Failed!");
			return EyeResult::Failed;
		}
		parser.DebugPrintNodes();

		return EyeResult::Successful;
	}
}
