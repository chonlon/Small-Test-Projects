#include <gtest/gtest.h>
#include <log.h>


TEST(LogTest, LogLeveltoString) {
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::DEBUG), "DEBUG");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::WARNN), "WARNN");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::INFO), "INFO");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::ERROR), "ERROR");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::FATAL), "FATAL");
    EXPECT_STREQ(sylar::LogLevel::toString(sylar::LogLevel::Level::UNKNOW), "UNKNOW");
    EXPECT_STREQ(sylar::LogLevel::toString(static_cast<sylar::LogLevel::Level>(1000)), "UNKNOW");

}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}