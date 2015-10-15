#pragma once

#include <memory>

#define CREATE_FUNC_DECLARE(clazz) \
    template<typename... ARGS> \
    static std::shared_ptr<clazz> Create(ARGS &&... args) \
    { \
        return std::make_shared<clazz>(std::forward<ARGS>(args)...); \
    }

#if SAM_OSX || SAM_MINGW
namespace std
{
    template <typename TYPE, typename... Args>
    std::unique_ptr<TYPE> make_unique(Args &&... args)
    {
        return std::unique_ptr<TYPE>(new TYPE(std::forward<Args>(args)...));
    }
}
#endif
