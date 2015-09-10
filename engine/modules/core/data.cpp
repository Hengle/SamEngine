#include "data.h"

#include "assert.h"

#include <cstdlib>
#include <cstring>

namespace sam
{
    data::data(size_t size) :
        size(size)
    {
        if (size > 0)
        {
            buffer = static_cast<uchar *>(std::malloc(size));
        }
    }

    data::data(uchar *buffer, size_t size):
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

    bool data::empty() const
    {
        return size == 0 || buffer == nullptr;
    }

    void data::assign(void *buffer, const size_t size)
    {
        clear();
        this->buffer = reinterpret_cast<uchar *>(buffer);
        this->size = size;
    }

    void data::copy(const void *buffer, const size_t size, const size_t offset)
    {
        if (this->size - offset < size)
        {
            this->size = size + offset;
            this->buffer = static_cast<uchar *>(std::realloc(this->buffer, this->size));
        }
        std::memcpy(this->buffer + offset, buffer, size);
    }

    void data::append(const void *buffer, const size_t size)
    {
        if (buffer != nullptr && size > 0)
        {
            this->buffer = static_cast<uchar *>(std::realloc(this->buffer, this->size + size));
            std::memcpy(this->buffer + this->size, buffer, size);
            this->size += size;
        }
    }

    uchar *data::get_buffer(const size_t offset)
    {
        s_assert(!empty());
        s_assert(offset < size);
        return buffer + offset;
    }

    size_t data::get_size() const
    {
        return size;
    }

    void data::set_size(size_t size)
    {
        if (this->size != size)
        {
            this->size = size;
            this->buffer = static_cast<uchar *>(std::realloc(this->buffer, this->size));
        }
    }
}