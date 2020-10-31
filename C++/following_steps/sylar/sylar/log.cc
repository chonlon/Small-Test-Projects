#include "log.h"

namespace  sylar {

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
}

void Logger::debug(LogEvent::ptr event) {
     log(LogLevel::Level::DEBUG, event);
}

void Logger::info(LogEvent::ptr event) {
    log(LogLevel::Level::INFO, event);
}

void Logger::warn(LogEvent::ptr event) {
    log(LogLevel::Level::WARNN, event);
}

void Logger::error(LogEvent::ptr event) {
    log(LogLevel::Level::ERROR, event);
}

void Logger::fatal(LogEvent::ptr event) {
    log(LogLevel::Level::FATAL, event);
}

void Logger::addAppender(LogAppender::ptr appender) {
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender) {
    for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it)
    {
        if(*it == appender)
        {
            m_appenders.erase(it);
            break;
        }
    }
}
}
