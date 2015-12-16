#pragma once

#include "IStorage.h"

namespace SamEngine
{
    class Storage : public IStorage
    {
    public:
        virtual DataPtr Read(const std::string &path) override;

        virtual void Write(const std::string &path, DataPtr data) override;
    };
}