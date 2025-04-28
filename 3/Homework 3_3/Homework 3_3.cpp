#include <iostream>
#include <fstream>
#include <exception>

enum class LogType {
    Unknown,
    Warning,
    Error,
    FatalError
};

class LogMessage {
private:
    LogType _type_;
    std::string _msg_;
public:

    LogMessage(LogType type, const std::string& msg) : _type_(type), _msg_(msg) {}

    LogType type() const {
        return _type_;
    };
    const std::string& message() const {
        return _msg_;
    };
};

class LogHandler {
public:
    virtual ~LogHandler() = default;

    virtual void handle_request(const LogMessage& msg) = 0;
    virtual void set_next_handler (LogHandler* _next_) = 0;
};

class FatalErrorHandler : public LogHandler {
private:
    LogHandler* _next_ = nullptr;
public:
    void set_next_handler(LogHandler* next) override {
        _next_ = next;
    }

    void handle_request(const LogMessage& msg) override {
        if (msg.type() == LogType::FatalError) {
            std::string er = msg.message();
            throw er;
        }
        else if (_next_ != nullptr) {
            _next_->handle_request(msg);
        }
        else {
            std::cout << "Unknown command!" << std::endl;
        }
    }
};

class ErrorHandler : public LogHandler {
private:
    LogHandler* _next_ = nullptr;
    std::string _path_{ "error.txt" };
public:
    void set_next_handler(LogHandler* next) override {
        _next_ = next;
    }

    void handle_request(const LogMessage& msg) override {
        if (msg.type() == LogType::Error) {
            std::ofstream log_record;
            log_record.open(_path_);
            if (log_record.is_open())
            {
                log_record << msg.message() << std::endl;
            }
            log_record.close();
        }
        else if (_next_ != nullptr) {
            _next_->handle_request(msg);
        }
        else {
            std::cout << "Unknown command!" << std::endl;
        }
    }

    void select_path() {
        std::cout << "Enter the path: ";
        std::string path{};
        std::cin >> path;
        _path_ = path;
    }
};

class WarningHandler : public LogHandler {
private:
    LogHandler* _next_ = nullptr;
public:
    void set_next_handler(LogHandler* next) override {
        _next_ = next;
    }

    void handle_request(const LogMessage& msg) override {
        if (msg.type() == LogType::Warning) {
            std::cout << "Warning: " << msg.message() << std::endl;
        }
        else if (_next_ != nullptr) {
            _next_->handle_request(msg);
        }
        else {
            std::cout << "Unknown command!" << std::endl;
        }
    }
};

class UnknownHandler : public LogHandler {
private:
    LogHandler* _next_ = nullptr;
public:
    void set_next_handler(LogHandler* next) override {
        _next_ = next;
    }

    void handle_request(const LogMessage& msg) override {
        if (msg.type() == LogType::Unknown) {
            throw "Message can not be processed!";
        }
        else if (_next_ != nullptr) {
            _next_->handle_request(msg);
        }
        else {
            std::cout << "Unknown command!" << std::endl;
        }
    }
};

int main()
{
    LogMessage msg1(LogType(0), "TEST ERROR 1");
    LogMessage msg2(LogType(1), "TEST ERROR 2");
    LogMessage msg3(LogType (2), "TEST ERROR 3");
    LogMessage msg4(LogType(3), "TEST ERROR 4");

    LogHandler* warn = new WarningHandler;
    LogHandler* err = new ErrorHandler;
    LogHandler* fatal_err = new FatalErrorHandler;
    LogHandler* unk = new UnknownHandler;

    fatal_err->set_next_handler(err);
    err->set_next_handler(warn);
    warn->set_next_handler(unk);

    try {
        fatal_err->handle_request(msg4);
    }
    catch (std::string& error_message) {
        std::cout << error_message << std::endl;
    }
    catch (const char* err_msg)
    {
        std::cout << err_msg << std::endl;
    }

    return 0;
}


