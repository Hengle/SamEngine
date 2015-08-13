#include "url.h"

#include "core/assert.h"

namespace sam
{
	url::url()
	{
	}

	url::url(const char *c_str) :
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

	url::url(const std::string &string) :
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

    url::url(const url &other) :
        raw_string(other.raw_string),
        fs_name(other.fs_name)
    {
    }

    url::url(url &&other)
    {
        raw_string = std::move(other.raw_string);
        fs_name = std::move(other.fs_name);
    }

    void url::operator=(const char *c_str)
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

	void url::operator=(const std::string &string)
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

    void url::operator=(const url &other)
    {
        raw_string = other.raw_string;
        fs_name = other.fs_name;
    }

    void url::operator=(url &&other)
    {
        raw_string = std::move(other.raw_string);
        fs_name = std::move(other.fs_name);
    }

    const std::string &url::get_filesystem() const
	{
		return fs_name;
	}
}