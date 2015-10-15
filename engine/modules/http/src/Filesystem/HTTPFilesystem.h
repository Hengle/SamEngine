#pragma once

#include <IOModule.h>

namespace SamEngine
{
    class HTTPFilesystem : public Filesystem
    {
    public:
        FS_CREATOR_DECLARE(HTTPFilesystem)

        bool Handle(const EventPtr &event) override;
    };

    inline HTTP_API Filesystem::Creator GetHTTPFilesystemCreator()
    {
        return HTTPFilesystem::Creator;
    }
}