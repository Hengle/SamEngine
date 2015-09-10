#pragma once

#include <io/filesystem/filesystem.h>

namespace sam
{
    class http_filesystem : public filesystem
    {
    public:
        FS_CREATOR_DECLARE(http_filesystem)

        virtual ~http_filesystem() {}

        virtual bool handle(const event_ptr &e) override;
    };
}