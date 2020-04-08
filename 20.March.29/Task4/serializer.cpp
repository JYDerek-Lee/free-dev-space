#include "serializer.hpp"
#include <future>

constexpr int default_priority = 3;

namespace task
{

Serializer::Serializer()
{
    // std::async(std::launch::async,
    //            [this]() {
    //                this->run_task();
    //            });
}

void Serializer::set_task(Serializer::TaskType type,
                          Serializer::task_data *data)
{
    this->q.emplace(default_priority, data);
}

void Serializer::run_task()
{
    std::cout << "Test" << std::endl;
}

} // namespace task
