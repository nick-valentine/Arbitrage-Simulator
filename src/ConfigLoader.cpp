#include "ConfigLoader.hpp"

const std::string ConfigLoader::config_path = "./GameData/config.txt";
std::map<std::string, std::string> ConfigLoader::configuration = std::map<std::string, std::string>();

ConfigLoader::ConfigLoader()
{

}

void ConfigLoader::load()
{
    std::ifstream ifile;
    ifile.open(ConfigLoader::config_path.c_str());
    while(ifile.good()) {
        std::string key, value;
        ifile>>key>>value;
        configuration[key] = value;
    }
    ifile.close();
}

void ConfigLoader::save()
{
    std::ofstream ofile;
    ofile.open(ConfigLoader::config_path.c_str());
    for(c_iter it = ConfigLoader::configuration.begin(); it != ConfigLoader::configuration.end(); ++it) {
        ofile<<it->first<<' '<<it->second<<'\n';
    }
    ofile.close();
}

int ConfigLoader::getIntOption(std::string key) 
{
    std::string value = ConfigLoader::getStringOption(key);
    std::stringstream ss;
    ss.str(value);
    int x;
    ss>>x;
    return x;
}

std::string ConfigLoader::getStringOption(std::string key) 
{
    c_iter it = ConfigLoader::configuration.find(key);
    if(it != ConfigLoader::configuration.end()) {
        return it->second; 
    } else {
        return "";
    }
}

void ConfigLoader::mutateOption(std::string key, int value)
{
    std::stringstream ss;
    std::string s;
    ss<<value;
    s = ss.str();
    ConfigLoader::mutateOption(key, s);
}

void ConfigLoader::mutateOption(std::string key, std::string value)
{
    ConfigLoader::configuration[key] = value;
}

std::vector< std::pair<std::string, std::string> > ConfigLoader::getAllOptions() 
{
    std::vector< std::pair<std::string, std::string> > options;
    for(c_iter it = ConfigLoader::configuration.begin(); it != ConfigLoader::configuration.end(); ++it) {
        options.push_back(*it);
    }
    return options;
}
