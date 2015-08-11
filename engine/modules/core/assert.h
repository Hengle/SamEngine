#pragma once

#include "log.h"

#if defined(_WIN32)
#   define SAM_TRAP __debugbreak
#else
#   define SAM_TRAP __builtin_trap
#endif

#if !__GNUC__
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#if DEBUG || _DEBUG
#   define s_assert(condition) do { if (!(condition)) { sam::log::assert(#condition, nullptr, __FILE__, __LINE__, __PRETTY_FUNCTION__); SAM_TRAP(); } } while(0)
#   define s_assert_msg(condition, message) do { if (!(condition) { sam::log::assert(#condition, message, __FILE__, __LINE__, __PRETTY_FUNCTION__); SAM_TRAP(); } } while(0)
#   define s_assert_range(value, min, max) s_assert_msg(((value >= min) && (value <= max)), "out of range")
#else
#   define s_assert(condition) ((void)0)
#   define s_assert_msg(condition, message) ((void)0)
#   define s_assert_range(value, min, max) ((void)0)
#endif