#include "storage.h"

#include "core/assert.h"

#include <fstream>

namespace sam
{
    storage::state *storage::storage_state = nullptr;

	void storage::initialize(const param &p)
	{
        s_assert(!available());
        storage_state = new state();
        storage_state->path = p.path;
	}

	void storage::finalize()
	{
        s_assert(available());
        delete storage_state;
        storage_state = nullptr;
	}

	bool storage::available()
	{
		return storage_state != nullptr;
	}

    data_ptr storage::read(const std::string &path)
    {
        auto full_path = storage_state->path + path;
        std::ifstream file(full_path, std::ios::binary | std::ios::in);
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
		auto full_path = storage_state->path + path;
		std::ofstream file(full_path, std::ios::binary | std::ios::out);
		if (file.is_open())
		{
			file.write(reinterpret_cast<char *>(data->get_buffer()), data->get_size());
		}
    }
}