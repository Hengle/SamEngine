#pragma once

#include "IHTTP.h"

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
        bool mAvailable{ false };
    };
}