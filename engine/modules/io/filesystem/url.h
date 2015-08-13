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

		url(const url &other);

		url(url &&other);

		void operator=(const char *c_str);

		void operator=(const std::string &string);

		void operator=(const url &other);

		void operator=(url &&other);

		const std::string &get_filesystem() const;

	protected:
		std::string raw_string;
		std::string fs_name;
    };
}