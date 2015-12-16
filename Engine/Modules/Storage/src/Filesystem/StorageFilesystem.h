#pragma once

#include <IOModule.h>

namespace SamEngine
{
    class StorageFilesystem : public Filesystem
    {
    public:
        FS_CREATOR_DECLARE(StorageFilesystem)

        virtual bool Handle(const EventPtr event) override;
    };
}