#include "Storage.h"

#include <fstream>

#if SAM_WINDOWS
#   define PATH_SEPARATOR '\\'
#else
#   define PATH_SEPARATOR '/'
#endif

namespace SamEngine
{
    DataPtr Storage::Read(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::in);
        if (file.is_open())
        {
            file.seekg(0, std::ios::beg);
            auto begin = file.tellg();
            file.seekg(0, std::ios::end);
            auto end = file.tellg();
            file.seekg(0, std::ios::beg);
            auto d = Data::Create(static_cast<size_t>(end - begin));
            file.read(reinterpret_cast<char *>(d->GetBuffer()), d->GetSize());
            return d;
        }
        return nullptr;
    }

    void Storage::Write(const std::string &path, DataPtr data)
    {
        std::ofstream file(path, std::ios::binary | std::ios::out);
        if (file.is_open())
        {
            file.write(reinterpret_cast<char *>(data->GetBuffer()), data->GetSize());
        }
    }

    STORAGE_API IStorage &GetStorage()
    {
        static Storage instance;
        return instance;
    }
}