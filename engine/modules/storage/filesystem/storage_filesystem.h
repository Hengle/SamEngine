#pragma once

#include "io/filesystem/filesystem.h"

#include "io/event/io_request_location_event.h"

namespace sam
{
    class storage_filesystem : public filesystem
    {
    public:
        FS_CREATOR_DECLARE(storage_filesystem)

        storage_filesystem();

        virtual ~storage_filesystem();

        virtual bool dispatch(const event_ptr &e) override;

        virtual void handle() override;

        bool available();

    private:
        io_request_location_event_ptr e;
    };
}