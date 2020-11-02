#include "log.h"
#include <iostream>

namespace sylar {

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

void LogFormatter::init() {
    std::vector<std::tuple<std::string, std::string, int>> vec;
    std::string nstr;
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

        while (++n < size) {
            if (isspace(m_pattern[n])) {
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
                    fmt        = m_pattern.substr(fmt_begin + 1, n - fmt_begin);
                    fmt_status = 2;
                    ++n;
                    continue;
                }
            }

        }

        if (fmt_status == 0) {
            if (!nstr.empty()) {
                vec.emplace_back(nstr, "", 0);
            }
            str = m_pattern.substr(i + 1, n - i - 1);
            vec.emplace_back(str, fmt, 1);
            i = n;
        } else if (fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - " <<
                m_pattern.substr(i) << '\n';
            vec.emplace_back("<<pattern_error>>", fmt, 0);
        } else if (fmt_status == 2) {
            if (!nstr.empty()) {
                vec.emplace_back(nstr, "", 0);
            }
            vec.emplace_back(str, fmt, 1);
            i = n;
        }


    }
    if (!nstr.empty()) {
        vec.emplace_back(nstr, "", 0);
    }

    //%m 消息体
    //%p level
    //%r 启动后的时间
    //%c 日志名称
    //%t 线程id
    //%n 回车换行
    //%d 时间
    //%f 文件名
    //%l 行号


}

std::string LogFormatter::format(LogLevel::Level level, LogEvent::ptr event) {
    std::stringstream ss;
    for (auto& i : m_items) {
        i->format(ss, level, event);
    }
    return ss.str();
}

LogAppender::~LogAppender() {
}

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
    for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
        if (*it == appender) {
            m_appenders.erase(it);
            break;
        }
    }
}

StdoutLogAppender::StdoutLogAppender() {

}

void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        std::cout << m_formatter->format(level, event);
    }
}

bool FileLogAppender::reopen() {
    if (m_filestream) {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !m_filestream;
}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        m_filestream << m_formatter->format(level, event);
    }
}

struct MessageFormatItem : public LogFormatter::FormatItem
{
    void format(std::ostream& os,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << event->getContent();
    }
};

struct LevelFormatItem : public LogFormatter::FormatItem
{
    void format(std::ostream& os,
                LogLevel::Level level,
                LogEvent::ptr event) override {
        os << LogLevel::toString(level);
    }
};

}
