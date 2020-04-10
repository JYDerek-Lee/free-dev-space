#include <mutex>
#include <memory>
#include <unordered_map>
#include <string>

namespace task
{

class Store
{
public:
    enum class store_event_type
    {
        kUndefined = 0,
        kGetValue,
        kSetValue
    };

    struct store_data
    {
    public:
        std::string key{};
        std::string value{};
        store_event_type etype{};
    };

public:
    static Store &get_store_instance()
    {
        std::call_once(store_once_, []() {
            store_.reset(new Store());
        });

        return *(store_.get());
    };
    ~Store() = default;

    Store(Store &) = delete;
    Store(Store &&) = delete;
    Store(Store const &) = delete;

    Store operator=(Store &) = delete;
    Store operator=(Store &&) = delete;
    Store operator=(Store const &) = delete;

public:
    static void get_event(void *user_data)
    {
        auto data = static_cast<store_data*>(user_data);

        switch (data->etype)
        {
        case store_event_type::kSetValue:
        {
            get_store_instance().set_value(std::move(data->key),
                                           std::move(data->value));
        }
        break;

        case store_event_type::kGetValue:
        {
        }
        break;
        }
    }

    std::string get_value(std::string &&str,
                          std::string &&value);
    void set_value(std::string &&key,
                   std::string &&value);
    void expire_value(std::string &&key,
                      uint64_t &&tick);

private:
    Store() = default;

private:
    // key, value
    std::unordered_map<std::string, std::string> data_{};
    // key, expire time
    std::unordered_map<std::string, uint64_t> time_data_{};

    static std::unique_ptr<Store> store_;
    static std::once_flag store_once_;
};

} // namespace task