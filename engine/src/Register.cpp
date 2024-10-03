/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Register
*/

#include "Register.hpp"

enum mat {
    POS,
    DRAW,
};

Register::Register()
{
    regist.insert({std::type_index(typeid(Positions)), SparseArray<Positions>()});
    regist.insert({std::type_index(typeid(Drawable)), SparseArray<Drawable>()});
    regist.insert({std::type_index(typeid(Sprite_Animation)), SparseArray<Sprite_Animation>()});
    regist.insert({std::type_index(typeid(Controllable)), SparseArray<Controllable>()});
    regist.insert({std::type_index(typeid(Velocity)), SparseArray<Velocity>()});
    regist.insert({std::type_index(typeid(Sprite_Status)), SparseArray<Sprite_Status>()});
    regist.insert({std::type_index(typeid(Hitable)), SparseArray<Hitable>()});
    regist.insert({std::type_index(typeid(Explosion)), SparseArray<Explosion>()});
    regist.insert({std::type_index(typeid(Colision)), SparseArray<Colision>()});
    regist.insert({std::type_index(typeid(Move)), SparseArray<Move>()});
    regist.insert({std::type_index(typeid(Module)), SparseArray<Module>()});
    regist.insert({std::type_index(typeid(Shoot)), SparseArray<Shoot>()});
    regist.insert({std::type_index(typeid(Hit)), SparseArray<Hit>()});
    regist.insert({std::type_index(typeid(ScreenLimit)), SparseArray<ScreenLimit>()});
    regist.insert({std::type_index(typeid(Life)), SparseArray<Life>()});
    regist.insert({std::type_index(typeid(Dmg)), SparseArray<Dmg>()});
    regist.insert({std::type_index(typeid(ModuleShoot)), SparseArray<ModuleShoot>()});
    regist.insert({std::type_index(typeid(ModuleArmor)), SparseArray<ModuleArmor>()});
    regist.insert({std::type_index(typeid(Enemy)), SparseArray<Enemy>()});
    regist.insert({std::type_index(typeid(DoDmg)), SparseArray<DoDmg>()});
    regist.insert({std::type_index(typeid(Type)), SparseArray<Type>()});
    regist.insert({std::type_index(typeid(Death)), SparseArray<Death>()});
    //regist.insert({std::type_index(typeid(Text)), SparseArray<Text>()});
    regist.insert({std::type_index(typeid(LoopMove)), SparseArray<LoopMove>()});
    regist.insert({std::type_index(typeid(Invincible)), SparseArray<Invincible>()});
    regist.insert({std::type_index(typeid(InvincibleTime)), SparseArray<InvincibleTime>()});
    regist.insert({std::type_index(typeid(LvLUp)), SparseArray<LvLUp>()});
    regist.insert({std::type_index(typeid(SoundLoop)), SparseArray<SoundLoop>()});
    regist.insert({std::type_index(typeid(SoundEffect)), SparseArray<SoundEffect>()});
    regist.insert({std::type_index(typeid(Lvl)), SparseArray<Lvl>()});
    regist.insert({std::type_index(typeid(Points)), SparseArray<Points>()});
    regist.insert({std::type_index(typeid(Exp)), SparseArray<Exp>()});
    regist.insert({std::type_index(typeid(DistanceKm)), SparseArray<DistanceKm>()});
    regist.insert({std::type_index(typeid(Short_Animation)), SparseArray<Short_Animation>()});
    regist.insert({std::type_index(typeid(Animation2Time)), SparseArray<Animation2Time>()});
    regist.insert({std::type_index(typeid(MoveToPlayer)), SparseArray<MoveToPlayer>()});
    regist.insert({std::type_index(typeid(MoveToPlayerTime)), SparseArray<MoveToPlayerTime>()});
    regist.insert({std::type_index(typeid(BombGeneration)), SparseArray<BombGeneration>()});
    regist.insert({std::type_index(typeid(BombGenerationTime)), SparseArray<BombGenerationTime>()});
    regist.insert({std::type_index(typeid(DrawKm)), SparseArray<DrawKm>()});
    regist.insert({std::type_index(typeid(DrawPoints)), SparseArray<DrawPoints>()});
    regist.insert({std::type_index(typeid(DrawLvl)), SparseArray<DrawLvl>()});
<<<<<<< HEAD
<<<<<<< HEAD
    regist.insert({std::type_index(typeid(Message)), SparseArray<Message>()});
    regist.insert({std::type_index(typeid(Reborn)), SparseArray<Reborn>()});
    regist.insert({std::type_index(typeid(DrawReborn)), SparseArray<DrawReborn>()});
    regist.insert({std::type_index(typeid(GameLvl)), SparseArray<GameLvl>()});
    regist.insert({std::type_index(typeid(MoveTo)), SparseArray<MoveTo>()});
    regist.insert({std::type_index(typeid(MessageTime)), SparseArray<MessageTime>()});
    regist.insert({std::type_index(typeid(AutoShoot)), SparseArray<AutoShoot>()});
=======
>>>>>>> c351202 (feat(Engine): add the Text Components)
=======
    regist.insert({std::type_index(typeid(Message)), SparseArray<Message>()});
>>>>>>> 5f4ac64 (feat(Engine): add the Dead text)
}

Register::~Register()
{

}

void Register::creatEntity()
{
    currentEntity++;
    std::any_cast<SparseArray<Positions>&>(regist[std::type_index(typeid(Positions))]).add();
    std::any_cast<SparseArray<Drawable>&>(regist[std::type_index(typeid(Drawable))]).add();
    std::any_cast<SparseArray<Sprite_Animation>&>(regist[std::type_index(typeid(Sprite_Animation))]).add();
    std::any_cast<SparseArray<Velocity>&>(regist[std::type_index(typeid(Velocity))]).add();
    std::any_cast<SparseArray<Controllable>&>(regist[std::type_index(typeid(Controllable))]).add();
    std::any_cast<SparseArray<Sprite_Status>&>(regist[std::type_index(typeid(Sprite_Status))]).add();
    std::any_cast<SparseArray<Hitable>&>(regist[std::type_index(typeid(Hitable))]).add();
    std::any_cast<SparseArray<Explosion>&>(regist[std::type_index(typeid(Explosion))]).add();
    std::any_cast<SparseArray<Colision>&>(regist[std::type_index(typeid(Colision))]).add();
    std::any_cast<SparseArray<Move>&>(regist[std::type_index(typeid(Move))]).add();
    std::any_cast<SparseArray<Module>&>(regist[std::type_index(typeid(Module))]).add();
    std::any_cast<SparseArray<Shoot>&>(regist[std::type_index(typeid(Shoot))]).add();
    std::any_cast<SparseArray<Hit>&>(regist[std::type_index(typeid(Hit))]).add();
    std::any_cast<SparseArray<ScreenLimit>&>(regist[std::type_index(typeid(ScreenLimit))]).add();
    std::any_cast<SparseArray<Life>&>(regist[std::type_index(typeid(Life))]).add();
    std::any_cast<SparseArray<Dmg>&>(regist[std::type_index(typeid(Dmg))]).add();
    std::any_cast<SparseArray<ModuleShoot>&>(regist[std::type_index(typeid(ModuleShoot))]).add();
    std::any_cast<SparseArray<ModuleArmor>&>(regist[std::type_index(typeid(ModuleArmor))]).add();
    std::any_cast<SparseArray<Enemy>&>(regist[std::type_index(typeid(Enemy))]).add();
    std::any_cast<SparseArray<DoDmg>&>(regist[std::type_index(typeid(DoDmg))]).add();
    std::any_cast<SparseArray<Type>&>(regist[std::type_index(typeid(Type))]).add();
    std::any_cast<SparseArray<Death>&>(regist[std::type_index(typeid(Death))]).add();
    //std::any_cast<SparseArray<Text>&>(regist[std::type_index(typeid(Text))]).add();
    std::any_cast<SparseArray<LoopMove>&>(regist[std::type_index(typeid(LoopMove))]).add();
    std::any_cast<SparseArray<Invincible>&>(regist[std::type_index(typeid(Invincible))]).add();
    std::any_cast<SparseArray<InvincibleTime>&>(regist[std::type_index(typeid(InvincibleTime))]).add();
    std::any_cast<SparseArray<LvLUp>&>(regist[std::type_index(typeid(LvLUp))]).add();
    std::any_cast<SparseArray<SoundEffect>&>(regist[std::type_index(typeid(SoundEffect))]).add();
    std::any_cast<SparseArray<SoundLoop>&>(regist[std::type_index(typeid(SoundLoop))]).add();
    std::any_cast<SparseArray<Lvl>&>(regist[std::type_index(typeid(Lvl))]).add();
    std::any_cast<SparseArray<Exp>&>(regist[std::type_index(typeid(Exp))]).add();
    std::any_cast<SparseArray<Points>&>(regist[std::type_index(typeid(Points))]).add();
    std::any_cast<SparseArray<DistanceKm>&>(regist[std::type_index(typeid(DistanceKm))]).add();
    std::any_cast<SparseArray<Short_Animation>&>(regist[std::type_index(typeid(Short_Animation))]).add();
    std::any_cast<SparseArray<Animation2Time>&>(regist[std::type_index(typeid(Animation2Time))]).add();
    std::any_cast<SparseArray<MoveToPlayer>&>(regist[std::type_index(typeid(MoveToPlayer))]).add();
    std::any_cast<SparseArray<MoveToPlayerTime>&>(regist[std::type_index(typeid(MoveToPlayerTime))]).add();
    std::any_cast<SparseArray<BombGeneration>&>(regist[std::type_index(typeid(BombGeneration))]).add();
    std::any_cast<SparseArray<BombGenerationTime>&>(regist[std::type_index(typeid(BombGenerationTime))]).add();
    std::any_cast<SparseArray<DrawKm>&>(regist[std::type_index(typeid(DrawKm))]).add();
    std::any_cast<SparseArray<DrawPoints>&>(regist[std::type_index(typeid(DrawPoints))]).add();
    std::any_cast<SparseArray<DrawLvl>&>(regist[std::type_index(typeid(DrawLvl))]).add();
    std::any_cast<SparseArray<Message>&>(regist[std::type_index(typeid(Message))]).add();
<<<<<<< HEAD
    std::any_cast<SparseArray<Reborn>&>(regist[std::type_index(typeid(Reborn))]).add();
    std::any_cast<SparseArray<DrawReborn>&>(regist[std::type_index(typeid(DrawReborn))]).add();
    std::any_cast<SparseArray<GameLvl>&>(regist[std::type_index(typeid(GameLvl))]).add();
    std::any_cast<SparseArray<MoveTo>&>(regist[std::type_index(typeid(MoveTo))]).add();
    std::any_cast<SparseArray<MessageTime>&>(regist[std::type_index(typeid(MessageTime))]).add();
    std::any_cast<SparseArray<AutoShoot>&>(regist[std::type_index(typeid(AutoShoot))]).add();
=======
>>>>>>> 5f4ac64 (feat(Engine): add the Dead text)
    for (auto const &cb : _rules) {
        cb(regist);
    }
}

std::map<std::type_index, std::any> &Register::getRegister()
{
    return regist;
}

std::size_t Register::entityNbr()
{
    return std::any_cast<SparseArray<Positions>>(regist[std::type_index(typeid(Positions))]).size();
}
