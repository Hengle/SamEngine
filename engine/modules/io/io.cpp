#include "io.h"

namespace sam
{
    io::state *io::io_state = nullptr;

    io::state::state()
    {
        threads.reserve(4);
        for (auto i = 0; i < 4; ++i)
        {
            auto t = io_thread::create();
            t->start();
            threads.push_back(t);
        }
    }

    io::state::~state()
    {
        for (auto &t : threads)
        {
            t = io_thread::create();
            t->stop();
        }
        threads.clear();
    }

    void io::initialize()
    {
        s_assert(io_state == nullptr);
        io_state = new state;
    }

    void io::finalize()
    {
        delete io_state;
    }

    bool io::available()
    {
        return io_state != nullptr;
    }
}