#include "Keymap.hpp"

const std::string Keymap::mapFile = "GameData/keymap.txt";

void Keymap::init()
{
    std::vector< std::pair<std::string, std::string> > m;
    m = this->loadFile();
    this->createMap(m);
    this->inputMap[27] = Input::ESCAPE;
}

Input Keymap::convert(int rawInput)
{
    if (this->inputMap.find(rawInput) != this->inputMap.end()) {
        return this->inputMap[rawInput];
    }
    return Input::IGNORED;
}

std::vector< std::pair<std::string, std::string> > Keymap::loadFile()
{
    std::vector< std::pair<std::string, std::string> > configPairs;
    std::ifstream ifile;
    ifile.open(Keymap::mapFile.c_str());
    while (ifile.good()) {
        std::string tmp;
        std::getline(ifile, tmp);
        std::stringstream ss;
        ss.str(tmp);
        std::pair<std::string, std::string> mapPair;
        ss>>mapPair.first>>mapPair.second;
        configPairs.push_back(mapPair);
    }
    ifile.close();
    return configPairs;
}

// At this time, create map will only handle the ascii part of the keyboard
// and only printable non-whitespace characters
void Keymap::createMap(std::vector< std::pair<std::string, std::string> > mappings)
{
    for (unsigned int i = 0; i < mappings.size(); ++i) {
        if (mappings[i].first.size() == 1) {
            inputMap[mappings[i].first[0]] = InputMapping::toInput(mappings[i].second);
        }
    }
}

