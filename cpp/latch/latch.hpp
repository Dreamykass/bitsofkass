
#include <mutex>
#include <condition_variable>
#include <utility>

namespace bok
{
    // a counting latch (single-use non-movable non-copyable barrier)
    // calling thread waits (blocks) on the latch (or arrives and waits, which also decrements the counter),
    // until the counter reaches zero, because of: arriving, decrementation, or until
    // another thread calls release, which sets the counter to zero
    template <size_t m_max = std::numeric_limits<size_t>::max()>
    class Latch
    {
    private:
        size_t m_downcounter = m_max;
        std::mutex m_mutex;
        std::condition_variable m_condvar;

    public:
        Latch() {}
        ~Latch() {}

        Latch(const Latch &other) = delete;
        Latch(Latch &&other) noexcept = delete;

        Latch &operator=(const Latch &other) = delete;
        Latch &operator=(Latch &&other) noexcept = delete;

    public:
        // decrements the counter by n = 1
        // if n > counter, then throws std::underflow_error
        void Decrement(size_t n = 1)
        {
            std::unique_lock ulock(m_mutex);

            if (n > m_downcounter)
                throw std::underflow_error("bok::Latch::Decrement(" + std::to_string(n) + "); latch downcounter would underflow");

            m_downcounter -= n;

            if (m_downcounter == 0)
                m_condvar.notify_all();

            return;
        }

        // zeroes the counter
        // effectively releasing any and every waiting thread
        // no effect if counter is already zero
        void Release()
        {
            std::unique_lock ulock(m_mutex);

            m_downcounter = 0;
            m_condvar.notify_all();

            return;
        }

        // doesn't decrement the counter
        // and blocks the caller until the counter is zero
        void Wait()
        {
            std::unique_lock<std::mutex> ulock(m_mutex);
            while (m_downcounter != 0)
                m_condvar.wait(ulock);
        }

        // doesn't decrement the counter
        // calls the callback (void()) passed in the parameter
        // just after locking the mutex guarding the counter
        // and blocks the caller until the counter is zero
        template <typename Fun>
        void Wait(Fun callback)
        {
            std::unique_lock<std::mutex> ulock(m_mutex);
            callback();

            while (m_downcounter != 0)
                m_condvar.wait(ulock);
        }

        // decrements the counter
        // and blocks the caller until the counter is zero
        void Arrive()
        {
            std::unique_lock<std::mutex> ulock(m_mutex);
            m_downcounter--;

            if (m_downcounter == 0)
                m_condvar.notify_all();

            while (m_downcounter != 0)
                m_condvar.wait(ulock);
        }

        // decrements the counter
        // calls the callback (void()) passed in the parameter
        // just after locking the mutex guarding the counter
        // and blocks the caller until the counter is zero
        template <typename Fun>
        void Arrive(Fun callback)
        {
            std::unique_lock<std::mutex> ulock(m_mutex);
            callback();
            m_downcounter--;

            if (m_downcounter == 0)
                m_condvar.notify_all();

            while (m_downcounter != 0)
                m_condvar.wait(ulock);
        }
    };

} // namespace bok