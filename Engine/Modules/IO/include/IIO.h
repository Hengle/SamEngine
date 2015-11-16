#pragma once

#include "Filesystem/Filesystem.h"
#include "Filesystem/Location.h"

#include <CoreModule.h>
#include <EventModule.h>

#include <functional>

namespace SamEngine
{
    typedef std::function<uint32(const EventPtr, uint32)> IORouterFunction;

    typedef std::function<void(EventPtr)> IOCallbackFunction;

    class IO_API IIO
    {
    public:
        virtual ~IIO() {}

        virtual void Initialize(int32 threadCount = 8) = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual DataPtr Read(const std::string &file) = 0;

        virtual void Write(const std::string &file, DataPtr data) = 0;

        virtual void AsyncRead(const std::string &file, IOCallbackFunction callback) = 0;

        virtual void AsyncWrite(const std::string &file, DataPtr data, IOCallbackFunction callback = nullptr) = 0;

        virtual void SetLocationPlaceholder(const std::string &original, const std::string &replacement) = 0;

        virtual void SetFilesystemCreator(const std::string &name, Filesystem::Creator function = nullptr) = 0;

        virtual Location ResolveLocation(const std::string &file) = 0;

        virtual Filesystem::Creator GetFilesystemCreator(const std::string &name) = 0;

        virtual void SetRouterFunction(IORouterFunction function) = 0;

        virtual IORouterFunction GetRouterFunction() = 0;
    };

    extern IO_API IIO &GetIO();
}
