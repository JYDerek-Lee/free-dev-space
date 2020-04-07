#include <mutex>
#include <memory>
#include <unordered_map>
#include <string>

namespace task
{

class Store
{
public:
    static Store &get_store_instance()
    {
        std::call_once(store_once_, []() {
            store_.reset(new Store());
        });
    };
    ~Store() = default;

    Store(Store &) = delete;
    Store(Store &&) = delete;
    Store(Store const &) = delete;

    Store operator=(Store &) = delete;
    Store operator=(Store &&) = delete;
    Store operator=(Store const &) = delete;

public:
    std::string get_value(std::string &&str);
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

std::unique_ptr<Store> store_;
std::once_flag store_once_;

} // namespace task