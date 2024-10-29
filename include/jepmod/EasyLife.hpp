/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** EasyLife
*/

#pragma once

#include <string>
#include <filesystem>
#include <map>
#include <functional>
#include <stdexcept>
#include <cstdlib>

namespace jmod {
    /**
     * Allow simple folder/resource path managing for folders and files.
     * 
     * ### Notes
     * This class makes the life of Paul easy.
     * 
     * ### Other notes
     * It's just the absolute path of the binary
     */
    class EasyLife {
        public:
            inline EasyLife() {
                char const *str = std::getenv("JEPGO_BUILD");

                if (str == nullptr)
                    throw std::runtime_error("build variable not found");
                _wd.assign(std::filesystem::absolute(str));
            }
            inline EasyLife(std::string const &firstArg)
            : _wd(std::filesystem::absolute(firstArg).parent_path()) {
                if (*--_wd.string().end() == '.')
                    _wd = std::filesystem::path(_wd.parent_path());
                return;
            }

            inline auto getWorkingDir(void) const -> std::string {
                return _wd.string();
            }

            inline auto createFolders(std::string const &name) -> std::string {
                std::filesystem::path path = _wd / name;

                std::filesystem::create_directories(path);
                return std::filesystem::absolute(path).string();
            }

            inline auto operator/(std::string const &what) const -> std::string {
                return _wd / what;
            }

        private:
            std::filesystem::path _wd;
    };
}
