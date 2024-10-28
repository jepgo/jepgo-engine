/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Hit
*/

#pragma once

class Hit {
    public:
        /**
         * @brief Construct a new Hit object
         * 
         * @param entity The entity B who's hit (A is the current get this components)
         */
        Hit(int entity) : _entity(entity) {};
        ~Hit() {};
        /**
         * @brief Get the Entity object
         * 
         * @return int The entity contained by the Hit object
         */
        int GetEntity() {return _entity;};
    private:
        int _entity;

};