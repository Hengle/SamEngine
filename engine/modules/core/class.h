#pragma once

#include <memory>

#define CREATE_FUNC_DECLARE(clazz) \
    template<typename... ARGS> \
    static std::shared_ptr<clazz> create(ARGS&&... args) \
    { \
        return std::make_shared<clazz>(std::forward<ARGS>(args)...); \
    }
