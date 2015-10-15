#pragma once

#include <CoreModule.h>

#include <string>
#include <unordered_map>

namespace SamEngine
{
    typedef uint32 ResourceSignature;

    enum : ResourceSignature
    {
        DefaultSignature = 0x7fffffff,
        UniqueSignature = 0xffffffff,
    };

    class RESOURCE_API ResourceName
    {
    public:
        static ResourceName Unique();

        static ResourceName Unique(const std::string &name);

        static ResourceName Unique(const char *name);

        static ResourceName Shared(ResourceSignature signature = DefaultSignature);

        static ResourceName Shared(const std::string &name, ResourceSignature signature = DefaultSignature);

        static ResourceName Shared(const char *name, ResourceSignature signatrue = DefaultSignature);

        void operator=(const ResourceName &other);

        bool IsUnique() const;

        bool operator<(const ResourceName &other) const;

        bool operator==(const ResourceName &other) const;

        bool operator!=(const ResourceName &other) const;

        const std::string &GetName() const;

        size_t Hash() const;

    private:
        std::string mName;
        ResourceSignature mSignature{ DefaultSignature };
    };

    inline ResourceName ResourceName::Unique()
    {
        ResourceName instance;
        instance.mSignature = UniqueSignature;
        return instance;
    }

    inline ResourceName ResourceName::Unique(const std::string &name)
    {
        ResourceName instance;
        instance.mName = name;
        instance.mSignature = UniqueSignature;
        return instance;
    }

    inline ResourceName ResourceName::Unique(const char *name)
    {
        ResourceName instance;
        instance.mName = name;
        instance.mSignature = UniqueSignature;
        return instance;
    }

    inline ResourceName ResourceName::Shared(ResourceSignature signature)
    {
        s_assert(signature != UniqueSignature);
        ResourceName instance;
        instance.mSignature = signature;
        return instance;
    }

    inline ResourceName ResourceName::Shared(const std::string &name, ResourceSignature signature)
    {
        s_assert(signature != UniqueSignature);
        ResourceName instance;
        instance.mName = name;
        instance.mSignature = signature;
        return instance;
    }

    inline ResourceName ResourceName::Shared(const char *name, ResourceSignature signature)
    {
        s_assert(signature != UniqueSignature);
        ResourceName instance;
        instance.mName = name;
        instance.mSignature = signature;
        return instance;
    }

    inline void ResourceName::operator=(const ResourceName &other)
    {
        mName = other.mName;
        mSignature = other.mSignature;
    }

    inline bool ResourceName::IsUnique() const
    {
        return mSignature == UniqueSignature;
    }

    inline bool ResourceName::operator<(const ResourceName &other) const
    {
        return mSignature < other.mSignature || mName < other.mName;
    }

    inline bool ResourceName::operator==(const ResourceName &other) const
    {
        return mSignature == other.mSignature && mName == other.mName;
    }

    inline bool ResourceName::operator!=(const ResourceName &other) const
    {
        return mSignature != other.mSignature || mName != other.mName;
    }

    inline const std::string &ResourceName::GetName() const
    {
        return mName;
    }

    inline size_t ResourceName::Hash() const
    {
        return std::hash<std::string>()(mName) ^ std::hash<int32>()(mSignature);
    }
}

namespace std
{
    template<>
    struct hash<SamEngine::ResourceName>
    {
        size_t operator()(const SamEngine::ResourceName &other) const
        {
            return other.Hash();
        }
    };
}