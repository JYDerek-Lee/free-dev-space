#include "serializer.hpp"
#include "store.hpp"

#include <iostream>

int main()
{
    task::Serializer::task_data data{};
    data.func = [](void *data) {
        std::cout << "TestTTT" << std::endl;
    };

    // Input tasks
    auto &serializer = task::Serializer::get_serializer();
    serializer.set_task(std::move(data));
    serializer.set_task(std::move(data));
    serializer.set_task(std::move(data));

    auto sdata = new task::Store::store_data();
    data.func = task::Store::get_store_instance().get_event;
    sdata->key = "Testing";
    sdata->value = "Okey";
    sdata->etype = task::Store::store_event_type::kSetValue;
    data.user_data = sdata;

    serializer.set_task(std::move(data));

    while (true)
    {
    }
}