#include <string>
#include <gtest/gtest.h>
#include <log.h>
#include <regex>


TEST(LogTest, LogLeveltoString) {
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::DEBUG),
                 "DEBUG");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::WARN),
                 "WARN");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::INFO),
                 "INFO");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::ERROR),
                 "ERROR");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::FATAL),
                 "FATAL");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::UNKNOW),
                 "UNKNOW");
    EXPECT_STREQ(
        sylar::LogLevel::toString(static_cast<sylar::LogLevel::Level>(1000)),
        "UNKNOW");
}

TEST(LogTest, LogOutTest) {
    // test defualt format log output
    using namespace sylar;
    const char* logger_name = "LogOutTest";

    Logger::ptr logger(std::make_shared<sylar::Logger>(logger_name));
    auto string_log_appender = std::make_shared<sylar::StringLogAppender>();
    logger->addAppender(sylar::LogAppender::ptr(string_log_appender));

    const char* file_name   = "test.cc";
    int32_t line            = 10;
    uint32_t thread_id      = 0;
    uint32_t elapsed_ms     = 1;
    uint32_t fiber_id       = 2;
    uint64_t _time          = static_cast<uint64_t>(time(nullptr));
    const char* thread_name = "null";
    LogLevel::Level level   = sylar::LogLevel::Level::DEBUG;

    sylar::LogEvent::ptr event(new sylar::LogEvent(logger,
                                                   level,
                                                   file_name,
                                                   line,
                                                   elapsed_ms,
                                                   thread_id,
                                                   fiber_id,
                                                   _time,
                                                   thread_name));
    event->getSS() << "log";
    logger->log(level, event);

    std::string string_log = string_log_appender->log_sstream.str();
    std::smatch result;
    std::regex pattern("(\\d+-\\d+-\\d+\\s\\d+:\\d+:\\d+)\\s+(.*)\\n");


    if (std::regex_match(string_log, result, pattern)) {
        // part1 for time fmt check
        struct tm tm;
        time_t time = static_cast<time_t>(event->getTime());
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
        EXPECT_STREQ(result.str(1).c_str(), buf);

        // part2 for rest check
        auto part2 = result.str(2);
        std::stringstream str_result;
        str_result << thread_id << '\t' << thread_name << '\t' << fiber_id
                   << '\t' << '[' << LogLevel::toString(level) << ']' << '\t'
                   << '[' << logger_name << ']' << '\t' << '<' << file_name
                   << ':' << line << '>' << '\t' << "log";
        auto s = str_result.str();
        EXPECT_STREQ(part2.c_str(), s.c_str());
    } else {
        EXPECT_FALSE(true);
    }
}

TEST(LogTest, LogFmtTest) {
    const char* logger_name = "LogOutTest";

    sylar::Logger::ptr logger(std::make_shared<sylar::Logger>(logger_name));

    auto string_log_appender = std::make_shared<sylar::StringLogAppender>();
    string_log_appender->setFormatter(
        std::make_shared<sylar::LogFormatter>("%t%T%m%n"));
    logger->addAppender(string_log_appender);
    const char* msg = "log msg";
    SYLAR_LOG_INFO(logger) << msg;

    std::stringstream ss;
    ss << sylar::GetThreadId() << '\t' << msg << '\n';
    EXPECT_STREQ(string_log_appender->log_sstream.str().c_str(),
                 ss.str().c_str());
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
