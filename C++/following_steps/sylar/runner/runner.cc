#include "log.h"

#include <iostream>
//
// struct my_struct : std::shared_ptr<>
// {
//     
// };

int main() {
    sylar::Logger::ptr logger(new sylar::Logger()); 
    // sylar::Logger::ptr logger(std::make_shared<sylar::Logger>());
    logger->addAppender(sylar::LogAppender::ptr(std::make_shared<sylar::StdoutLogAppender>()));

    sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));
    logger->log(sylar::LogLevel::Level::DEBUG, event);

    std::cout << "hello log";

    return 0;
}