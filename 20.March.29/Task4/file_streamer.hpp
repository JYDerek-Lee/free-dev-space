#include <fstream>

namespace task
{

class FileStreamer
{
public:
    FileStreamer() = default;
    ~FileStreamer() = default;

    FileStreamer(FileStreamer &) = delete;
    FileStreamer(FileStreamer &&) = delete;
    FileStreamer(FileStreamer const &) = delete;

    FileStreamer operator=(FileStreamer &) = delete;
    FileStreamer operator=(FileStreamer &&) = delete;
    FileStreamer operator=(FileStreamer const &) = delete;

public:

private:
    std::ifstream ostrm{};
    std::ofstream fstrm{};
};

} // namespace task
