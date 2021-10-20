#ifndef __TAO_CONFIG_H__
#define __TAO_CONFIG_H__

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>

#include "log.h"

namespace Tao{

class ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string& name, const std::string& description)
        :m_name(name)
        ,m_description(description){
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

template<class T>
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
            return boost::lexical_cast<std::string>(m_val);
        } catch (std::exception& e) {
            TAO_LOG_ERROR(TAO_LOG_ROOT()) << "ConfigVar::toString exception"
                << e.what() << "convert: " << typeid(m_val).name() << "to string";
        }
        return "";
    }

    bool fromString(const std::string& val) override {
        try {
            m_val = boost::lexical_cast<T>(val);
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
        if (name.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM._0123456789")
                != std::string::npos) {
            TAO_LOG_ERROR(TAO_LOG_ROOT() ) << "Lookup name invalid" << name;
            throw std::invalid_argument(name);
        }

        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_val, description) );
        s_datas[name] = v;
        return v;
    }

private:
    static ConfigVarMap s_datas;
};

}

#endif