#pragma once

#include <string>
#include <unordered_map>

class Singleton
{
private:
    static Singleton *instance;
    std::unordered_map<std::string, std::string> config;

    Singleton() {}

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

public:
    static Singleton *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }

    void setValue(const std::string &key, const std::string &value)
    {
        config[key] = value;
    }

    std::string getValue(const std::string &key) const
    {
        auto it = config.find(key);
        if (it != config.end())
        {
            return it->second;
        }
        return "";
    }
};