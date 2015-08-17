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
	}

	location::location(const std::string &string) :
		raw_string(string)
	{
	}

    location::location(const location &other) :
        raw_string(other.raw_string)
    {
    }

    location::location(location &&other)
    {
        raw_string = std::move(other.raw_string);
    }

    void location::operator=(const char *c_str)
	{
		raw_string = c_str;
	}

	void location::operator=(const std::string &string)
	{
		raw_string = string;
		if (!raw_string.empty())
		{
			
		}
	}

    void location::operator=(const location &other)
    {
        raw_string = other.raw_string;
    }

    void location::operator=(location &&other)
    {
        raw_string = std::move(other.raw_string);
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

	std::string location::get_filesystem() const
	{
		s_assert(raw_string.find(":") != std::string::npos);
		return raw_string.substr(0, raw_string.find(":"));
	}

	std::string location::get_path() const
	{
		s_assert(raw_string.find(":") != std::string::npos);
		return raw_string.substr(raw_string.find(":") + 1);
	}
}