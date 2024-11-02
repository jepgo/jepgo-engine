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
    class Position2D {
        public:
            /**
             * @brief Construct a new Position2D object
             *
             * @param x Position x of the object
             * @param y Position y of the Object
             */
            Position2D(float x, float y);

            /**
             * @brief Destroy the Position2D object
             * 
             */
            ~Position2D() = default;


            /**
             * @brief Addition of 2 positions
             * 
             * @param pos The position to add
             * @return Position2D A new position object
             */
            Position2D operator+(Position2D const &pos) const;

            /**
             * @brief Compare 2 positions
             * 
             * @param pos The position to compare with
             * @return true If the positions are the same
             * @return false If the positions are different
             */
            bool operator==(Position2D const &pos) const;



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
