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

        explicit data(size_t size = 0);

        data(uchar *buffer, size_t size);

        data(const data &other);

        data(data &&other);

        virtual ~data();

        data &operator=(const data &other);

        data &operator=(data &&other);

        void clear();

        bool empty() const;

        void assign(void *buffer, const size_t size);

        void copy(const void *buffer, const size_t size, const size_t offset = 0);

        void append(const void *buffer, const size_t size);

        uchar *get_buffer(const size_t offset = 0);

        size_t get_size() const;

        void set_size(size_t size);

    private:
        uchar *buffer{ nullptr };
        size_t size{ 0 };
    };

    typedef std::shared_ptr<data> data_ptr;
}