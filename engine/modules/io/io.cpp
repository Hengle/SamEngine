#include "io.h"

namespace sam
{
    io::state *io::io_state = nullptr;

    io::state::state(const param &p)
    {
        threads.reserve(static_cast<size_t>(p.thread_count));
        for (auto i = 0; i < p.thread_count; ++i)
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

    void io::initialize(const param &p)
    {
        s_assert(io_state == nullptr);
        io_state = new state(p);
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