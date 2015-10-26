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

        const std::string &GetFilesystemName() const;

        const std::string &GetPath() const;

        const std::string &GetRaw() const;

    private:
        void update();

    protected:
        std::string mRawString;
        std::string mFilesystemName;
        std::string mPath;
    };

    inline Location::Location()
    {
    }

    inline Location::Location(const char *c_str) :
        mRawString(c_str)
    {
        update();
    }

    inline Location::Location(const std::string &string) :
        mRawString(string)
    {
        update();
    }

    inline Location::Location(const Location &other) :
        mRawString(other.mRawString),
        mFilesystemName(other.mFilesystemName),
        mPath(other.mPath)
    {
    }

    inline Location::Location(Location &&other)
    {
        mRawString = std::move(other.mRawString);
        mFilesystemName = std::move(other.mFilesystemName);
        mPath = std::move(other.mPath);
    }

    inline void Location::operator=(const char *c_str)
    {
        mRawString = c_str;
        update();
    }

    inline void Location::operator=(const std::string &string)
    {
        mRawString = string;

        update();
    }

    inline void Location::operator=(const Location &other)
    {
        mRawString = other.mRawString;
        mFilesystemName = other.mFilesystemName;
        mPath = other.mPath;
    }

    inline void Location::operator=(Location &&other)
    {
        mRawString = std::move(other.mRawString);
        mFilesystemName = std::move(other.mFilesystemName);
        mPath = std::move(other.mPath);
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

    inline const std::string &Location::GetFilesystemName() const
    {
        return mFilesystemName;
    }

    inline const std::string &Location::GetPath() const
    {
        return mPath;
    }

    inline const std::string &Location::GetRaw() const
    {
        return mRawString;
    }

    inline void Location::update()
    {
        s_assert(mRawString.find("://") != std::string::npos);
        mFilesystemName = mRawString.substr(0, mRawString.find("://"));
        mPath = mRawString.substr(mRawString.find("://") + 3);
    }
}