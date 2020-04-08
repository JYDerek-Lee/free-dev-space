#include "store.hpp"
#include <chrono>

namespace task
{

std::string Store::get_value(std::string &&str)
{
    auto time_sec = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (time_data_[str] >= time_sec)
    {
        this->data_.erase(str);
        this->time_data_.erase(str);
        return "";
    }

    return this->data_[str];
}

void Store::set_value(std::string &&key,
                      std::string &&value)
{
    this->data_.emplace(key, value);
}

void Store::expire_value(std::string &&key,
                         uint64_t &&expire_tick)
{
    auto tick = std::chrono::system_clock::now() + std::chrono::seconds(expire_tick);
    time_data_.emplace(key, std::chrono::system_clock::to_time_t(tick));
}

} // namespace task

// How to use chrono
// #include <iostream>
// #include <ctime>
// #include <iomanip>
// int main()
// {
//     auto temp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//     auto time_tick = std::chrono::system_clock::now() + std::chrono::seconds(30);
//     auto tick = std::chrono::system_clock::to_time_t(time_tick);
//     std::cout << std::put_time(std::localtime(&tick), "%Y-%m-%d %X") << std::endl;

//     return 0;
// }