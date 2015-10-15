#pragma once

#include "IStorage.h"

namespace SamEngine
{
    class Storage : public IStorage
    {
    public:
        DataPtr Read(const std::string &path) override;

        void Write(const std::string &path, DataPtr data) override;
    };

    inline STORAGE_API IStorage &GetStorage()
    {
        static Storage instance;
        return instance;
    }
}