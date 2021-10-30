#ifndef __TAO_CONFIG_H__
#define __TAO_CONFIG_H__

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>
//配置系统支持的复杂类型
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "log.h"

namespace Tao{

class ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string& name, const std::string& description)
        :m_name(name)
        ,m_description(description){
        std::transform(m_name.begin(), m_name.end(), m_name.begin(),::tolower);
    }
    virtual ~ConfigVarBase() {};

    const std::string& getName() const { return m_name; }
    const std::string& getDescription() const { return m_description; }

    virtual std::string toString() = 0;
    virtual bool fromString(const std::string& val) = 0;
private:
    std::string m_name;
    std::string m_description;
};

//调用boost::lexical_cast完成基本类型转换
template<class From, class To>
class LexicalCast {
public:
    To operator() (const From& v){
        return boost::lexical_cast<To>(v);
    }
};

//完成复杂类型vector的类型转换 模板偏特化
template<class To>
class LexicalCast<std::string, std::vector<To> >{
public:
    std::vector<To> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::vector<To> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); i++){
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, To>() (ss.str()));
        }
        return vec;
    }
};
template<class From>
class LexicalCast<std::vector<From>, std::string>{
public:
    std::string operator() (const std::vector<From>& v){
        YAML::Node node;
        for (auto& i : v){
            node.push_back(YAML::Load(LexicalCast<From, std::string>()(i) ) );
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//完成复杂类型list的类型转换 模板偏特化
template<class To>
class LexicalCast<std::string, std::list<To> >{
public:
    std::list<To> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::list<To> list;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); i++){
            ss.str("");
            ss << node[i];
            list.push_back(LexicalCast<std::string, To>() (ss.str()));
        }
        return list;
    }
};
template<class From>
class LexicalCast<std::list<From>, std::string>{
public:
    std::string operator() (const std::list<From>& v){
        YAML::Node node;
        for (auto& i : v){
            node.push_back(YAML::Load(LexicalCast<From, std::string>()(i) ) );
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//完成复杂类型set的类型转换 模板偏特化
template<class To>
class LexicalCast<std::string, std::set<To> >{
public:
    std::set<To> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::set<To> set;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); i++){
            ss.str("");
            ss << node[i];
            set.insert(LexicalCast<std::string, To>() (ss.str()));
        }
        return set;
    }
};
template<class From>
class LexicalCast<std::set<From>, std::string>{
public:
    std::string operator() (const std::set<From>& v){
        YAML::Node node;
        for (auto& i : v){
            node.push_back(YAML::Load(LexicalCast<From, std::string>()(i) ) );
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//完成复杂类型unorder_set的类型转换 模板偏特化
template<class To>
class LexicalCast<std::string, std::unordered_set<To> >{
public:
    std::unordered_set<To> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::unordered_set<To> uset;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); i++){
            ss.str("");
            ss << node[i];
            uset.insert(LexicalCast<std::string, To>() (ss.str()));
        }
        return uset;
    }
};
template<class From>
class LexicalCast<std::unordered_set<From>, std::string>{
public:
    std::string operator() (const std::unordered_set<From>& v){
        YAML::Node node;
        for (auto& i : v){
            node.push_back(YAML::Load(LexicalCast<From, std::string>()(i) ) );
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//完成复杂类型map的类型转换 模板偏特化
template<class To>
class LexicalCast<std::string, std::map<std::string, To> >{
public:
    std::map<std::string, To> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::map<std::string, To> map;
        std::stringstream ss;
        for (auto it = node.begin();
                it != node.end(); it++){
            ss.str("");
            ss << it->second;
            map.insert(std::make_pair(it->first.Scalar(), 
                        LexicalCast<std::string, To>() (ss.str())));
        }
        return map;
    }
};
template<class From>
class LexicalCast<std::map<std::string, From>, std::string>{
public:
    std::string operator() (const std::map<std::string, From>& v){
        YAML::Node node;
        for (auto& i : v){
            node[i.first] = YAML::Load(LexicalCast<From, std::string>()(i.second) ) ;
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//完成复杂类型unordered_map的类型转换 模板偏特化
template<class To>
class LexicalCast<std::string, std::unordered_map<std::string, To> >{
public:
    std::unordered_map<std::string, To> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::unordered_map<std::string, To> umap;
        std::stringstream ss;
        for (auto it = node.begin();
                it != node.end(); it++){
            ss.str("");
            ss << it->second;
            umap.insert(std::make_pair(it->first.Scalar(), 
                        LexicalCast<std::string, To>() (ss.str())));
        }
        return umap;
    }
};
template<class From>
class LexicalCast<std::unordered_map<std::string, From>, std::string>{
public:
    std::string operator() (const std::unordered_map<std::string, From>& v){
        YAML::Node node;
        for (auto& i : v){
            node[i.first] = YAML::Load(LexicalCast<From, std::string>()(i.second) ) ;
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template<class T, class FromStr = LexicalCast<std::string, T>, class ToStr = LexicalCast<T, std::string> >
class ConfigVar:public ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVar> ptr;
    ConfigVar(const std::string& name
            ,const T& defaultVal
            ,const std::string& description)
        :ConfigVarBase(name, description)
        ,m_val(defaultVal){

    }

    std::string toString() override {
        try {
            // return boost::lexical_cast<std::string>(m_val);
            return ToStr()(m_val);
        } catch (std::exception& e) {
            TAO_LOG_ERROR(TAO_LOG_ROOT()) << "ConfigVar::toString exception"
                << e.what() << "convert: " << typeid(m_val).name() << "to string";
        }
        return "";
    }

    bool fromString(const std::string& val) override {
        try {
            // m_val = boost::lexical_cast<T>(val);
            setValue(FromStr()(val));
            return true;
        } catch (std::exception& e) {
            TAO_LOG_ERROR(TAO_LOG_ROOT()) << "ConfigVar::toString exception"
                << e.what() << "convert: to string" << typeid(m_val).name();
        }
        return false;
    }

    const T getValue() const { return m_val; }
    void setValue(const T& v) { m_val = v; }

private:
    T m_val;
};

class Config {
public:
    typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;
    
    //查找
    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name){
        auto it = s_datas.find(name);
        if (it == s_datas.end()){
            return nullptr;
        }
        return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
    }

    //创建
    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name, 
            const T& default_val, const std::string& description = ""){
        auto tmp = Lookup<T>(name);
        //已存在
        if (tmp) {
            TAO_LOG_INFO(TAO_LOG_ROOT() )<< "Lookup name=" << name << "exists";
            return tmp;
        }
        //命名错误
        if (name.find_first_not_of("qwertyuiopasdfghjklzxcvbnm._0123456789")
                != std::string::npos) {
            TAO_LOG_ERROR(TAO_LOG_ROOT() ) << "Lookup name invalid" << name;
            throw std::invalid_argument(name);
        }

        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_val, description) );
        s_datas[name] = v;
        return v;
    }

    static void loadFromYaml(const YAML::Node& root);
    static ConfigVarBase::ptr LookupBase(const std::string& name);
private:
    static ConfigVarMap s_datas;
};

}

#endif