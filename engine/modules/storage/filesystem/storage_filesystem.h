#pragma once

#include "io/filesystem/filesystem.h"

namespace sam
{
    class storage_filesystem : public filesystem
    {
    public:
        FS_CREATOR_DECLARE(storage_filesystem)

        storage_filesystem();

        virtual ~storage_filesystem();

        virtual bool handle(const event_ptr &e) override;
    };
}