#pragma once

#include <memory>
#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdint>

namespace sylar {
class Logger;

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
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent(const char* file,
             int32_t line,
             uint32_t thread_id,
             uint32_t elapsed_ms,
             uint32_t fiberid,
             uint64_t time);

    ~LogEvent() {
    }

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

};

struct LogLevel
{
    enum class Level
    {
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARNN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* toString(LogLevel::Level level);
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
private:
    /* data */

public:
    typedef std::shared_ptr<Logger> ptr;

    explicit Logger(const std::string& name = "root");

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

    FileLogAppender(/* args */) {
    }

    ~FileLogAppender() {
    }

    bool reopen();

    void log(std::shared_ptr<Logger> logger,
             LogLevel::Level level,
             LogEvent::ptr event) override;
};

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
