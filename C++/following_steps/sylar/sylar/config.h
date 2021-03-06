#pragma once
#include "log.h"
#include "thread.h"


#include <boost/lexical_cast.hpp>
#include <exception>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <yaml-cpp/yaml.h>

// 这里其实冲突了, 为了不对每种自定义类型写两套偏特化, 所以目前不用yamlcpp方式(保持和视频同样方式)(yamlcpp convert对于stl的常用模板类做了特化, 所以没有自定义类型不用担心)
#define USING_YAML_CPP_CONVERT false

namespace sylar {
class ConfigVarBase
{
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;


    ConfigVarBase(const std::string& name, const std::string& description)
        : m_description{description} {
        std::transform(name.begin(), name.end(), m_name.begin(), ::tolower);
    }

    virtual ~ConfigVarBase() = default;

    const std::string& getName() const {
        return m_name;
    }

    const std::string& getDescription() const {
        return m_description;
    }

    virtual std::string toString()                  = 0;
    virtual bool fromString(const std::string& str) = 0;
#if USING_YAML_CPP_CONVERT

    // 这样的接口其实不好,
    // 可以使用模板的静态多态来做到统一接口(不依赖与具体库/具体配置类型[json/yaml/ini])...
    // 比如fromData(const typename Data& d),
    // 或者直接使用像std::any这样的保存数据的结构.
    virtual bool fromNode(const YAML::Node& node) = 0;
#endif

protected:
    std::string m_name;
    std::string m_description;
};

template <typename FromType, typename ToType>
class LexicalCast
{
public:
    ToType operator()(const FromType& s) {
        return boost::lexical_cast<ToType>(s);
    }
};

template <class T>
class LexicalCast<std::string, std::vector<T>>
{
public:
    std::vector<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::vector<T> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, T>()(ss.str()));
        }
        return vec;
    }
};

template <class T>
class LexicalCast<std::vector<T>, std::string>
{
public:
    std::string operator()(const std::vector<T>& v) {
        YAML::Node node;
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template <class T>
class LexicalCast<std::string, std::list<T>>
{
public:
    std::list<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::list<T> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, T>()(ss.str()));
        }
        return vec;
    }
};

template <class T>
class LexicalCast<std::list<T>, std::string>
{
public:
    std::string operator()(const std::list<T>& v) {
        YAML::Node node;
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template <class T>
class LexicalCast<std::string, std::set<T>>
{
public:
    std::set<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::set<T> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            vec.insert(LexicalCast<std::string, T>()(ss.str()));
        }
        return vec;
    }
};

template <class T>
class LexicalCast<std::set<T>, std::string>
{
public:
    std::string operator()(const std::set<T>& v) {
        YAML::Node node;
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template <class T>
class LexicalCast<std::string, std::unordered_set<T>>
{
public:
    std::unordered_set<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::unordered_set<T> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            vec.insert(LexicalCast<std::string, T>()(ss.str()));
        }
        return vec;
    }
};

template <class T>
class LexicalCast<std::unordered_set<T>, std::string>
{
public:
    std::string operator()(const std::unordered_set<T>& v) {
        YAML::Node node;
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template <class T>
class LexicalCast<std::string, std::map<std::string, T>>
{
public:
    std::map<std::string, T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::map<std::string, T> vec;
        std::stringstream ss;
        for (auto it = node.begin(); it != node.end(); ++it) {
            ss.str("");
            ss << it->second;
            vec.insert(std::make_pair(it->first.Scalar(),
                                      LexicalCast<std::string, T>()(ss.str())));
        }
        return vec;
    }
};

template <class T>
class LexicalCast<std::map<std::string, T>, std::string>
{
public:
    std::string operator()(const std::map<std::string, T>& v) {
        YAML::Node node;
        for (auto& i : v) {
            node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template <class T>
class LexicalCast<std::string, std::unordered_map<std::string, T>>
{
public:
    std::unordered_map<std::string, T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::unordered_map<std::string, T> vec;
        std::stringstream ss;
        for (auto it = node.begin(); it != node.end(); ++it) {
            ss.str("");
            ss << it->second;
            vec.insert(std::make_pair(it->first.Scalar(),
                                      LexicalCast<std::string, T>()(ss.str())));
        }
        return vec;
    }
};

template <class T>
class LexicalCast<std::unordered_map<std::string, T>, std::string>
{
public:
    std::string operator()(const std::unordered_map<std::string, T>& v) {
        YAML::Node node;
        for (auto& i : v) {
            node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};


// FromStr T operator()(const std::string&)
// ToStr std::string operator()(const T&)
template <typename T,
          typename FromStr = LexicalCast<std::string, T>,
          typename ToStr   = LexicalCast<T, std::string>>
class ConfigVar : public ConfigVarBase
{
public:
    typedef RWMutex RWMutexType;
    typedef std::shared_ptr<ConfigVar> ptr;
    typedef std::function<void(const T& old_value, const T& new_value)>
        on_change_cb;

    ConfigVar(const std::string& name,
              const std::string& description,
              const T& val)
        : ConfigVarBase{name, description}, m_val{val} {}


    std::string toString() override {
        try {
            // return boost::lexical_cast<std::string>(m_val);
            RWMutexType::ReadLock locker(m_mutex);
            return ToStr()(m_val);
        } catch (std::exception& e) {
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())
                << __FUNCTION__ << " expection " << e.what()
                << " convert: " << typeid(m_val).name() << " to string";
        }
        return "";
    };

    bool fromString(const std::string& str) override {
        try {
            // m_val = boost::lexical_cast<T>(str);
            setValue(FromStr()(str));
            return true;
        } catch (std::exception& e) {
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())
                << __FUNCTION__ << " expection " << e.what()
                << " convert: string to " << typeid(m_val).name();
        }
        return false;
    }
#if USING_YAML_CPP_CONVERT
    bool fromNode(const YAML::Node& node) override {
        try {
            m_val = node.as<T>();
            return true;
        } catch (std::exception& e) {
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())
                << "load from node failed, type:" << typeid(T).name();
        }
        return false;
    }
#endif

    const T& getValue() const {
        RWMutexType::ReadLock locker(m_mutex);
        return m_val;
    }
    void setValue(const T& v) {
        {
            RWMutexType::ReadLock locker(m_mutex);
            if (v == m_val)
                return;
            for (auto& i : m_cbs) {
                i.second(m_val, v);
            }

        }
        
        {
            RWMutexType::WriteLock locker(m_mutex);
            m_val = v;
        }
        
    }


    uint64_t addListener(on_change_cb cb) {
        static uint64_t s_fun_id = 0;
        RWMutexType::WriteLock locker(m_mutex);
        m_cbs[s_fun_id] = cb;
        return s_fun_id++;
    }

    void delListener(uint64_t key) {
        RWMutexType::WriteLock locker(m_mutex);
        m_cbs.erase(key);
    }

    on_change_cb getListener(uint64_t key) {
        RWMutexType::ReadLock locker(m_mutex);
        auto it = m_cbs.find(key);
        return it == m_cbs.end() ? nullptr : it->second;
    }

    void clearListener() {
        RWMutexType::WriteLock locker(m_mutex);
        m_cbs.clear();
    }

private:
    mutable RWMutexType m_mutex;
    T m_val;

    //变更回调函数组
    std::unordered_map<uint64_t, on_change_cb> m_cbs;
};

class Config
{
public:
    typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;
    typedef RWMutex RWMutexType;
    /**
     * @brief 创建/查找给定key的数据, 如果查找失败, 使用默认值创建数据节点
     * @tparam T 节点数据类型
     * @param name key名
     * @param default_val 如果查找失败使用的默认值
     * @param description
     * @exception arg: invalid_argument
     * @exception bad_alloc: bad_alloc from map and make_shareed
     * @return 返回一个配置节点数据指针
     */
    template <typename T>
    static typename ConfigVar<T>::ptr lookUp(
        const std::string& name,
        const T& default_val,
        const std::string& description = "") {
        
        auto tmp = lookUp<T>(name);
        if (tmp) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT())
                << "Lookup name=" << name << " exits";
            return tmp;
        }
        RWMutexType::WriteLock locker(GetMutex());
        if (name.find_first_not_of("abcdefghikjlmnopqrstuvwxyz._012345678") !=
            std::string::npos) {
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name invalid " << name;
            throw std::invalid_argument(name);
        }
        auto v = std::make_shared<ConfigVar<T>>(name, description, default_val);
        getDatas()[name] = v;
        return v;
    }

    template <typename T>
    static typename ConfigVar<T>::ptr lookUp(const std::string& name) {
        RWMutexType::ReadLock locker(GetMutex());
        auto it = getDatas().find(name);
        if (it == getDatas().end()) {
            return nullptr;
        }

        return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
    }


    static void LoadFromYaml(const YAML::Node& root);

#if USING_YAML_CPP_CONVERT
    /**
     * @brief 使用yaml-cpp提供的convert来做转换,
     * 并且它里面已经定义了stl常用类型的特化,
     * 如果希望解析自定义类型需要对这些类型提供特化 link
     * https://stackoverflow.com/a/53247246/7059225
     * @param root yaml根节点
     *
     */
    static void LoadFromYaml_2(const YAML::Node& root);
#endif


    static ConfigVarBase::ptr LookupBase(const std::string& name);

    static void Visit(std::function<void(ConfigVarBase::ptr)> cb);

private:
    
    static ConfigVarMap& getDatas() {
        static ConfigVarMap s_datas;
        return s_datas;
    }

    static RWMutexType& GetMutex() {
        static RWMutexType s_mutex;
        return s_mutex;
    }
};


}  // namespace sylar
