namespace task
{
class Connector
{
public:
    Connector() = default;
    virtual ~Connector() = default;

    Connector(Connector &) = delete;
    Connector(Connector &&) = delete;
    Connector(Connector const &) = delete;

    Connector operator=(Connector &) = delete;
    Connector operator=(Connector &&) = delete;
    Connector operator=(Connector const &) = delete;

public:
    void get_connect(){};
};
} // namespace task