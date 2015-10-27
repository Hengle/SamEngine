#pragma once

#include <IOModule.h>

namespace SamEngine
{
    class StorageFilesystem : public Filesystem
    {
    public:
        FS_CREATOR_DECLARE(StorageFilesystem)

        bool Handle(const EventPtr &event) override;
    };
}