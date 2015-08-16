#include "storage_filesystem.h"



#include "storage/storage.h"

namespace sam
{
    storage_filesystem::storage_filesystem() :
        e(nullptr)
    {
    }

    storage_filesystem::~storage_filesystem()
    {
    }

    bool storage_filesystem::dispatch(const event_ptr &e)
    {
        s_assert(this->e == nullptr);
        this->e = std::dynamic_pointer_cast<io_request_location_event>(e);
        s_assert(this->e != nullptr);
        return true;
    }

    void storage_filesystem::handle()
    {
        auto data = storage::read(e->get_location().get_filesystem());
        e->set_data(data);
        e->finish();
        e.reset();
    }

    bool storage_filesystem::available()
    {
        return e == nullptr;
    }
}