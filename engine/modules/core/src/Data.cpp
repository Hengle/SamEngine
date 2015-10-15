#include "Data.h"

#include "ILog.h"

#include <cstdlib>
#include <cstring>

namespace SamEngine
{
    Data::Data(size_t size) :
        mSize(size)
    {
        if (mSize > 0)
        {
            mBuffer = static_cast<uchar *>(std::malloc(mSize));
        }
    }

    Data::Data(uchar *buffer, size_t size):
        mBuffer(buffer),
        mSize(size)
    {
        s_assert(mSize == 0 || buffer != nullptr);
    }

    Data::Data(const Data &other) :
        mBuffer(other.mBuffer),
        mSize(other.mSize)
    {
        s_assert(mSize == 0 || mBuffer != nullptr);
    }

    Data::Data(Data &&other) :
        mBuffer(other.mBuffer),
        mSize(other.mSize)
    {
        s_assert(mSize == 0 || mBuffer != nullptr);
        other.mBuffer = nullptr;
        other.mSize = 0;
    }

    Data::~Data()
    {
        Clear();
    }

    Data &Data::operator=(const Data &other)
    {
        Copy(other.mBuffer, other.mSize);
        s_assert(mSize == 0 || mBuffer != nullptr);
        return *this;
    }

    Data &Data::operator=(Data &&other)
    {
        mBuffer = other.mBuffer;
        mSize = other.mSize;
        other.mBuffer = nullptr;
        other.mSize = 0;
        s_assert(mSize == 0 || mBuffer != nullptr);
        return *this;
    }

    void Data::Clear()
    {
        if (mBuffer)
        {
            std::free(mBuffer);
        }
        mBuffer = nullptr;
        mSize = 0;
    }

    bool Data::Empty() const
    {
        return mSize == 0 || mBuffer == nullptr;
    }

    void Data::Assign(void *buffer, const size_t size)
    {
        Clear();
        mBuffer = reinterpret_cast<uchar *>(buffer);
        mSize = size;
    }

    void Data::Copy(const void *buffer, const size_t size, const size_t offset)
    {
        if (mSize - offset < size)
        {
            mSize = size + offset;
            mBuffer = static_cast<uchar *>(std::realloc(mBuffer, mSize));
        }
        std::memcpy(mBuffer + offset, buffer, size);
    }

    void Data::Append(const void *buffer, const size_t size)
    {
        if (buffer != nullptr && size > 0)
        {
            mBuffer = static_cast<uchar *>(std::realloc(mBuffer, mSize + size));
            std::memcpy(mBuffer + mSize, buffer, size);
            mSize += size;
        }
    }

    uchar *Data::GetBuffer(const size_t offset) const
    {
        s_assert(!Empty());
        s_assert(offset < mSize);
        return mBuffer + offset;
    }

    size_t Data::GetSize() const
    {
        return mSize;
    }

    void Data::SetSize(size_t size)
    {
        if (mSize != size)
        {
            mSize = size;
            mBuffer = static_cast<uchar *>(std::realloc(mBuffer, mSize));
        }
    }
}