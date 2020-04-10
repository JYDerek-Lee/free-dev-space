#include "serializer.hpp"

namespace task
{

std::unique_ptr<Serializer> Serializer::serializer_;
std::once_flag Serializer::serializer_once_;

void Serializer::set_task(Serializer::task_data &&data)
{
    this->q.emplace(data);
}

} // namespace task