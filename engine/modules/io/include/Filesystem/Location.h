#pragma once

#include <CoreModule.h>

#include <string>

namespace SamEngine
{
    class IO_API Location
    {
    public:
        Location();

        Location(const char *c_str);

        Location(const std::string &string);

        Location(const Location &other);

        Location(Location &&other);

        void operator=(const char *c_str);

        void operator=(const std::string &string);

        void operator=(const Location &other);

        void operator=(Location &&other);

        bool operator==(const char *c_str) const;

        bool operator==(const std::string &string) const;

        bool operator==(const Location &other) const;

        std::string GetFilesystemName() const;

        std::string GetPath() const;

        const std::string &GetRaw() const;

    protected:
        std::string mRawString;
    };

    inline Location::Location()
    {
    }

    inline Location::Location(const char *c_str) :
        mRawString(c_str)
    {
    }

    inline Location::Location(const std::string &string) :
        mRawString(string)
    {
    }

    inline Location::Location(const Location &other) :
        mRawString(other.mRawString)
    {
    }

    inline Location::Location(Location &&other)
    {
        mRawString = std::move(other.mRawString);
    }

    inline void Location::operator=(const char *c_str)
    {
        mRawString = c_str;
    }

    inline void Location::operator=(const std::string &string)
    {
        mRawString = string;
    }

    inline void Location::operator=(const Location &other)
    {
        mRawString = other.mRawString;
    }

    inline void Location::operator=(Location &&other)
    {
        mRawString = std::move(other.mRawString);
    }

    inline bool Location::operator==(const char *c_str) const
    {
        return mRawString == c_str;
    }

    inline bool Location::operator==(const std::string &string) const
    {
        return mRawString == string;
    }

    inline bool Location::operator==(const Location &other) const
    {
        return mRawString == other.mRawString;
    }

    inline std::string Location::GetFilesystemName() const
    {
        s_assert(mRawString.find("://") != std::string::npos);
        return mRawString.substr(0, mRawString.find("://"));
    }

    inline std::string Location::GetPath() const
    {
        s_assert(mRawString.find("://") != std::string::npos);
        return mRawString.substr(mRawString.find("://") + 3);
    }

    inline const std::string& Location::GetRaw() const
    {
        return mRawString;
    }
}