#pragma once

#include "EYEUtility/Platform.h"
#include "EYEUtility/Logger.h"

#if defined EYE_DEBUG
	#ifdef EYE_PLATFORM_WINDOWS
		#define EYE_DEBUGBREAK() __debugbreak()	
	#else
		#error "Platform doesnt support debugbreak"
	#endif
	#define EYE_ENABLE_ASSERTS
#else
	#define EYE_DEBUGBREAK()
#endif

#ifdef EYE_ENABLE_ASSERTS
	#define EYE_ASSERT(x, msg) { if(!(x)) { EYE_LOG_ERROR("Assertion Error: {}, File: {}, Line: {}", msg, __FILE__, __LINE__); EYE_DEBUGBREAK(); } }
#else
	#define EYE_ASSERT(...)
#endif
