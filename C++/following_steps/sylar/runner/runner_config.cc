#include "config.h"
#include <yaml-cpp/yaml.h>

sylar::ConfigVar<int>::ptr g_int_value_config;
sylar::ConfigVar<float>::ptr g_float_value_config;

void initGlobal() {
    g_int_value_config = sylar::Config::loopUp(
        "system.port", static_cast<int>(8080), "system port");
    g_float_value_config = sylar::Config::loopUp(
        "system.port", static_cast<float>(10.2f), "system port");
}

void print_yaml(const YAML::Node& node, int level) {
    if (node.IsScalar()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    }
    else if (node.IsNull()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    }
    else if (node.IsMap()) {
        for (auto it = node.begin();
            it != node.end(); ++it) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
                << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    }
    else if (node.IsSequence()) {
        for (size_t i = 0; i < node.size(); ++i) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
                << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("./log.yml");
    print_yaml(root, 0);
    //SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root;
}

int main() {
    try {
        initGlobal();

        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
    } catch (std::invalid_argument& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())
            << "look for wrong type; " << e.what();
    } catch (std::exception& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << e.what();
    }

    try {
        test_yaml();
    } catch (YAML::BadFile& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "log.yml" << e.what();
    } catch (YAML::ParserException& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) <<"parse log.yml failed! " <<  e.what();
    } catch (std::exception& e) {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << e.what();
    }


    return 0;
}