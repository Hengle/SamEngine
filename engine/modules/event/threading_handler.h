#include "handler.h"

#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>

namespace sam
{
    class threading_handler : public handler
    {
    public:
        enum class status
        {
            waiting,
            running,
            stopping,
            stopped,
        };

        threading_handler();

        virtual ~threading_handler();

        virtual bool notify(const event_ptr &e) override;

        virtual void handle() override;

        void start();

        void stop();

        void set_wait_time(int32 value) { wait_ms = value; }

        int32 get_wait_time() const { return wait_ms; }

    protected:
        virtual void enter_thread();

        virtual void leave_thread();

        virtual void forward_notify(const event_ptr &e);

        virtual void forward_handle();

    private:
        static void main_loop(threading_handler *self);

    protected:
        int32 wait_ms;
        handler_ptr dst_handler;

    private:
        status current;
        std::thread::id parent;
        std::thread::id child;
        std::thread worker;
        std::mutex mutex;
        std::mutex queue_lock;
        std::condition_variable condition_variable;
        std::queue<event_ptr> comming_events;
        std::queue<event_ptr> waiting_events;
        std::queue<event_ptr> forwarding_events;
    };
}