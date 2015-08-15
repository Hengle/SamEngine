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

		bool operator==(const char *c_str) const;

		bool operator==(const std::string &string) const;

		bool operator==(const location &other) const;

		const std::string &get_filesystem() const;

	protected:
		std::string raw_string;
		std::string fs_name;
    };
}