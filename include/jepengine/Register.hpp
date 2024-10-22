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

class Register {
public:
    using RuleMap = std::map<std::type_index, std::any>;
    using RuleCB = std::function<void(RuleMap &)>;
    Register();
    ~Register();

    void creatEntity();
    std::map<std::type_index, std::any> &getRegister();
    template <typename T>
    inline auto runTimeInsert() -> void {
        regist.insert({std::type_index(typeid(T)), SparseArray<T>()});
    }
    inline auto addRule(RuleCB cb) -> void {
        _rules.push_back(cb);
    }
    template <typename Component, class ...Params>
    inline auto add_comp(std::size_t id, Params &&... par) -> void {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).add(par...);
    }
    template <typename Component>
    inline auto emplace_comp(std::size_t id, Component &&comp) -> void {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).insert_at(id, std::move(comp));
    }
    template <typename Component>
    inline auto emplace_comp(std::size_t id, Component &comp) -> void {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).insert_at(id, std::move(comp));
    }
    template <typename Component>
    void removeComponent(std::size_t entity) {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).erase(entity);
    }
    template <typename Component>
    SparseArray<Component> &getComp()
    {
        return std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]);
    }
    std::size_t entityNbr(void) const;
    int currentEntity = -1;

private:
    std::map<std::type_index, std::any> regist;
    std::vector<RuleCB> _rules;
};
