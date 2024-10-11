/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#ifndef CPOSITION_HPP_
    #define CPOSITION_HPP_

/**
 * @brief The namespace of the components
 * 
 */
namespace Components {

    /**
     * @brief Class of the position of an entity
     * 
     */
    class Positions {
        public:
            /**
             * @brief Construct a new Positions object
             *
             * @param x Position x of the object
             * @param y Position y of the Object
             */
            Positions(float x, float y);

            /**
             * @brief Destroy the Positions object
             * 
             */
            ~Positions() = default;


            /**
             * @brief Addition of 2 positions
             * 
             * @param pos The position to add
             * @return Positions A new position object
             */
            Positions operator+(Positions const &pos) const;

            /**
             * @brief Compare 2 positions
             * 
             * @param pos The position to compare with
             * @return true If the positions are the same
             * @return false If the positions are different
             */
            bool operator==(Positions const &pos) const;



            /**
             * @brief The x position of the object
             * 
             */
            float x;

            /**
             * @brief The y position of the object
             * 
             */
            float y;
    };
}

#endif /* !CPOSITION_HPP_ */
