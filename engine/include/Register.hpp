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
#include "Text.hpp"
#include "MoveTo.hpp"
#include "SparseArray.hpp"
#include "Enemy.hpp"
#include "Components.hpp"
#include "Module.hpp"

class Register
{

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

    // template <typename T>
    // inline auto applyCreateRule() -> void {
    //     std::any_cast<SparseArray<T>&>(regist[std::type_index(typeid(T))]).add();
    // }

    template <typename Component, class ...Params>
    void add_comp(std::size_t id, Params &&... par)
    {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).add(par...);
    }
    template <typename Component>
    void emplace_comp(std::size_t id, Component &&comp)
    {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).insert_at(id, std::move(comp));
    }
    template <typename Component>
    void emplace_comp(std::size_t id, Component &comp)
    {
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
    std::size_t entityNbr();

    // void erase(std::size_t enity){
    //     for (auto it = regist.begin(); it != regist.end(); it++) {
    //         auto tmp = it->first;
    //         std::any_cast<SparseArray<tmp>&>(regist[std::type_index(typeid(Component))]);
    //     }
    // };
    // inline auto getComponents(void) -> std::map<std::type_index, std::any> & {
    //     return regist;
    // }

    int currentEntity = -1;
private:
    std::map<std::type_index, std::any> regist;
    std::vector<RuleCB> _rules;
};
