#ifndef KEYMAP_HPP
#define KEYMAP_HPP

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>

#include "Input.hpp"

class Keymap {
public:
    void init();

    Input convert(int rawInput);
private:
    const static std::string mapFile;

    std::vector< std::pair<std::string, std::string> > loadFile();
    void createMap(std::vector< std::pair<std::string, std::string> > mappings);
    std::map<int, Input> inputMap;
};

#endif //KEYMAP_HPP
