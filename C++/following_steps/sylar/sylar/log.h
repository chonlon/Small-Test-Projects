#pragma once

#include <memory>
#include <string>

namespace sylar {

/**
 * @brief 日志事件
 *
 */
class LogEvent
{
private:
    /* data */
    const char* m_file     = nullptr;  //文件号
    int32_t m_line         = 0;        // 行号
    uint32_t m_threadId    = 0;        // 线程ID
    uint32_t m_elapsedMs   = 0;        // 程序启动经过事件
    uint32_t m_fiberid     = 0;        // 协程ID
    std::string m_content;             // 时间戳
    uint64_t m_time;

public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent(/* args */) {}
    ~LogEvent() {}
};

struct LogLevel
{
    enum class Level
    {
        DEBUG = 1,
        INFO  = 2,
        WARNN = 3,
        ERROR = 4,
        FATAL = 5
    };
};


/**
 * @brief 日志输出器
 *
 */
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;

    virtual ~LogAppender() = 0;

    void log(LogLevel::Level level, LogEvent::ptr event);

private:
    LogLevel::Level m_level;
};

/**
 * @brief
 *
 */
class LogFormatter
{
private:
    /* data */
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(LogEvent::ptr event);

    LogFormatter(/* args */) {}
    ~LogFormatter() {}
};

/**
 * @brief 日志器
 *
 */
class Logger
{
private:
    /* data */

public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");

    void log(LogLevel::Level level, const LogEvent& event);

private:
    std::string m_name;
    LogLevel::Level m_level;
    LogAppender::ptr m_appder;
};

class StdoutLogAppender : public LogAppender
{
private:
    /* data */
public:
    StdoutLogAppender(/* args */) {}
    ~StdoutLogAppender() {}
};

class FileLogAppender : public LogAppender
{
private:
    /* data */
public:
    FileLogAppender(/* args */) {}
    ~FileLogAppender() {}
};


}  // namespace sylar