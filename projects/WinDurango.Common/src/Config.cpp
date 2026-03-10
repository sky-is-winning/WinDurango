#include "Config.h"

bool wd::common::Config::parse()
{
    try
    {
        pFile->open();
        std::string jsonData = pFile->read();
        data = nlohmann::json::parse(jsonData);
        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
    catch (...)
    {
        return false;
    }
}

template <typename T> T &wd::common::Config::operator[](std::string node)
{
    return data[node];
}

template <typename T> bool wd::common::Config::set(std::string node, T type)
{
    data[node] = type;
    return true;
}

template <typename T> T wd::common::Config::get(std::string node)
{
    return data[node].get<T>();
}

bool wd::common::Config::save()
{
    if (RO || pFile == nullptr)
        return false;
    try
    {
        *pFile << data.dump(4);
        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
    catch (...)
    {
        return false;
    }
}

bool wd::common::Config::contains(std::string node)
{
    return data.contains(node);
}