#include <mutex>
#include <memory>
#include <queue>

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
    };

    //to FileStreamer
#include <string>
    struct file_data : task_data
    {
        std::string key {};
        std::string value {};
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
    }

    void set_task(Serializer::TaskType type,
                  task_data *data);

private:
    Serializer() = default;

private:
    std::priority_queue<int, int> q{};

    static std::unique_ptr<Serializer> serializer_;
    static std::once_flag serializer_once_;
};

std::unique_ptr<Serializer> serializer_;
std::once_flag serializer_once_;

} // namespace task