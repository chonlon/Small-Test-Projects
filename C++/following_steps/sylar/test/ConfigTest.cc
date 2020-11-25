#include <gtest/gtest.h>
#include <config.h>
#include <string>

sylar::ConfigVar<int>::ptr int_value;
sylar::ConfigVar<std::string>::ptr string_value;
sylar::ConfigVar<std::vector<int>>::ptr vector_value;


TEST(ConfigTest, DefaultTest) {
    int origin_int_value = 8080;
    std::string origin_string_value = "this is a test string";
    std::vector<int> origin_vector_value{{1, 2, 3}};

    {
        int_value = sylar::Config::lookUp(
            "system.int", static_cast<int>(origin_int_value), "system int");
        string_value = sylar::Config::lookUp(
            "system.string", static_cast<std::string>(origin_string_value), "system string");
        vector_value = sylar::Config::lookUp(
            "system.int_vec", std::vector<int>(origin_vector_value), "system vec");
    }

    {
        EXPECT_EQ(int_value->getValue(), origin_int_value);
        EXPECT_STREQ(int_value->getDescription().c_str(), "system int");
        EXPECT_EQ(string_value->getValue(), origin_string_value);
        EXPECT_STREQ(string_value->getDescription().c_str(), "system string");
        EXPECT_EQ(vector_value->getValue(), origin_vector_value);
        EXPECT_STREQ(vector_value->getDescription().c_str(), "system vec");
    }
}

TEST(ConfigTest, YamlLoad) {
    std::string test_yml = R"(
system:
    int: 9900
    string: 'this is a string from yaml'
    int_vec: [10,20,30,40]
    )";
    auto yaml_root       = YAML::Load(test_yml);

    sylar::Config::LoadFromYaml(yaml_root);

    int changed_int_value            = 9900;
    std::string changed_string_value = "this is a string from yaml";
    std::vector<int> changed_vector_value{{10, 20, 30, 40}};

    {
        EXPECT_EQ(int_value->getValue(), changed_int_value);
        EXPECT_EQ(string_value->getValue(), changed_string_value);
        EXPECT_EQ(vector_value->getValue(), changed_vector_value);
    }
}