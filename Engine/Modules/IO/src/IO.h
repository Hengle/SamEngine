#pragma once

#include "IIO.h"
#include "IOThreadAsyncEventHandler.h"

#include <unordered_map>

namespace SamEngine
{
    class IO : public IIO, public ITick
    {
    public:
        virtual void Initialize(int32 threadCount = 8) override;

        virtual void Finalize() override;

        virtual bool Available() override;

        virtual DataPtr Read(const std::string &file) override;

        virtual void Write(const std::string &file, DataPtr data) override;

        virtual void AsyncRead(const std::string &file, IOCallbackFunction callback) override;

        virtual void AsyncWrite(const std::string &file, DataPtr data, IOCallbackFunction callback = nullptr) override;

        virtual void SetLocationPlaceholder(const std::string &original, const std::string &replacement) override;

        virtual void SetFilesystemCreator(const std::string &name, Filesystem::Creator function = nullptr) override;

        virtual Location ResolveLocation(const std::string &file) override;

        virtual Filesystem::Creator GetFilesystemCreator(const std::string &name) override;

        virtual void SetRouterFunction(IORouterFunction function) override;

        virtual IORouterFunction GetRouterFunction() override;

        virtual void Tick(TickCount now, TickCount delta) override;

    protected:
        void AsyncHandle(EventPtr event, IOCallbackFunction function);

    private:
        bool mValid{ false };

        uint32 mCurrentThread{ 0 };

        IORouterFunction mRouterFunction{ nullptr };

        TickID mTickID{ InvalidTickID };

        std::unordered_map<std::string, std::string> mLocationPlaceholder;

        std::unordered_map<std::string, Filesystem::Creator> mFilesystemCreatorRegistery;

        IOEventHandlerPtr mEventHandler{ nullptr };

        std::vector<IOThreadAsyncEventHandlerPtr> mAsyncEventHandlers;

        std::vector<EventPtr> mHandlingEvents;

        std::unordered_map<EventPtr, IOCallbackFunction> mEvent2Callback;
    };
}