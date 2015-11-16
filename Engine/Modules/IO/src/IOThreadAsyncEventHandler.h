#pragma once

#include "IOEventHandler.h"

namespace SamEngine
{
    class IOThreadAsyncEventHandler : public IOEventHandler, public ThreadAsyncEventHandler
    {
    public:
        CREATE_FUNC_DECLARE(IOThreadAsyncEventHandler)

        IOThreadAsyncEventHandler();

        bool Handle(const EventPtr event) override;

    protected:
        void EnterThread() override;

        void ExitThread() override;
    };

    typedef std::shared_ptr<IOThreadAsyncEventHandler> IOThreadAsyncEventHandlerPtr;
}