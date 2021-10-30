#include "config.h"
#include "log.h"
#include <yaml-cpp/yaml.h>

void printYaml(const YAML::Node &node, int level)
{
    if (node.IsScalar())
    {
        TAO_LOG_INFO(TAO_LOG_ROOT()) << std::string(level * 4, ' ')
                                     << node.Scalar() << "-" << node.Type() << "-" << level;
    }
    else if (node.IsNull())
    {
        TAO_LOG_INFO(TAO_LOG_ROOT()) << std::string(level * 4, ' ')
                                     << "NULL-" << node.Type() << "-" << level;
    }
    else if (node.IsMap())
    {
        for (auto it = node.begin();
             it != node.end(); it++)
        {
            TAO_LOG_INFO(TAO_LOG_ROOT()) << std::string(level * 4, ' ')
                                         << it->first << "-" << it->second.Type() << "-" << level;
            printYaml(it->second, level + 1);
        }
    }
    else if (node.IsSequence())
    {
        for (size_t i = 0; i < node.size(); i++)
        {
            TAO_LOG_INFO(TAO_LOG_ROOT()) << std::string(level * 4, ' ')
                                         << i << "-" << node[i].Type() << "-" << level;
            printYaml(node[i], level + 1);
        }
    }
}

void testYaml()
{
    YAML::Node root = YAML::LoadFile("/home/zt/linux_stud/TaoServer/bin/config/log.yml");
    printYaml(root, 0);
}

void testConfig()
{
    Tao::ConfigVar<int>::ptr gIntValueConfig =
        Tao::Config::Lookup("system.port", (int)8080, "systemport");
    Tao::ConfigVar<std::vector<int>>::ptr gVecIntValueConfig =
        Tao::Config::Lookup("system.vec", std::vector<int>{1, 2, 3, 4}, "systemvec");
    Tao::ConfigVar<std::list<int>>::ptr gListIntValueConfig =
        Tao::Config::Lookup("system.list", std::list<int>{1, 2, 3, 4}, "systemlist");
    Tao::ConfigVar<std::set<int>>::ptr gSetIntValueConfig =
        Tao::Config::Lookup("system.set", std::set<int>{1, 2, 3, 4}, "systemset");
    Tao::ConfigVar<std::unordered_set<int>>::ptr gUsetIntValueConfig =
        Tao::Config::Lookup("system.uset", std::unordered_set<int>{1, 2, 3, 4}, "systemuset");
    Tao::ConfigVar<std::map<std::string, int>>::ptr gMapIntValueConfig =
        Tao::Config::Lookup("system.map", std::map<std::string, int>{{"k1", 1}, {"k2", 2}}, "systemmap");
    Tao::ConfigVar<std::unordered_map<std::string, int>>::ptr gUmapIntValueConfig =
        Tao::Config::Lookup("system.umap", std::unordered_map<std::string, int>{{"k1", 1}, {"k2", 2}}, "systemumap");

    TAO_LOG_INFO(TAO_LOG_ROOT()) << "before: " << gIntValueConfig->getValue();
    TAO_LOG_INFO(TAO_LOG_ROOT()) << "before: " << gIntValueConfig->toString();

#define XX(g_var, name, prefix)                                                      \
    {                                                                                \
        auto v = g_var->getValue();                                                  \
        for (int i : v)                                                              \
        {                                                                            \
            TAO_LOG_INFO(TAO_LOG_ROOT()) << #prefix " " #name ": " << i;             \
        }                                                                            \
        TAO_LOG_INFO(TAO_LOG_ROOT()) << #prefix " " #name ": " << g_var->toString(); \
    }

#define XX_M(g_var, name, prefix)                                                                         \
    {                                                                                                     \
        auto v = g_var->getValue();                                                                       \
        for (auto i : v)                                                                                  \
        {                                                                                                 \
            TAO_LOG_INFO(TAO_LOG_ROOT()) << #prefix " " #name ": {" << i.first << "-" << i.second << "}"; \
        }                                                                                                 \
        TAO_LOG_INFO(TAO_LOG_ROOT()) << #prefix " " #name ": " << g_var->toString();                      \
    }
    XX(gVecIntValueConfig, int_vec, before);
    XX(gListIntValueConfig, int_list, before);
    XX(gSetIntValueConfig, int_set, before);
    XX(gUsetIntValueConfig, int_uset, before);
    XX_M(gMapIntValueConfig, str_int_map, before);
    XX_M(gUmapIntValueConfig, str_int_umap, before);

    YAML::Node root = YAML::LoadFile("/home/zt/linux_stud/TaoServer/bin/config/log.yml");
    Tao::Config::loadFromYaml(root);

    TAO_LOG_INFO(TAO_LOG_ROOT()) << "after: " << gIntValueConfig->getValue();
    TAO_LOG_INFO(TAO_LOG_ROOT()) << "after: " << gIntValueConfig->toString();

    XX(gVecIntValueConfig, int_vec, after);
    XX(gListIntValueConfig, int_list, after);
    XX(gSetIntValueConfig, int_set, after);
    XX(gUsetIntValueConfig, int_uset, after);
    XX_M(gMapIntValueConfig, str_int_map, after);
    XX_M(gUmapIntValueConfig, str_int_umap, after);
}

int main(int argc, char **argv)
{
    testConfig();
    // testYaml();
    return 0;
}