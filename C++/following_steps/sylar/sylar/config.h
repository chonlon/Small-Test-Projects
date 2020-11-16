#pragma once
#include "log.h"


#include <boost/lexical_cast.hpp>
#include <exception>
#include <map>
#include <memory>
#include <sstream>

namespace sylar {
class ConfigVarBase
{
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;


    ConfigVarBase(const std::string& name, const std::string& description)
        : m_name{name}, m_description{description} {}

    virtual ~ConfigVarBase() = default;

    const std::string& getName() const {
        return m_name;
    }

    const std::string& getDescription() const {
        return m_description;
    }

    virtual std::string toString()                  = 0;
    virtual bool fromString(const std::string& str) = 0;

protected:
    std::string m_name;
    std::string m_description;
};

template <typename T>
class ConfigVar : public ConfigVarBase
{
public:
    typedef std::shared_ptr<ConfigVar> ptr;


    ConfigVar(const std::string& name,
              const std::string& description,
              const T& val)
        : ConfigVarBase{name, description}, m_val{val} {}


    std::string toString() override {
        try {
            return boost::lexical_cast<std::string>(m_val);
        } catch (std::exception& e) {
            SYLAY_LOG_ERROR(SYLAR_LOG_ROOT())
                << __FUNCTION__ << " expection " << e.what()
                << " convert: " << typeid(m_val).name() << " to string";
        }
        return "";
    };

    bool fromString(const std::string& str) override {
        try {
            m_val = boost::lexical_cast<T>(str);
            return true;
        } catch (std::exception& e) {
            SYLAY_LOG_ERROR(SYLAR_LOG_ROOT())
                << __FUNCTION__ << " expection " << e.what()
                << " convert: string to " << typeid(m_val).name();
        }
        return false;
    }

    const T& getValue() const {
        return m_val;
    }
    void setValue(const T& v) {
        m_val = v;
    }

private:
    T m_val;
};

class Config
{
public:
    typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;

    /**
     * \brief 创建/查找给定key的数据, 如果查找失败, 使用默认值创建数据节点
     * \tparam T 节点数据类型
     * \param name key名
     * \param default_val 如果查找失败使用的默认值
     * \param description
     * \exception arg: invalid_argument
     * \exception bad_alloc: bad_alloc from map and make_shareed
     * \return 返回一个配置节点数据指针
     */
    template <typename T>
    static typename ConfigVar<T>::ptr loopUp(
        const std::string& name,
        const T& default_val,
        const std::string& description = "") {
        auto tmp = loopUp<T>(name);
        if (tmp) {
            SYLAY_LOG_INFO(SYLAR_LOG_ROOT())
                << "Lookup name=" << name << " exits";
            return tmp;
        }
        if (name.find_first_not_of("abcdefghikjlmnopqrstuvwxyz._012345678 ") !=
            std::string::npos) {
            SYLAY_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name invalid " << name;
            throw std::invalid_argument(name);
        }
        auto v = std::make_shared<ConfigVar<T>>(name, description, default_val);
        s_datas[name] = v;
        return v;
    }

    template <typename T>
    static typename ConfigVar<T>::ptr loopUp(const std::string& name) {
        auto it = s_datas.find(name);
        if (it == s_datas.end()) {
            return nullptr;
        }

        return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
    }

private:
    static ConfigVarMap s_datas;
};

}  // namespace sylar
