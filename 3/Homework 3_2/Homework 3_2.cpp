#include <iostream>
#include <fstream>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;

    virtual void onWarning(const std::string& message){}
    virtual void onError(const std::string& message){}
    virtual void onFatalError(const std::string& message){}
};

class EventMsg {
private:
    std::vector<Observer*> _observers_;
public:
    ~EventMsg() {}

    void warning(const std::string& message) const {
        for (const auto& observer : _observers_) {
            observer->onWarning(message);
        }
    }
    void error(const std::string& message) const {
        for (const auto& observer : _observers_) {
            observer->onError(message);
        }
    }
    void fatalError(const std::string& message) const {
        for (const auto& observer : _observers_) {
            observer->onFatalError(message);
        }
    }

    void add_observer(Observer* obs) {
        _observers_.push_back(obs);
    }

    void remove_observer(Observer* obs) {
        auto it = remove(_observers_.begin(), _observers_.end(), obs);
        _observers_.erase(it, _observers_.end());
    }
};

class WarningWork : public Observer {
private:

public:
    void onWarning(const std::string& message) override {
        std::cout << "WARNING: " << message << std::endl;
    }
};

class ErrorWork : public Observer {
private:
    std::string _path_{ "error.txt" };
public:
    void onError(const std::string& message) override {
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

class FatalErrorWork : public Observer {
private:
    std::string _path_{ "fatal_error.txt" };
public:
    void onFatalError(const std::string& message) override {
        std::cout << "FATAL ERROR: " << message << std::endl;
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

int main()
{
    EventMsg event_msg;
    WarningWork warn;
    ErrorWork err;
    FatalErrorWork fatal_errr;

    event_msg.add_observer(&warn);
    event_msg.add_observer(&err);
    event_msg.add_observer(&fatal_errr);

    event_msg.warning("test warning");
    event_msg.error("test error");
    event_msg.fatalError("test fatal error");

    return 0;
}
