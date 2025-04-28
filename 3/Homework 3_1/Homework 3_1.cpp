#include <iostream>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLog : public LogCommand {
public:
    ConsoleLog(){}

    void print(const std::string& message) override {
        std::cout << "Log message is: " << message << std::endl;
    }
};

class FileLog : public LogCommand {
private:
    std::string _path_{ "log.txt" };
public:
    FileLog(){}

    void print(const std::string& message) override {
        std::ofstream log_record;
        log_record.open(_path_);
        if (log_record.is_open())
        {
            log_record << message << std::endl;
        }
        log_record.close();
    }

    void select_path() {
        std::cout << "Enter the path: ";
        std::string path{};
        std::cin >> path;
        _path_ = path;
    }
};

void print(LogCommand& log, const std::string& message) {
    log.print(message);
}

int main()
{
    FileLog fl;
    ConsoleLog cl;

    print(fl, "file log");
    print(cl, "console log");

    return 0;
}
