#include <mutex>
#include <memory>
#include <queue>
#include <iostream>

namespace task
{

class Serializer
{
public:
    enum class TaskType : uint16_t
    {
        kUndefined = 0,
        kFileStream = 1,
    };

    struct task_data
    {
        int a;
    };

public:
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

    void set_task(Serializer::TaskType type,
                  task_data *data);

private:
    Serializer();
    void run_task();

private:
    std::queue<task_data *> q{};

    static std::unique_ptr<Serializer> serializer_;
    static std::once_flag serializer_once_;
};

std::unique_ptr<Serializer> serializer_;
std::once_flag serializer_once_;

} // namespace task

// int main()
// {
//     int a = 0;
//     auto &serializer = task::Serializer::get_serializer();
// }