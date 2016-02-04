#pragma once

#include "IHTTP.h"

#include <mongoose.h>

namespace SamEngine
{
    class HTTP : public IHTTP
    {
    public:
        virtual void Initialize() override;

        virtual void Finalize() override;

        virtual bool Available() override;

        virtual DataPtr Read(const std::string &path) override;

    private:
        static void EventHandle(struct mg_connection *connection, int event, void *eventData);

    private:
        bool mAvailable{ false };
        bool mPollFlag{ false };
        DataPtr mData{ nullptr };
        mg_mgr mManager;
    };
}