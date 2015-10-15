#pragma once

#include "Class.h"

#include "Types.h"

#include <memory>

namespace SamEngine
{
    class CORE_API Data
    {
    public:
        CREATE_FUNC_DECLARE(Data)

        explicit Data(size_t size = 0);

        Data(uchar *buffer, size_t size);

        Data(const Data &other);

        Data(Data &&other);

        virtual ~Data();

        Data &operator=(const Data &other);

        Data &operator=(Data &&other);

        void Clear();

        bool Empty() const;

        void Assign(void *buffer, const size_t size);

        void Copy(const void *buffer, const size_t size, const size_t offset = 0);

        void Append(const void *buffer, const size_t size);

        uchar *GetBuffer(const size_t offset = 0) const;

        size_t GetSize() const;

        void SetSize(size_t size);

    private:
        uchar *mBuffer{ nullptr };
        size_t mSize{ 0 };
    };

    typedef std::shared_ptr<Data> DataPtr;
}