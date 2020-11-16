#include "log.h"
#include "util.h"

#include <iostream>
#include <thread>

//
// struct my_struct : std::shared_ptr<>
// {
//     
// };

int main() {
    sylar::Logger::ptr logger(new sylar::Logger()); 
    // sylar::Logger::ptr logger(std::make_shared<sylar::Logger>());
    logger->addAppender(sylar::LogAppender::ptr(std::make_shared<sylar::StdoutLogAppender>()));
    
    auto file_appender = std::make_shared<sylar::FileLogAppender>("./log.txt");
    sylar::LogFormatter::ptr fmt(std::make_shared<sylar::LogFormatter>("%d%T%m%n"));
    file_appender->setFormatter(fmt);
    logger->addAppender(file_appender);
    file_appender->setLevel(sylar::LogLevel::Level::ERROR);

    // sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0)));
    // event->getSS() << "Hello log";
    // logger->log(sylar::LogLevel::Level::DEBUG, event);
    
    SYLAR_LOG_INFO(logger) << "test macro";
    SYLAR_LOG_ERROR(logger) << "test macro";



    SYLAR_LOG_FATAL(logger) << "test macro";
    SYLAR_LOG_DEBUG(logger) << "test macro";

    auto l = sylar::LoggerMgr::getInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "mgr";

    return 0;
}