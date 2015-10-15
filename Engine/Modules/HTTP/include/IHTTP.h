#pragma once

#include <CoreModule.h>
#include <IOModule.h>

#include <string>

namespace SamEngine
{
    class HTTP_API IHTTP
    {
    public:
        virtual ~IHTTP() {}

        virtual void Initialize() = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual DataPtr Read(const std::string &path) = 0;
    };

    extern HTTP_API IHTTP &GetHTTP();

    extern HTTP_API Filesystem::Creator GetHTTPFilesystemCreator();
}