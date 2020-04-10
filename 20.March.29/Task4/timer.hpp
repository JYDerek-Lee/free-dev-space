#include <queue>
#include <thread>
#include <functional>
#include <chrono>

namespace task
{

class Timer
{
public:
    Timer() = default;
    Timer(std::function<void(void)> func, uint32_t interval)
        : func_(func),
          interval_(interval){};
    ~Timer()
    {
        this->stop();
    }

    Timer(Timer &) = delete;
    Timer(Timer &&) = delete;
    Timer(Timer const &) = delete;

    Timer operator=(Timer &) = delete;
    Timer operator=(Timer &&) = delete;
    Timer operator=(Timer const &) = delete;

public:
    void start()
    {
        this->active = true;
        this->thrd = std::thread([&]() {
            while (this->active)
            {
                auto delta = std::chrono::system_clock::now() + std::chrono::milliseconds(this->interval_);
                this->func_();
                std::this_thread::sleep_until(delta);
            }
        });

        this->thrd.detach();
    }

    void stop()
    {
        this->active = true;
        this->thrd.~thread();
    }

    void set_function(std::function<void(void)> func, uint32_t interval)
    {
        this->func_ = func;
        this->interval_ = interval;
    }

private:
    uint32_t interval_{};
    std::function<void(void)> func_{};

    std::thread thrd{};

    bool active{};
};

} // namespace task