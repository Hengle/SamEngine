#pragma once

#include "log.h"

#if defined(SAM_WIN32)
#   define SAM_TRAP __debugbreak
#else
#   define SAM_TRAP __builtin_trap
#endif

#if !__GNUC__
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#if DEBUG
#   define s_assert(condition) do { if (!(condition)) { sam::log::assert(#condition, nullptr, __FILE__, __LINE__, __PRETTY_FUNCTION__); SAM_TRAP(); } } while(0)
#   define s_assert_msg(condition, message) do { if (!(condition)) { sam::log::assert(#condition, message, __FILE__, __LINE__, __PRETTY_FUNCTION__); SAM_TRAP(); } } while(0)
#   define s_assert_range(value, min, max) s_assert_msg((value >= min) && (value <= max), "out of range")
#	define s_static_assert(condition) static_assert((condition))
#	define s_static_assert_range(value, min, max) s_static_assert((value >= min) && (value <= max))
#	define s_error(...) do { sam::log::error(__VA_ARGS__); SAM_TRAP(); } while(0)
#else
#   define s_assert(condition) ((void)0)
#   define s_assert_msg(condition, message) ((void)0)
#   define s_assert_range(value, min, max) ((void)0)
#	define s_static_assert(condition) ((void)0)
#	define s_static_assert_range(value, min, max) ((void)0)
#	define s_error(...) do { exit(-1); } while(0)
#endif