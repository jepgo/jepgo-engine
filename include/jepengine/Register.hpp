/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Register
*/

#pragma once

#include <map>
#include <string>
#include <utility>
#include <any>
#include <typeindex>
#include <vector>
#include <functional>

#include "SparseArray.hpp"

/**
 * Register is the class that manages the ECS. It allows to create, manage,
 * destroy entities and components.
 */
class Register {
public:
    using RuleMap = std::map<std::type_index, std::any>;
    using RuleCB = std::function<void(RuleMap &)>;
    using RuleGCB = std::function<void(RuleMap &, std::size_t)>;

    /**
     * The register constructor.
     */
    Register();

    /**
     * The register destructor.
     */
    ~Register();

    /**
     * Creates a new entity (number is stored in currentEntity).
     */
    void createEntity();

    /**
     * Remove an entity
     */
    void removeEntity(std::size_t entity);
    
    /**
     * Get the register map.
     */
    RuleMap &getRegister();

    /**
     * ## DO NOT USE ###
     *
     * Insert a new component at runtime.
     */
    template <typename T>
    inline auto runTimeInsert() -> void {
        _regist.insert({std::type_index(typeid(T)), SparseArray<T>()});
    }

    /**
     * Add a new rule that applies when entity creates.
     */
    inline auto addRule(RuleCB cb) -> void {
        _rules.push_back(cb);
    }

    /**
     * Add a new rule that applies when entity destroys.
     */
    inline auto addGarbageRule(RuleGCB cb) -> void {
        _garbageRules.push_back(cb);
    }

    /**
     * Apply a component to an entity.
     */
    template <typename Component>
    inline auto emplaceComp(std::size_t id, Component const &comp) -> void {
        std::any_cast<SparseArray<Component>&>(_regist[std::type_index(typeid(Component))]).insert_at(id, comp);
    }

    template <typename Component>
    inline auto emplaceComp(std::size_t id, Component &&comp) -> void {
        std::any_cast<SparseArray<Component>&>(_regist[std::type_index(typeid(Component))]).insert_at(id, std::move(comp));
    }

    /**
     * Remove a component to an entity.
     */
    template <typename Component>
    void removeComponent(std::size_t entity) {
        std::any_cast<SparseArray<Component>&>(_regist[std::type_index(typeid(Component))]).erase(entity);
    }

    template <typename... Components>
    void removeComponents(std::size_t entity) {
        (std::any_cast<SparseArray<Components>&>(_regist[std::type_index(typeid(Components))]).erase(entity), ...);
    }

    /**
     * Get an array of all entities that have the component.
     */
    template <typename T>
    SparseArray<T> &getComp() {
        return std::any_cast<SparseArray<T>&>(_regist[std::type_index(typeid(T))]);
    }

    /**
     * Get the number of entities.
     */
    std::size_t entityNbr(void) const;

    int currentEntity = -1;
    int tmp = -1;

private:
    RuleMap _regist;
    std::vector<RuleCB> _rules;
    std::vector<RuleGCB> _garbageRules;
};
