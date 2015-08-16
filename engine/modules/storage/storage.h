#pragma once

#include "core/data.h"

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

		static bool available();

	    static data_ptr read(const std::string &path);

        static void write(const std::string &path, data_ptr data);

	private:
		static class state
		{
		public:
			std::string path;
		} *storage_state;
    };
}