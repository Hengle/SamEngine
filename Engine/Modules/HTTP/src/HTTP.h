#pragma once

#include "IHTTP.h"

namespace SamEngine
{
    class HTTP : public IHTTP
    {
    public:
        void Initialize() override;

        void Finalize() override;

        bool Available() override;

        DataPtr Read(const std::string &path) override;

    private:
        bool mAvailable{ false };
    };
}