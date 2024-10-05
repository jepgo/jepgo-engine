/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AllSystem
*/

#pragma once
#include "Raylib.hpp"
#include <iostream>
#include "DrawKmSystem.hpp"
#include "DrawLvlSystem.hpp"
#include "DetachModulesSystem.hpp"
#include "MessageTimeSystem.hpp"
#include "MessageSystem.hpp"
#include "MoveToSystem.hpp"
#include "DrawRebornSystem.hpp"
#include "DrawPointsSystem.hpp"
#include "MoveToPlayerSystem.hpp"
#include "Animation2TimeSystem.hpp"
#include "BombGenerationSystem.hpp"
#include "BombGenerationTimeSystem.hpp"
#include "MoveToPlayerTimeSystem.hpp"
#include "InvinsibleSystem.hpp"
#include "LoopMoveSystem.hpp"
#include "DestroyerSystem.hpp"
#include "ShortAnimationSystem.hpp"
#include "SoundLoopSystem.hpp"
#include "AddDmgSystem.hpp"
#include "GameSystem.hpp"
#include "TestGame.hpp"
#include "Game.hpp"
#include "DeathSystem.hpp"
#include "AttachModuleSystem.hpp"
#include "DmgSystem.hpp"
#include "ModuleSystem.hpp"
#include "RebornSystem.hpp"
#include "HitSystem.hpp"
#include "DrawSystem.hpp"
#include "Register.hpp"
#include "Components.hpp"
#include "ExplosionSystem.hpp"
#include "SparseArray.hpp"
#include "MoveSystem.hpp"
#include "AnimationSpriteSystem.hpp"

class AllSystem {
    public:
        AllSystem(float time, float reset) : _time(time), _reset(reset) {};
        ~AllSystem() {};
    private:
        float _time;
        float _reset;
};
