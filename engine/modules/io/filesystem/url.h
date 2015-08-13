#pragma once

#include <string>

namespace sam
{
    class url
    {
	public:
		url();

		url(const char *c_str);

		url(const std::string &string);

		url(url &other);

		url(url &&other);

		const std::string &get_filesystem();

	protected:
		std::string raw_string;
		std::string fs_name;
    };
}