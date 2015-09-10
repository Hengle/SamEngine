#pragma once

#include <core/assert.h>

#include <string>

namespace sam
{
    class location
    {
    public:
        location();

        location(const char *c_str);

        location(const std::string &string);

        location(const location &other);

        location(location &&other);

        void operator=(const char *c_str);

        void operator=(const std::string &string);

        void operator=(const location &other);

        void operator=(location &&other);

        bool operator==(const char *c_str) const;

        bool operator==(const std::string &string) const;

        bool operator==(const location &other) const;

        std::string get_filesystem() const;

        std::string get_path() const;

        const std::string &get_raw() const;

    protected:
        std::string raw_string;
    };

    inline location::location()
    {
    }

    inline location::location(const char *c_str) :
        raw_string(c_str)
    {
    }

    inline location::location(const std::string &string) :
        raw_string(string)
    {
    }

    inline location::location(const location &other) :
        raw_string(other.raw_string)
    {
    }

    inline location::location(location &&other)
    {
        raw_string = std::move(other.raw_string);
    }

    inline void location::operator=(const char *c_str)
    {
        raw_string = c_str;
    }

    inline void location::operator=(const std::string &string)
    {
        raw_string = string;
    }

    inline void location::operator=(const location &other)
    {
        raw_string = other.raw_string;
    }

    inline void location::operator=(location &&other)
    {
        raw_string = std::move(other.raw_string);
    }

    inline bool location::operator==(const char *c_str) const
    {
        return raw_string == c_str;
    }

    inline bool location::operator==(const std::string &string) const
    {
        return raw_string == string;
    }

    inline bool location::operator==(const location &other) const
    {
        return raw_string == other.raw_string;
    }

    inline std::string location::get_filesystem() const
    {
        s_assert(raw_string.find("://") != std::string::npos);
        return raw_string.substr(0, raw_string.find("://"));
    }

    inline std::string location::get_path() const
    {
        s_assert(raw_string.find("://") != std::string::npos);
        return raw_string.substr(raw_string.find("://") + 3);
    }

    inline const std::string& location::get_raw() const
    {
        return raw_string;
    }
}