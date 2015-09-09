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

        static resource_name shared(int32 signature = default_signatrue);

        static resource_name shared(const std::string &name, int32 signature = default_signatrue);

        static resource_name shared(const char *name, int32 signatrue = default_signatrue);

        void operator=(const resource_name &other);

        bool is_unique() const;

        bool operator<(const resource_name &other) const;

        bool operator==(const resource_name &other) const;

        bool operator!=(const resource_name &other) const;

        const std::string &get_name() const;

        size_t hash() const;

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
        resource_name instance;
        instance.name = name;
        instance.signature = unique_signatrue;
        return instance;
    }

    inline resource_name resource_name::unique(const char *name)
    {
        resource_name instance;
        instance.name = name;
        instance.signature = unique_signatrue;
        return instance;
    }

    inline resource_name resource_name::shared(int32 signature)
    {
        s_assert(signature != unique_signatrue);
        resource_name instance;
        instance.signature = signature;
        return instance;
    }

    inline resource_name resource_name::shared(const std::string &name, int32 signature)
    {
        s_assert(signature != unique_signatrue);
        resource_name instance;
        instance.name = name;
        instance.signature = signature;
        return instance;
    }

    inline resource_name resource_name::shared(const char *name, int32 signature)
    {
        s_assert(signature != unique_signatrue);
        resource_name instance;
        instance.name = name;
        instance.signature = signature;
        return instance;
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

    inline size_t resource_name::hash() const
    {
        return std::hash<std::string>()(name) ^ std::hash<int32>()(signature);
    }
}

namespace std
{
    template<>
    struct hash<sam::resource_name>
    {
        size_t operator()(const sam::resource_name &other) const
        {
            return other.hash();
        }
    };
}