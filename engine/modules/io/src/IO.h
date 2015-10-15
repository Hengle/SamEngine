#pragma once

#include "IIO.h"
#include "IOThreadAsyncEventHandler.h"

#include <unordered_map>

namespace SamEngine
{
    class IO : public IIO, public ITick
    {
    public:
        void Initialize(int32 threadCount = 8) override;

        void Finalize() override;

        bool Available() override;

        void Read(const std::string &file, IOCallbackFunction callback) override;

        void Write(const std::string &file, const DataPtr &data, IOCallbackFunction callback = nullptr) override;

        void SetLocationPlaceholder(const std::string &original, const std::string &replacement) override;

        void SetFilesystemCreator(const std::string &name, Filesystem::Creator function = nullptr) override;

        Filesystem::Creator GetFilesystemCreator(const std::string &name) override;

        void SetRouterFunction(IORouterFunction function) override;

        IORouterFunction GetRouterFunction() override;

        void Tick(TickCount now, TickCount delta) override;

    protected:
        void Handle(const EventPtr &event, IOCallbackFunction function);

    private:
        bool mValid{ false };

        uint32 mCurrentThread{ 0 };

        IORouterFunction mRouterFunction{ nullptr };

        TickID mTickID{ InvalidTickID };

        std::unordered_map<std::string, std::string> mLocationPlaceholder;

        std::unordered_map<std::string, Filesystem::Creator> mFilesystemCreatorRegistery;

        std::vector<IOThreadAsyncEventHandlerPtr> mThreads;

        std::vector<EventPtr> mHandlingEvents;

        std::unordered_map<EventPtr, IOCallbackFunction> mEvent2Callback;

        
    };

    inline IO_API IIO &GetIO()
    {
        static IO instance;
        return instance;
    }
}