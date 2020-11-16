#include "config.h"

sylar::ConfigVar<int>::ptr g_int_value_config;

void initGlobal() {
    g_int_value_config = sylar::Config::loopUp(
        "system port", static_cast<int>(8080), "system port");
}

int main() {
    try {
        initGlobal();

        SYLAY_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
        SYLAY_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->toString();
    } catch (std::invalid_argument& e) {
        SYLAY_LOG_ERROR(SYLAR_LOG_ROOT())
            << "look for wrong type; " << e.what();
    } catch (std::exception& e) {
        SYLAY_LOG_ERROR(SYLAR_LOG_ROOT()) << e.what();
    }


    return 0;
}