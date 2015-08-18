#pragma once

#include "event/handler.h"

#include <functional>
#include <memory>
#include <queue>

#define FS_CREATOR_DECLARE(clazz) \
    static filesystem_ptr creator() \
    { \
       return std::dynamic_pointer_cast<filesystem>(std::make_shared<clazz>()); \
    }

namespace sam
{
    class filesystem;

    typedef std::shared_ptr<filesystem> filesystem_ptr;

    class filesystem : public handler
    {
    public:
        typedef std::function<filesystem_ptr()> creator;
    };
}