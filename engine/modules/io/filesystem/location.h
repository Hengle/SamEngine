#pragma once

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

		const std::string &get_filesystem() const;

	protected:
		std::string raw_string;
		std::string fs_name;
    };
}