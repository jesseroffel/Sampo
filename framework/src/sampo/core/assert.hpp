#pragma once
#include <assert.h>

#if SAMPO_COMPILER_VISUALSTUDIO
	#define SAMPO_DEBUG_BREAK() __debugbreak()
#else
	#error Assert not supported on this platform yet
#endif 

__forceinline void Sampo_Assert(const char* aExprString, const char* aFile, int aLine, const char* aString)
{
	std::cerr << "Assert failed:\t" << aString << "\n" << "Expected:\t" << aExprString << "\n" << "Occurance:\t" << aFile << ", line " << aLine << "\n";
	SAMPO_DEBUG_BREAK();
}

#define SAMPO_ASSERT_IMPL(Expr) \
	if (Expr) {} \
	else \
	{ \
		SAMPO_DEBUG_BREAK(); \
	}

#define SAMPO_ASSERT_MSG_IMPL(Expr, Msg) \
	if (Expr) { } \
	else \
	{ \
		Sampo_Assert(#Expr, __FILE__, __LINE__, Msg); \
	}

#if SAMPO_ASSERT_ENABLED
	#define SAMPO_ASSERT(X)				SAMPO_ASSERT_IMPL(X);
	#define SAMPO_ASSERT_MSG(X, Msg)	SAMPO_ASSERT_MSG_IMPL(X, Msg);
#else
	#define SAMPO_ASSERT(X)				(static_cast<void>(0))
	#define SAMPO_ASSERT_MSG(X, Msg)	(static_cast<void>(0))
#endif // SAMPO_ASSERT_ENABLED