/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParsingFile
*/

#include "ParsingFile.hpp"
#include <iostream>

void ParsingPathLevel::getAllPathsFromFile(const ParsingFile &file)
{
    const libconfig::Setting &root = file.cfg.getRoot();
    const libconfig::Setting &levels = root["textures_levels"]["levels"];
    
    for (int i = 0; i < levels.getLength(); i++) {
        const libconfig::Setting &levelPath = levels[i]["paths"];
        std::vector<std::string> listOfPath;
        for (int j = 0; j < levelPath.getLength(); j++) {
            const libconfig::Setting &paths = levelPath[j];
            listOfPath.push_back(std::string(paths));
        }
        this->pathsLevels.push_back(listOfPath);
    }
    return;
}