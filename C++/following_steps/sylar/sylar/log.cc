#include "log.h"
#include <iostream>

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

StdoutLogAppender::StdoutLogAppender() {

}

void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level)
    {
        std::cout <<  m_formatter->format(event);
    }
}

bool FileLogAppender::reopen() {
    if (m_filestream)
    {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !m_filestream;
}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level)
    {
        m_filestream << m_formatter->format(event);
    }
}
}
