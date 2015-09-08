#include "func_group.h"

#include "assert.h"

#include <algorithm>

namespace sam
{
    func_group::id func_group::add(func value)
    {
        auto new_id = ++current;
        add_cache.insert({ new_id, value });
        return new_id;
    }

    void func_group::remove(id value)
    {
        s_assert(std::find(remove_cache.begin(), remove_cache.end(), value) == remove_cache.end());
        s_assert(group.find(value) != group.end() || add_cache.find(value) != add_cache.end());
        remove_cache.push_back(value);
    }

    bool func_group::contain(id value)
    {
        return group.find(value) != group.end() || add_cache.find(value) != add_cache.end();
    }

    void func_group::run()
    {
        remove_from_group();
        add_to_group();
        for (auto &pair : group)
        {
            pair.second();
        }
        remove_from_group();
        add_to_group();
    }

    void func_group::add_to_group()
    {
        for (auto &pair : add_cache)
        {
            group.insert({ pair.first, pair.second });
        }
        add_cache.clear();
    }

    void func_group::remove_from_group()
    {
        for (auto &value : remove_cache)
        {
            if (group.find(value) != group.end())
            {
                group.erase(value);
            }
            else if (add_cache.find(value) != add_cache.end())
            {
                add_cache.erase(value);
            }
        }
        remove_cache.clear();
    }
}
