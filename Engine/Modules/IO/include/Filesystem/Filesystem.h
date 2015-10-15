#pragma once

#include <EventModule.h>

#include <functional>
#include <memory>

#define FS_CREATOR_DECLARE(clazz) \
    static FilesystemPtr Creator() \
    { \
       return std::static_pointer_cast<Filesystem>(std::make_shared<clazz>()); \
    }

namespace SamEngine
{
    class IO_API Filesystem : public IEventHandler
    {
    public:
        typedef std::function<std::shared_ptr<Filesystem>()> Creator;
    };

    typedef std::shared_ptr<Filesystem> FilesystemPtr;
}