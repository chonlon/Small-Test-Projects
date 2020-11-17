#include "config.h"
#include <yaml-cpp/yaml.h>

sylar::ConfigVar<int>::ptr g_int_value_config;
sylar::ConfigVar<float>::ptr g_float_value_config;
sylar::ConfigVar<std::vector<int>>::ptr g_vector_value_config;

void initGlobal() {
    g_int_value_config = sylar::Config::loopUp(
        "system.port", static_cast<int>(8080), "system port");
    g_float_value_config = sylar::Config::loopUp(
        "system.value", static_cast<float>(10.2f), "system port");
    g_vector_value_config = sylar::Config::loopUp(
        "system.int_vec", std::vector<int>({1, 2, 3}), "system vec");
}

void print_yaml(const YAML::Node& node, int level) {
    //auto i = node.as<std::vector<int>>();
    if (node.IsScalar()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
            << std::string(level * 4, ' ') << node.Scalar() << " - "
            << node.Type() << " - " << level;
    } else if (node.IsNull()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
            << std::string(level * 4, ' ') << "NULL - " << node.Type() << " - "
            << level;
    } else if (node.IsMap()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
                << std::string(level * 4, ' ') << it->first << " - "
                << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if (node.IsSequence()) {
        for (size_t i = 0; i < node.size(); ++i) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
                << std::string(level * 4, ' ') << i << " - " << node[i].Type()
                << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("./log.yml");
    print_yaml(root, 0);
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root;
}

void test_config() {
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
        << g_int_value_config->getDescription()
        << "before: " << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
        << g_int_value_config->getDescription()
        << "before: " << g_float_value_config->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
        << g_vector_value_config->getDescription()
        << "before: " << g_vector_value_config->toString();

    auto v = g_vector_value_config->getValue();
    for (auto i : v) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
            << g_vector_value_config->getDescription() << " " << i;
    }

    auto root = YAML::LoadFile("./log.yml");
#if 0
    sylar::Config::LoadFromYaml(root);
#else
    sylar::Config::LoadFromYaml_2(root);
#endif


    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
        << g_int_value_config->getDescription()
        << "after: " << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
        << g_int_value_config->getDescription()
        << "after: " << g_float_value_config->toString();

    auto v2 = g_vector_value_config->getValue();
    for (auto i : v2) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
            << g_vector_value_config->getDescription() << " " << i;
    }
}

int main() {
    try {
        initGlobal();
        test_config();
    } catch (std::invalid_argument& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())
            << "look for wrong type; " << e.what();
    } catch (std::exception& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << e.what();
    }
#if 0
    try {
        test_yaml();
    } catch (YAML::BadFile& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "log.yml" << e.what();
    } catch (YAML::ParserException& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) <<"parse log.yml failed! " <<  e.what();
    } catch (std::exception& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << e.what();
    }

#endif

    return 0;
}