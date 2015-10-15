#pragma once

#include <CoreModule.h>
#include <IOModule.h>

#include <string>

namespace SamEngine
{
    class STORAGE_API IStorage
    {
    public:
        virtual ~IStorage() {}

        virtual DataPtr Read(const std::string &path) = 0;

        virtual void Write(const std::string &path, DataPtr data) = 0;
    };

    extern STORAGE_API IStorage &GetStorage();

    extern STORAGE_API Filesystem::Creator GetStorageFilesystemCreator();
}