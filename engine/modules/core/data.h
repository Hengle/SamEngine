#pragma once

#include "class.h"

#include "types.h"

#include <memory>

namespace sam
{
	class data
	{
	public:
		CREATE_FUNC_DECLARE(data)

		explicit data(size_t size);

		data(uint8 *buffer, size_t size);

		data(const data &other);

		data(data &&other);

		virtual ~data();

		data &operator=(const data &other);

		data &operator=(data &&other);

		void clear();

		bool empty();

		void copy(const uint8 *buffer, const size_t size, const size_t offset = 0);

		uint8 *get_buffer(const size_t offset = 0);

		size_t get_size();

		void set_size(size_t size);

	private:
		uint8 *buffer;
		size_t size;
	};

	typedef std::shared_ptr<data> data_ptr;
}