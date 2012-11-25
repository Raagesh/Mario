#pragma once

#include <Core/Macro/MacroCommon.h>

/*
Assertions
==========

Use one of
	TING_ASSERT(cond)
	TING_ASSERT_MESSAGE(cond, messageWithFormatSpecifiers, ...)
to, if TING_ASSERTS_ENABLED is defined, trigger assert-handling if cond evaluates to false.

If an assert-handler is specified via SetHandler, it is used.
Otherwise, the default assert-handler is used.

messageWithFormatSpecifiers, which is optional (set to nullptr if not using), can specify
format specifiers in the following varargs in printf style (http://www.cplusplus.com/reference/cstdio/printf/).

Use one of
	TING_VERIFY(cond)
	TING_VERIFY_MESSAGE(cond, messageWithFormatSpecifiers, ...)
to evaluate cond even if TING_ASSERTS_ENABLED is undefined (and the assert-handling is thus disabled).
This is useful when cond changes state.  e.g.:
	TING_VERIFY(PerformTask() > 3);

Use
	TING_ASSERT_FAIL(messageWithFormatSpecifiers, ...)
to always trigger the assert-handler.
This is the same as calling TING_ASSERT_MESSAGE(nullptr, messageWithFormatSpecifiers, ...).
*/

namespace Ting { namespace Core { namespace Assert
{
	enum FailBehavior
	{
		Halt,
		Continue,
	};

	typedef FailBehavior (*Handler)(
		const char* condition,
		const char* file,
		int line,
		const char* message);

	Handler GetHandler();
	void SetHandler(Handler newHandler);

	FailBehavior ReportFailure(
		const char* condition,
		const char* file,
		int line,
		const char* message, ...);
} } } // namespace Ting::Core::Assert

#define TING_HALT() TING_DEBUG_BREAK()

#ifdef TING_ASSERTS_ENABLED
	#define TING_ASSERT(cond) \
		TING_MACRO_BEGIN \
			if (!(cond)) \
			{ \
				if (Ting::Core::Assert::ReportFailure(#cond, __FILE__, __LINE__, nullptr) == Ting::Core::Assert::Halt) \
					TING_HALT(); \
			} \
		TING_MACRO_END

	#define TING_ASSERT_MESSAGE(cond, messageWithFormatSpecifiers, ...) \
		TING_MACRO_BEGIN \
			if (!(cond)) \
			{ \
				if (Ting::Core::Assert::ReportFailure(#cond, __FILE__, __LINE__, (messageWithFormatSpecifiers), __VA_ARGS__) == Ting::Core::Assert::Halt) \
					TING_HALT(); \
			} \
		TING_MACRO_END

	#define TING_ASSERT_FAIL(messageWithFormatSpecifiers, ...) \
		TING_MACRO_BEGIN \
			if (Ting::Core::Assert::ReportFailure(nullptr, __FILE__, __LINE__, (messageWithFormatSpecifiers), __VA_ARGS__) == Ting::Core::Assert::Halt) \
				TING_HALT(); \
		TING_MACRO_END

	#define TING_VERIFY(cond) TING_ASSERT(cond)
	#define TING_VERIFY_MESSAGE(cond, messageWithFormatSpecifiers, ...) TING_ASSERT_MESSAGE(cond, messageWithFormatSpecifiers, ##__VA_ARGS__)
#else
	#define TING_ASSERT(condition) \
		TING_MACRO_BEGIN \
			TING_UNUSED(condition); \
		TING_MACRO_END

	#define TING_ASSERT_MESSAGE(condition, messageWithFormatSpecifiers, ...) \
		TING_MACRO_BEGIN \
			TING_UNUSED(condition); \
			TING_UNUSED(messageWithFormatSpecifiers); \
		TING_MACRO_END

	#define TING_ASSERT_FAIL(messageWithFormatSpecifiers, ...) \
		TING_MACRO_BEGIN \
			TING_UNUSED(messageWithFormatSpecifiers); \
		TING_MACRO_END

	#define TING_VERIFY(cond) (void)(cond)

	#define TING_VERIFY_MESSAGE(cond, messageWithFormatSpecifiers, ...) \
		TING_MACRO_BEGIN \
			(void)(cond); \
			TING_UNUSED(messageWithFormatSpecifiers); \
		TING_MACRO_END
#endif