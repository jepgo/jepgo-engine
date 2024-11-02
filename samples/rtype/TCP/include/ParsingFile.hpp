/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParsingFile
*/

#ifndef PARSINGFILE_HPP_
#define PARSINGFILE_HPP_
#include <libconfig.h++>
#include <vector>

class ParsingFile
{
    public:
        /**
         * @brief Construct a new Parsing File object
         * 
         * @param path the path of the file
         */
        ParsingFile(const std::string &path) {
            cfg.readFile(path.c_str());
        };
        /**
         * @brief Destroy the Parsing File object
         * 
         */
        ~ParsingFile() = default;
        libconfig::Config cfg;
};

class ParsingPathLevel {
    public:
        /**
         * @brief Construct a new Parsing Path Level object
         * 
         */
        ParsingPathLevel() = default;
        /**
         * @brief Destroy the Parsing Path Level object
         * 
         */
        ~ParsingPathLevel() = default;
        /**
         * @brief all textures paths
         * 
         * @param file ParsingFile object
         */
        void getAllPathsFromFile(const ParsingFile &file);
        /**
         * @brief texture paths based on a given index
         * 
         * @param ind index
         * @return std::vector<std::string> list of textures
         */
        std::vector<std::string> getListOfPathsLevel(size_t ind){return pathsLevels[ind - 1];};
    private:
        /**
         * @brief All textures paths sort by level
         * 
         */
        std::vector<std::vector<std::string>> pathsLevels;
};

#endif /* !PARSINGFILE_HPP_ */