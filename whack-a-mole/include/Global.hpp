/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Global
*/

#ifndef GLOBAL_HPP_
    #define GLOBAL_HPP_
    #include <map>
    #include <string>

namespace WhackAMole {
    static const float DEFFAULT_WIDTH = 800;
    static const float DEFFAULT_HEIGHT = 600;

    enum Textures {
        GAME_BACKGROUND,
        MOLE_SPRITE
    };

    const std::map<Textures, std::string> TEXTURES_PATH = {
        {Textures::GAME_BACKGROUND, "./assets/background.png"},
        {Textures::MOLE_SPRITE, "./assets/sprite-mole.png"} 
    };
}

#endif /* !GLOBAL_HPP_ */
