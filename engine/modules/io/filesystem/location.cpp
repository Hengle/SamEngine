#include "location.h"

#include "core/assert.h"

namespace sam
{
	location::location()
	{
	}

	location::location(const char *c_str) :
		raw_string(c_str)
	{
		if (!raw_string.empty())
		{
			s_assert(raw_string.find(":") != std::string::npos);
			if (fs_name.empty())
			{
				fs_name = raw_string.substr(0, raw_string.find(":"));
			}
		}
	}

	location::location(const std::string &string) :
		raw_string(string)
	{
		if (!raw_string.empty())
		{
			s_assert(raw_string.find(":") != std::string::npos);
			if (fs_name.empty())
			{
				fs_name = raw_string.substr(0, raw_string.find(":"));
			}
		}
	}

    location::location(const location &other) :
        raw_string(other.raw_string),
        fs_name(other.fs_name)
    {
    }

    location::location(location &&other)
    {
        raw_string = std::move(other.raw_string);
        fs_name = std::move(other.fs_name);
    }

    void location::operator=(const char *c_str)
	{
		raw_string = c_str;
		fs_name.clear();
		if (!raw_string.empty())
		{
			s_assert(raw_string.find(":") != std::string::npos);
			if (fs_name.empty())
			{
				fs_name = raw_string.substr(0, raw_string.find(":"));
			}
		}
	}

	void location::operator=(const std::string &string)
	{
		raw_string = string;
		fs_name.clear();
		if (!raw_string.empty())
		{
			s_assert(raw_string.find(":") != std::string::npos);
			if (fs_name.empty())
			{
				fs_name = raw_string.substr(0, raw_string.find(":"));
			}
		}
	}

    void location::operator=(const location &other)
    {
        raw_string = other.raw_string;
        fs_name = other.fs_name;
    }

    void location::operator=(location &&other)
    {
        raw_string = std::move(other.raw_string);
        fs_name = std::move(other.fs_name);
    }

	bool location::operator==(const char *c_str) const
	{
		return raw_string == c_str;
	}

	bool location::operator==(const std::string &string) const
	{
		return raw_string == string;
	}

	bool location::operator==(const location &other) const
	{
		return raw_string == other.raw_string;
	}

	const std::string &location::get_filesystem() const
	{
		return fs_name;
	}
}