#pragma once

#include "pool.h"

#include <memory>

#define CREATE_FUNC_DECLARE(clazz) \
    template<typename... ARGS> \
    static std::shared_ptr<clazz> create(ARGS &&... args) \
    { \
        return std::make_shared<clazz>(std::forward<ARGS>(args)...); \
    }

#define POOL_DECLARE(clazz) static pool<clazz> clazz##_pool;

#define POOL_IMPLEMENT(clazz) pool<clazz> clazz::clazz##_pool;

#define POOL_CREATE_FUNC_DECLARE(clazz) \
    template<typename... ARGS> \
    static std::shared_ptr<clazz> create(ARGS &&... args) \
    { \
        return clazz##_pool.create(std::forward<ARGS>(args)...); \
    }


#if defined(SAM_APPLE) || defined(SAM_MINGW)
namespace std
{
    template <typename TYPE, typename... Args>
    std::unique_ptr<TYPE> make_unique(Args &&... args)
    {
        return std::unique_ptr<TYPE>(new TYPE(std::forward<Args>(args)...));
    }
}
#endif
