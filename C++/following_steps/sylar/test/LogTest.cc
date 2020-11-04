#include <gtest/gtest.h>
#include <log.h>
#include <regex>
#include <bits/basic_string.h>


TEST(LogTest, LogLeveltoString) {
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::DEBUG), "DEBUG");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::WARNN), "WARNN");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::INFO), "INFO");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::ERROR), "ERROR");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::FATAL), "FATAL");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::UNKNOW), "UNKNOW");
    EXPECT_STREQ(sylar::LogLevel::toString(static_cast<sylar::LogLevel::Level>(1000)), "UNKNOW");

}

TEST(LogTest, LogOutTest) {
    // note that now log is under developing , test need change later.
    using namespace sylar;
    sylar::Logger::ptr logger(std::make_shared<sylar::Logger>());
    auto string_log_appender = std::make_shared<sylar::StringLogAppender>();
    logger->addAppender(sylar::LogAppender::ptr(string_log_appender));

    const char* file_name = "test.cc";
    int32_t line = 10;
    uint32_t thread_id = 0;
    uint32_t elapsed_ms = 1;
    uint32_t fiber_id = 2;
    uint64_t _time = time(0);
    LogLevel::Level level = sylar::LogLevel::Level::DEBUG;

    sylar::LogEvent::ptr event(new sylar::LogEvent(file_name, line, thread_id, elapsed_ms, fiber_id, _time));
    logger->log(level, event);

    std::string string_log = string_log_appender->log_sstream.str();
    std::smatch result;
    std::regex pattern("(\\d{0,15}) (.*)\\n");
    
    if(std::regex_match(string_log, result, pattern)) {
        auto part1 = result.str(1);
        char* ptr;
        uint64_t time_result = strtoull(part1.c_str(), &ptr, 10);
        EXPECT_EQ(_time, time_result);


        auto part2 = result.str(2);
        std::string str_result{'['};
        str_result.append(LogLevel::toString(level));
        str_result.append("] ");
        str_result.append(file_name);
        str_result.push_back(':');
        str_result.append(std::to_string(line));
        str_result.push_back(' ');
        EXPECT_STREQ(part2.c_str(), str_result.c_str());
    } else {
        EXPECT_FALSE(true);
    }

}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}