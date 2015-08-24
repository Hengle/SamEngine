#pragma once

#include "types.h"

#include <cstdlib>
#include <memory>

namespace sam
{
    template <class TYPE>
    class pool
    {
    public:
        static const uint32 default_size = 128;

        pool();

        explicit pool(uint32 size);

        ~pool();

        template <typename... ARGS>
        std::shared_ptr<TYPE> create(ARGS &&... args);

        void destory(std::shared_ptr<TYPE> object);

    private:
        class node
        {
        public:
            node *next;
            TYPE object;
        };

        node *buffer;
        node *head;
    };

    template <class TYPE>
    pool<TYPE>::pool() :
        pool(default_size)
    {
    }

    template <class TYPE>
    pool<TYPE>::pool(uint32 size)
    {
        buffer = static_cast<node *>(std::malloc(static_cast<size_t>(size * sizeof(node))));
        head = buffer;
        for (uint32 i = 0; i < size; ++i)
        {
            buffer[i].next = &buffer[i + 1];
        }
        buffer[size - 1].next = nullptr;
    }

    template <class TYPE>
    pool<TYPE>::~pool()
    {
        std::free(buffer);
    }

    template <class TYPE>
    template <typename ... ARGS>
    std::shared_ptr<TYPE> pool<TYPE>::create(ARGS &&... args)
    {
        if (head != nullptr)
        {
            auto n = head;
            head = head->next;
            auto object = new(static_cast<void *>(&n->object)) TYPE(std::forward<ARGS>(args)...);
            return std::shared_ptr<TYPE>(object);
        }
        return nullptr;
    }

    template <class TYPE>
    void pool<TYPE>::destory(std::shared_ptr<TYPE> object)
    {
        object->~TYPE();
        auto n = reinterpret_cast<node *>(object.get()) - 1;
        n->next = head;
        head = n;
    }
}