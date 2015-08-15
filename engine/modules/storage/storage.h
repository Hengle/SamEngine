#pragma once

#include <string>

namespace sam
{
    class storage
    {
	public:
		class param
		{
		public:
			param(const char *path) : path(path) {}

			param(const std::string &path) : path(path) {}

			std::string path;
		};

		static void initialize(const param &p);

		static void finalize();

		static void available();

	private:
		static class state
		{
		public:
			std::string path;
		} *storage_state;
    };
}