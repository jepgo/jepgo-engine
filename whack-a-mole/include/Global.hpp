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

/**
 * @brief The namespace of the WhackAMole game
 * 
 */
namespace WhackAMole {
    /**
     * @brief The default width and height of the game
     * 
     */
    static const float DEFFAULT_WIDTH = 800;

    /**
     * @brief The default height of the game
     * 
     */
    static const float DEFFAULT_HEIGHT = 600;


    /**
     * @brief The textures indexes of the game
     * 
     */
    enum Textures {
        GAME_BACKGROUND,
        MOLE_SPRITE
    };

    /**
     * @brief The path of the textures
     * 
     */
    const std::map<Textures, std::string> TEXTURES_PATH = {
        {Textures::GAME_BACKGROUND, "./assets/background.png"},
        {Textures::MOLE_SPRITE, "./assets/sprite-mole.png"} 
    };
}

#endif /* !GLOBAL_HPP_ */
