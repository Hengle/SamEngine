#include "storage.h"

#include <fstream>

#if SAM_WINDOWS || SAM_MINGW
#   define PATH_SEPARATOR '\\'
#else
#   define PATH_SEPARATOR '/'
#endif

namespace sam
{
    data_ptr storage::read(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::in);
        if (file.is_open())
        {
            file.seekg(0, std::ios::beg);
            auto begin = file.tellg();
            file.seekg(0, std::ios::end);
            auto end = file.tellg();
            file.seekg(0, std::ios::beg);
            auto d = data::create(static_cast<size_t>(end - begin));
            file.read(reinterpret_cast<char *>(d->get_buffer()), d->get_size());
            return d;
        }
        return nullptr;
    }

    void storage::write(const std::string &path, data_ptr data)
    {
        std::ofstream file(path, std::ios::binary | std::ios::out);
        if (file.is_open())
        {
            file.write(reinterpret_cast<char *>(data->get_buffer()), data->get_size());
        }
    }
}