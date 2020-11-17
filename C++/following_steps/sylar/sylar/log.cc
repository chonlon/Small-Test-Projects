#include "log.h"
#include "config.h"

#include <functional>
#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
#include <unordered_map>

namespace sylar {

struct MessageFormatItem : public LogFormatter::FormatItem
{
    MessageFormatItem(const std::string& str) : FormatItem{str} {}

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
    LevelFormatItem(const std::string& str) : FormatItem{str} {}

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
    ElapseFormatItem(const std::string& str) : FormatItem{str} {}

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
    NameFormatItem(const std::string& str) : FormatItem{str} {}

    virtual ~NameFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getLogger()->getName();
    }
};

struct ThreadIdFormatItem : public LogFormatter::FormatItem
{
    ThreadIdFormatItem(const std::string& str) : FormatItem{str} {}

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
    FiberIdFormatItem(const std::string& str) : FormatItem{str} {}

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
    DateTimeFormatItem(const std::string& format) : m_format{format} {
        if (m_format.empty()) {
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
    FilenameFormatItem(const std::string& str = "") : FormatItem{str} {}

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
    LineFormatItem(const std::string& str = "") : FormatItem{str} {}

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
    NewLineFormatItem(const std::string& str = "") : FormatItem{str} {}

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
    StringFormatItem(const std::string& str = "")
        : FormatItem{str}, m_string{str} {}

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

struct TabFormatItem : LogFormatter::FormatItem
{
    TabFormatItem(const std::string& str = "") : FormatItem{str} {}

    virtual ~TabFormatItem() = default;

    void format(std::ostream& os,
                std::shared_ptr<Logger> logger,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << '\t';
    }
};


LogEvent::LogEvent(std::shared_ptr<Logger> logger,
                   LogLevel::Level level,
                   const char* file,
                   int32_t line,
                   uint32_t elapsed_ms,
                   uint32_t thread_id,
                   uint32_t fiberid,
                   uint64_t time)
    : m_file{file},
      m_line{line},
      m_threadId{thread_id},
      m_elapsedMs{elapsed_ms},
      m_fiberid{fiberid},
      m_time{time},
      m_logger{logger},
      m_level{level} {}


LogEventWrapper::LogEventWrapper(LogEvent::ptr e) : m_event{e} {}

LogEventWrapper::~LogEventWrapper() {
    m_event->getLogger()->log(m_event->getLevel(), m_event);
}

std::stringstream& LogEventWrapper::getSS() {
    return m_event->getSS();
}

const char* LogLevel::toString(LogLevel::Level level) {
    switch (level) {
#define XX(name)                \
    case LogLevel::Level::name: \
        return #name;           \
        break;

        XX(DEBUG)
        XX(INFO)
        XX(WARN)
        XX(ERROR)
        XX(FATAL)
#undef XX
        default:
            return "UNKNOW";
    }
}

LogFormatter::FormatItem::~FormatItem() {}

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

        while (n < m_pattern.size()) {
            if (!fmt_status &&
                (!isalpha(m_pattern[n]) && m_pattern[n] != '{' &&
                 m_pattern[n] != '}')) {
                str = m_pattern.substr(i + 1, n - i - 1);
                break;
            }
            if (fmt_status == 0) {
                if (m_pattern[n] == '{') {
                    str        = m_pattern.substr(i + 1, n - i - 1);
                    fmt_status = 1;  //解析格式
                    fmt_begin  = n;
                    ++n;
                    continue;
                }
            } else if (fmt_status == 1) {
                if (m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                    fmt_status = 0;
                    ++n;
                    break;
                }
            }
            ++n;
            if (n == m_pattern.size()) {
                if (str.empty()) {
                    str = m_pattern.substr(i + 1);
                }
            }
        }

        if (fmt_status == 0) {
            if (!nstr.empty()) {
                vec.emplace_back(nstr, "", 0);
                nstr.clear();
            }
            // str = m_pattern.substr(i + 1, n - i - 1);
            vec.emplace_back(str, fmt, 1);
            i = n - 1;
        } else if (fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - "
                      << m_pattern.substr(i) << '\n';
            vec.emplace_back("<<pattern_error>>", fmt, 0);
        } else if (fmt_status == 2) {
            if (!nstr.empty()) {
                vec.emplace_back(nstr, "", 0);
            }
            vec.emplace_back(str, fmt, 1);
            i = n - 1;
        }
    }

    if (!nstr.empty()) {
        vec.emplace_back(nstr, "", 0);
    }

    static std::unordered_map<
        std::string,
        std::function<FormatItem::ptr(const std::string& str)>>
        s_format_items = {
#define XX(str, C)                           \
    {                                        \
#str, [](const std::string& fmt) {   \
            return std::make_shared<C>(fmt); \
        }                                    \
    }

            XX(m, MessageFormatItem),
            XX(p, LevelFormatItem),
            XX(r, ElapseFormatItem),
            XX(c, NameFormatItem),
            XX(t, ThreadIdFormatItem),
            XX(n, NewLineFormatItem),
            XX(d, DateTimeFormatItem),
            XX(f, FilenameFormatItem),
            XX(l, LineFormatItem),
            XX(T, TabFormatItem),
            XX(F, FiberIdFormatItem)
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
                m_items.emplace_back(std::make_shared<StringFormatItem>(
                    "<<error_format%" + std::get<0>(i) + ">>"));
            } else {
                m_items.emplace_back(it->second(std::get<1>(i)));
            }
        }
        //     std::cout << std::get<0>(i) << " - " << std::get<1>(i) << " - "
        //     <<
        //         std::get<2>(i) << std::endl;
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

LogFormatter::LogFormatter(const std::string& str) : m_pattern{str} {
    init();
}

LogAppender::~LogAppender() {}

Logger::Logger(const std::string& name)
    : m_name{name}, m_level{LogLevel::Level::DEBUG} {
    m_formatter.reset(new LogFormatter(
        "%d{%Y-%m-%d %H:%M:%S}%T%t%T%F%T[%p]%T[%c]%T<%f:%l>%T%m%n"));
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        auto self = shared_from_this();
        if (m_appenders.empty()) {
            for (auto& i : m_appenders) {
                i->log(self, level, event);
            }
        } else {
            m_root->log(level, event);
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
    log(LogLevel::Level::WARN, event);
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

StdoutLogAppender::StdoutLogAppender() {}

void StdoutLogAppender::log(std::shared_ptr<Logger> logger,
                            LogLevel::Level level,
                            LogEvent::ptr event) {
    if (level >= m_level) {
        std::cout << m_formatter->format(logger, level, event);
    }
}

FileLogAppender::FileLogAppender(const std::string& filename)
    : m_filename{filename} {
    reopen();
}

bool FileLogAppender::reopen() {
    if (m_filestream) {
        m_filestream.close();
    }
    m_filestream.open(m_filename, std::ios_base::app);
    return !m_filestream;
}

void FileLogAppender::log(std::shared_ptr<Logger> logger,
                          LogLevel::Level level,
                          LogEvent::ptr event) {
    if (level >= m_level) {
        m_filestream << m_formatter->format(logger, level, event);
    }
}

LoggerManager::LoggerManager() {
    m_root = std::make_shared<Logger>("root");

    m_root->addAppender(std::make_shared<StdoutLogAppender>());
    init();
}

Logger::ptr LoggerManager::getLogger(const std::string& name) {
    auto it = m_loggers.find(name);
    if (it == m_loggers.end()) {
        return it->second;
    }

    auto logger     = std::make_shared<Logger>(name);
    logger->m_root  = m_root;
    m_loggers[name] = logger;
    return logger;
}

struct LogAppenderDefine
{
    enum class Type
    {
        Unknown,
        File,
        Stdout
    };
    Type type             = Type::Unknown;
    LogLevel::Level level = LogLevel::Level::UNKNOW std::string formatter;
    std::string file;

    bool operator==(const LogAppenderDefine& oth) const {
        return type == oth.type && level == oth.level &&
            formatter == oth.formatter && file == oth.file;
    }
};

struct LogDefine
{
    std::string name;
    LogLevel::Level level = LogLevel::Level::UNKNOW;
    std::string formatter;
    std::vector<LogAppenderDefine> appenders;

    bool operator==(const LogDefine& oth) const {
        return name == oth.name && level == oth.level &&
            formatter == oth.formatter && appenders == appenders;
    }

    bool operator<(const LogDefine& oth) const {
        return name < oth.name;
    } 
};

sylar::ConfigVar<std::set<LogDefine>>::ptr g_log_defines =
    sylar::Config::loopUp("logs", std::set<LogDefine>(), "logs config");

struct LogIniter
{
    LogIniter() {
        g_log_defines->addListener(0xF1E231, [](const std::set<LogDefine>& old_value, const std::set<LogDefine>& new_value)
        {
            //新增
            for(auto& i : new_value) {
                auto it = old_value.find(i);
                if(it == old_value.end()) {
                    // 新增logger

                } else {
                    if(i != *it) {
                        // 修改的logger
                    }
                }
            }

            for(auto& i : old_value) {
                auto it = new_value.find(i);
                if(it == new_value.end()) {
                    // 删除logger

                }
            }
            //修改
            //删除
        });
    }
};

static LogIniter ___log_init;

void LoggerManager::init() {}


}  // namespace sylar
