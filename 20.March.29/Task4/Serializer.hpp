#include <mutex>
#include <memory>
#include <queue>
#include <future>
#include "timer.hpp"

namespace task
{

class Serializer
{
public:
    struct task_data
    {
        std::function<void(void*)> func{};
        void *user_data {};
    };

public:
    ~Serializer()
    {
        this->scheduler.stop();
    }

    Serializer(Serializer &) = delete;
    Serializer(Serializer &&) = delete;
    Serializer(Serializer const &) = delete;

    Serializer operator=(Serializer &) = delete;
    Serializer operator=(Serializer &&) = delete;
    Serializer operator=(Serializer const &) = delete;

public:
    static Serializer &get_serializer()
    {
        std::call_once(serializer_once_, []() {
            serializer_.reset(new Serializer());
        });

        return *(serializer_.get());
    }

    void set_task(task_data &&data);

private:
    Serializer()
    {
        this->scheduler.set_function([&]() {
            if (!q.empty())
            {
                auto task = q.front();
                task.func(task.user_data);
                q.pop();
            }
        },
                                     500);

        this->scheduler.start();
    }

private:
    std::queue<task_data> q{};
    Timer scheduler{};

    static std::unique_ptr<Serializer> serializer_;
    static std::once_flag serializer_once_;
};

} // namespace task