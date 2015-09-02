#pragma once

#include <core/assert.h>
#include <core/types.h>

#include <string>

namespace sam
{
    class resource_name
    {
    public:
        static resource_name unique();

        static resource_name unique(const std::string &name);

        static resource_name unique(const char *name);

        resource_name(int32 signature = default_signatrue);

        resource_name(const std::string &name, int32 signature = default_signatrue);

        resource_name(const char *name, int32 signatrue = default_signatrue);

        void operator=(const resource_name &other);

        bool is_unique() const;

        bool operator<(const resource_name &other) const;

        bool operator==(const resource_name &other) const;

        bool operator!=(const resource_name &other) const;

        const std::string &get_name() const;

    private:
        static const int32 default_signatrue = 0x7fffffff;
        static const int32 unique_signatrue = 0xffffffff;
        std::string name;
        int32 signature{ default_signatrue };
    };

    inline resource_name resource_name::unique()
    {
        resource_name instance;
        instance.signature = unique_signatrue;
        return instance;
    }

    inline resource_name resource_name::unique(const std::string &name)
    {
        resource_name instance(name);
        instance.signature = unique_signatrue;
        return instance;
    }

    inline resource_name resource_name::unique(const char *name)
    {
        resource_name instance(name);
        instance.signature = unique_signatrue;
        return instance;
    }

    inline resource_name::resource_name(int32 signature) :
        signature(signature)
    {
        s_assert(signature != unique_signatrue);
    }

    inline resource_name::resource_name(const std::string &name, int32 signature) :
        name(name),
        signature(signature)
    {
        s_assert(signature != unique_signatrue);
    }

    inline resource_name::resource_name(const char *name, int32 signatrue) :
        name(name),
        signature(signature)
    {
        s_assert(signature != unique_signatrue);
    }

    inline void resource_name::operator=(const resource_name &other)
    {
        name = other.name;
        signature = other.signature;
    }

    inline bool resource_name::is_unique() const
    {
        return signature == unique_signatrue;
    }

    inline bool resource_name::operator<(const resource_name &other) const
    {
        return signature < other.signature || name < other.name;
    }

    inline bool resource_name::operator==(const resource_name &other) const
    {
        return signature == other.signature && name == other.name;
    }

    inline bool resource_name::operator!=(const resource_name &other) const
    {
        return signature != other.signature || name != other.name;
    }

    inline const std::string &resource_name::get_name() const
    {
        return name;
    }
}
