#include "log.h"

#include <functional>
#include <iostream>
#include <unordered_map>
#include <time.h>
#include <string.h>

namespace sylar {

struct MessageFormatItem : public LogFormatter::FormatItem
{
    MessageFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~MessageFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getContent();
    }
};

struct LevelFormatItem : public LogFormatter::FormatItem
{
    LevelFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~LevelFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << LogLevel::toString(level);
    }
};

struct ElapseFormatItem : public LogFormatter::FormatItem
{
    ElapseFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~ElapseFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getElapsedMs();
    }
};

struct NameFormatItem : public LogFormatter::FormatItem
{
    NameFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~NameFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << logger->getName();
    }
};

struct ThreadIdFormatItem : public LogFormatter::FormatItem
{
    ThreadIdFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~ThreadIdFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getThreadId();
    }
};

struct FiberIdFormatItem : public LogFormatter::FormatItem
{
    FiberIdFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~FiberIdFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getFiberid();
    }
};

struct DateTimeFormatItem : public LogFormatter::FormatItem
{
    DateTimeFormatItem(const std::string& format = "%Y:%m:%d %H:%M:%S")
        : m_format{format} {
        if(m_format.empty()) {
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }

    virtual ~DateTimeFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        struct tm tm;
        time_t time = event->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);

        os << buf;
    }

private:
    std::string m_format;
};

struct FilenameFormatItem : public LogFormatter::FormatItem
{
    FilenameFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~FilenameFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getFile();
    }
};

struct LineFormatItem : public LogFormatter::FormatItem
{
    LineFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~LineFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getLine();
    }
};

struct NewLineFormatItem : public LogFormatter::FormatItem
{
    NewLineFormatItem(const std::string& str)
        : FormatItem{str} {
    }

    virtual ~NewLineFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << '\n';
    }
};

struct StringFormatItem : public LogFormatter::FormatItem
{
    StringFormatItem(const std::string& str)
        : FormatItem{str},
          m_string{str} {
    }

    virtual ~StringFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << m_string;
    }

private:
    std::string m_string;
};


LogEvent::LogEvent(const char* file,
                   int32_t line,
                   uint32_t thread_id,
                   uint32_t elapsed_ms,
                   uint32_t fiberid,
                   uint64_t time)
    : m_file{file},
      m_line{line},
      m_threadId{thread_id},
      m_elapsedMs{elapsed_ms},
      m_fiberid{fiberid},
      m_time{time} {
}

const char* LogLevel::toString(LogLevel::Level level) {
    switch (level) {
#define XX(name) \
    case LogLevel::Level::name: \
        return #name; \
        break;

        XX(DEBUG)
        XX(INFO)
        XX(WARNN)
        XX(ERROR)
        XX(FATAL)
#undef XX
        default:
            return "UNKNOW";
    }
}

LogFormatter::FormatItem::~FormatItem() {
}

void LogFormatter::init() {
    std::vector<std::tuple<std::string, std::string, int>> vec;
    std::string nstr{};
    for (std::size_t i = 0, size = m_pattern.size(); i < size; ++i) {
        if (m_pattern[i] != '%') {
            nstr.append(1, m_pattern[i]);
            continue;
        }
        if ((i + 1) < size) {
            if (m_pattern[i + 1] == '%') {
                nstr.append(1, '%');
                continue;
            }
        }

        std::size_t n         = i + 1;
        int fmt_status        = 0;
        std::size_t fmt_begin = 0;
        std::string str;
        std::string fmt;

        while (n < size) {
            if (!isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}') {
                break;
            }
            if (fmt_status == 0) {
                if (m_pattern[n] == '{') {
                    str        = m_pattern.substr(i + 1, n - i - 1);
                    fmt_status = 1; // 
                    ++n;
                    fmt_begin = n;
                    continue;
                }
            }
            if (fmt_status == 1) {
                if (m_pattern[n] == '}') {
                    fmt        = m_pattern.substr(fmt_begin, n - fmt_begin);
                    fmt_status = 2;
                    ++n;
                    break;
                }
            }
            ++n;
            break;// once got pattern, next char is not part of pattern
        }

        if (fmt_status == 0) {
            if (!nstr.empty()) {
                vec.emplace_back(nstr, "", 0);
            }
            str = m_pattern.substr(i + 1, n - i - 1);
            vec.emplace_back(str, fmt, 1);
            i = n - 1;
        } else if (fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - " <<
                m_pattern.substr(i) << '\n';
            vec.emplace_back("<<pattern_error>>", fmt, 0);
        } else if (fmt_status == 2) {
            if (!nstr.empty()) {
                vec.emplace_back(nstr, "", 0);
            }
            vec.emplace_back(str, fmt, 1);
            i = n - 1;
        }
        nstr.clear();
    }
    if (!nstr.empty()) {
        vec.emplace_back(nstr, "", 0);
    }

    static std::unordered_map<std::string, std::function<FormatItem::ptr(
                                  const std::string& str)>> s_format_items = {
#define XX(str, C) \
        {#str, [](const std::string& fmt) {return std::make_shared<C>(fmt);}}

        XX(m, MessageFormatItem),
        XX(p, LevelFormatItem),
        XX(r, ElapseFormatItem),
        XX(c, NameFormatItem),
        XX(t, ThreadIdFormatItem),
        XX(n, NewLineFormatItem),
        XX(d, DateTimeFormatItem),
        XX(f, FilenameFormatItem),
        XX(l, LineFormatItem),
#undef XX
    };

    //%m 消息体
    //%p level
    //%r 启动后的时间
    //%c 日志名称
    //%t 线程id
    //%n 回车换行
    //%d 时间
    //%f 文件名
    //%l 行号

    for (auto& i : vec) {
        if (std::get<2>(i) == 0) {
            m_items.emplace_back(
                std::make_shared<StringFormatItem>(std::get<0>(i)));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if (it == s_format_items.end()) {
                m_items.emplace_back(
                    std::make_shared<StringFormatItem>(
                        "<<error_format%" + std::get<0>(i) + ">>"));
            } else {
                m_items.emplace_back(it->second(std::get<1>(i)));
            }
        }
        std::cout << std::get<0>(i) << " - " << std::get<1>(i) << " - " <<
            std::get<2>(i) << std::endl;
    }
}

std::string LogFormatter::format(std::shared_ptr<Logger> logger,
                                 LogLevel::Level level,
                                 LogEvent::ptr event) {
    std::stringstream ss;
    for (auto& i : m_items) {
        i->format(ss, logger, level, event);
    }
    return ss.str();
}

LogFormatter::LogFormatter(const std::string& str)
    : m_pattern{str} {
    init();
}

LogAppender::~LogAppender() {
}

Logger::Logger(const std::string& name)
    : m_name{name},
      m_level{LogLevel::Level::DEBUG} {
    m_formatter.reset(new LogFormatter("%d [%p] <%f:%l>     %m %n"));
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        auto self = shared_from_this();
        for (auto& i : m_appenders) {
            i->log(self, level, event);
        }
    }
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
    if (!appender->Formatter()) {
        appender->setFormatter(m_formatter);
    }
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender) {
    for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
        if (*it == appender) {
            m_appenders.erase(it);
            break;
        }
    }
}

StdoutLogAppender::StdoutLogAppender() {

}

void StdoutLogAppender::log(std::shared_ptr<Logger> logger,
                            LogLevel::Level level,
                            LogEvent::ptr event) {
    if (level >= m_level) {
        std::cout << m_formatter->format(logger, level, event);
    }
}

bool FileLogAppender::reopen() {
    if (m_filestream) {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !m_filestream;
}

void FileLogAppender::log(std::shared_ptr<Logger> logger,
                          LogLevel::Level level,
                          LogEvent::ptr event) {
    if (level >= m_level) {
        m_filestream << m_formatter->format(logger, level, event);
    }
}



}
