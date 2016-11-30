#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <utility>

class ConfigLoader
{
public:
    static void load();
    static void save();

    static int getIntOption(std::string key);
    static std::string getStringOption(std::string key);

    static void mutateOption(std::string key, int value);
    static void mutateOption(std::string key, std::string value);

    static std::vector< std::pair<std::string, std::string> > getAllOptions();
private:
    ConfigLoader();

    static const std::string config_path;
    using c_iter = std::map<std::string, std::string>::const_iterator;

    //map key to value
    static std::map<std::string, std::string> configuration;
};

#endif //CONFIGLOADER_HPP
