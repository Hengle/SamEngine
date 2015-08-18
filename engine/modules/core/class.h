#pragma once

#include <memory>

#define CREATE_FUNC_DECLARE(clazz) \
    template<typename... ARGS> \
    static std::shared_ptr<clazz> create(ARGS&&... args) \
    { \
        return std::make_shared<clazz>(std::forward<ARGS>(args)...); \
    }

#if defined(SAM_APPLE) || defined(SAM_MINGW)
namespace std
{
    template <typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif
