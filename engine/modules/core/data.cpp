#include "data.h"

#include "assert.h"

#include <cstdlib>

namespace sam
{
	data::data(size_t size) :
		buffer(nullptr),
		size(size)
	{
		if (size > 0)
		{
			buffer = static_cast<uint8_t *>(std::malloc(size));
		}
	}

	data::data(uint8 *buffer, size_t size):
		buffer(buffer),
		size(size)
	{
		s_assert(size == 0 || buffer != nullptr);
	}

	data::data(const data &other) :
		buffer(other.buffer),
		size(other.size)
	{
		s_assert(size == 0 || buffer != nullptr);
	}

	data::data(data &&other) :
		buffer(other.buffer),
		size(other.size)
	{
		s_assert(size == 0 || buffer != nullptr);
		other.buffer = nullptr;
		other.size = 0;
	}

	data::~data()
	{
		clear();
	}

	data &data::operator=(const data &other)
	{
		buffer = other.buffer;
		size = other.size;
		s_assert(size == 0 || buffer != nullptr);
		return *this;
	}

	data &data::operator=(data &&other)
	{
		buffer = other.buffer;
		size = other.size;
		other.buffer = nullptr;
		other.size = 0;
		s_assert(size == 0 || buffer != nullptr);
		return *this;
	}

	void data::clear()
	{
		if (buffer)
		{
			std::free(buffer);
		}
		buffer = nullptr;
		size = 0;
	}

	bool data::empty()
	{
		return size == 0 || buffer == nullptr;
	}

	void data::copy(const uint8 *buffer, const size_t size, const size_t offset)
	{
		if (this->size - offset < size)
		{
			this->size = size + offset;
			std::realloc(this->buffer, this->size);
		}
		std::memcpy(this->buffer + offset, buffer, size);
	}

	uint8 *data::get_buffer(const size_t offset)
	{
		s_assert(!empty());
		s_assert(offset < size);
		return buffer + offset;
	}

	size_t data::get_size()
	{
		return size;
	}

	void data::set_size(size_t size)
	{
		if (this->size != size)
		{
			this->size = size;
			std::realloc(this->buffer, this->size);
		}
	}
}