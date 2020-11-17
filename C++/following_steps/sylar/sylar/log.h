#pragma once

#include <memory>
#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include "util.h"
#include "singleton.h"

#define SYLAR_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrapper(std::make_shared<sylar::LogEvent>(logger, level, __FILE__, __LINE__, 0, sylar::GetThreadId(), \
                sylar::GetFiberId(), time(0))).getSS()


#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::DEBUG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::INFO)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::FATAL )

#define SYLAR_LOG_ROOT() sylar::LoggerMgr::getInstance()->getRoot()
#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::getInstance()->getLogger(name)

namespace sylar {
class Logger;
class LoggerManager

struct LogLevel
{
    enum class Level
    {
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* toString(LogLevel::Level level);
};


/**
 * @brief 日志事件
 *
 */
class LogEvent
{
private:
    /* data */
    const char* m_file   = nullptr; //文件号
    int32_t m_line       = 0;       // 行号
    uint32_t m_threadId  = 0;       // 线程ID
    uint32_t m_elapsedMs = 0;       // 程序启动经过时间
    uint32_t m_fiberid   = 0;       // 协程ID
    uint64_t m_time;                // 时间戳
    std::stringstream m_content_stream;

    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
public:

    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent(std::shared_ptr<Logger> logger,
             LogLevel::Level level,
             const char* file,
             int32_t line,
             uint32_t elapsed_ms,
             uint32_t thread_id,
             uint32_t fiberid,
             uint64_t time);

    ~LogEvent() = default;

    auto getFile() const -> const char* {
        return m_file;
    }

    auto getLine() const -> int32_t {
        return m_line;
    }

    auto getThreadId() const -> uint32_t {
        return m_threadId;
    }

    auto getElapsedMs() const -> uint32_t {
        return m_elapsedMs;
    }

    auto getFiberid() const -> uint32_t {
        return m_fiberid;
    }

    auto getTime() const -> uint64_t {
        return m_time;
    }

    auto getContent() const -> std::string {
        return m_content_stream.str();
    }

    std::stringstream& getSS() { return m_content_stream; }
    std::shared_ptr<Logger> getLogger() { return m_logger; }

    auto getLevel() const -> LogLevel::Level {
        return m_level;
    }
};

class LogEventWrapper
{
public:
    LogEventWrapper(LogEvent::ptr e);

    ~LogEventWrapper();

    std::stringstream& getSS();
private:
    LogEvent::ptr m_event;
};


/**
 * @brief
 *
 */
class LogFormatter
{
private:
    class FormatItem
    {
    public:
        typedef std::shared_ptr<FormatItem> ptr;

        FormatItem(const std::string& fmt = "") {
        }

        virtual ~FormatItem() = 0;
        virtual void format(std::ostream& os,
                            std::shared_ptr<Logger> logger,
                            LogLevel::Level level,
                            LogEvent::ptr event) = 0;
    };

    friend struct LevelFormatItem;
    friend struct MessageFormatItem;
    friend struct ElapseFormatItem;
    friend struct NameFormatItem;
    friend struct ThreadIdFormatItem;
    friend struct FiberIdFormatItem;
    friend struct DateTimeFormatItem;
    friend struct FilenameFormatItem;
    friend struct LineFormatItem;
    friend struct NewLineFormatItem;
    friend struct StringFormatItem;
    friend struct TabFormatItem;

    void init();
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(std::shared_ptr<Logger> logger,
                       LogLevel::Level level,
                       LogEvent::ptr event);

    LogFormatter(const std::string& str);

    ~LogFormatter() {
    }

private:
    /* data */
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
};


/**
 * @brief 日志输出器
 *
 */
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;

    virtual ~LogAppender();

    virtual void log(std::shared_ptr<Logger> logger,
                     LogLevel::Level level,
                     LogEvent::ptr event) = 0;

    auto Formatter() const -> LogFormatter::ptr {
        return m_formatter;
    }

    auto setFormatter(const LogFormatter::ptr& formatter) -> void {
        this->m_formatter = formatter;
    }


    auto getLevel() const -> LogLevel::Level {
        return m_level;
    }


    auto setLevel(LogLevel::Level level) -> void {
        this->m_level = level;
    }

protected:
    LogLevel::Level m_level = LogLevel::Level::DEBUG;

    LogFormatter::ptr m_formatter;
};


/**
 * @brief 日志器
 *
 */
class Logger : public std::enable_shared_from_this<Logger>
{
friend class LoggerManager;
private:
    /* data */

public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");

    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);

    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level val) { m_level = val; }

    const std::string& getName() const { return m_name; }
private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;
    LogFormatter::ptr m_formatter;
    Logger::ptr m_root;
};


class StdoutLogAppender : public LogAppender
{
private:
    /* data */
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;

    StdoutLogAppender(/* args */);

    ~StdoutLogAppender() {
    }

    void log(std::shared_ptr<Logger> logger,
             LogLevel::Level level,
             LogEvent::ptr event) override;
};

class FileLogAppender : public LogAppender
{
private:
    /* data */
    std::string m_filename;
    std::ofstream m_filestream;
public:
    typedef std::shared_ptr<FileLogAppender> ptr;

    FileLogAppender(const std::string& filename);

    ~FileLogAppender() {
    }

    bool reopen();

    void log(std::shared_ptr<Logger> logger,
             LogLevel::Level level,
             LogEvent::ptr event) override;
};

class LoggerManager
{
public:
    LoggerManager();

    Logger::ptr getLogger(const std::string& name);
    void init();

    Logger::ptr getRoot() { return m_root; }
private:
    std::unordered_map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

using LoggerMgr = sylar::Singleton<LoggerManager>;

namespace {
/**
 * @brief 用于测试
*/
struct StringLogAppender : public LogAppender
{
    std::stringstream log_sstream;

    void log(std::shared_ptr<Logger> logger,
             LogLevel::Level level,
             LogEvent::ptr event) override {
        if (level >= m_level) {
            log_sstream << m_formatter->format(logger, level, event);
        }
    }
};


}
} // namespace sylar
