/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Client
*/

#pragma once

#include <string>
#include <optional>

#include "engine/engine.hpp"
#include "jepgame/service/UDPBase.hpp"

namespace jgame {
    class Client: public jgo::UDPBase {
        public:
            inline Client(void) {
                return;
            }
            inline Client(int ac, char const *av[]): UDPBase(ac, av) {
                return;
            }
            inline auto sendToServer(std::string const &str) -> void {
                _udp->send(str);
            }
            inline auto sendToServer(jgo::Builder const &builder) -> void {
                _udp->send(builder.toString());
            }
            inline void updateTime(void) override {
                _time.current = GetTime() - _time.start;
            }
            
            auto connect(std::string ip, asio::ip::port port) -> void;
            auto getDirection(void) const -> Vector2;

            struct {
                unsigned int width = 800;
                unsigned int heigth = 600;
                std::string name = "Can you consider giving me a name ?";
            } window;

            /// FIXME: hardcoded
            struct AllSystems {
                AllSystems(void)
                : addDmg(.1), test(1), game(.1), move(.01), moveTo(.3) {
                    return;
                }
                AllSystems(double a, double b, double c, double d, double e)
                : addDmg(a), test(b), game(c), move(d), moveTo(e) {
                    return;
                }
                Game player;
                AddDmgSystem addDmg;
                TestGame test;
                GameSystem game;
                MoveSystem move;
                HitSystem hit;
                DrawSystem draw;
                MoveToPlayerSystem moveTo;
                AnimationSpriteSystem anim;
            } systems;

            /// FIXME: hardcoded
            std::vector<Texture2D> textures;
            void getAllTextures(std::vector<std::string> list) {
                textures.reserve(list.size());
                for (std::size_t i = 0; i < list.size(); i++) {
                    std::cout << list[i].c_str() << std::endl;
                    Texture2D tmp = LoadTexture(list[i].c_str());
                    std::cout << "bar" << std::endl;
                    //tmp.loadFromFile(list[i].c_str());
                    textures.push_back(std::move(tmp));
                }
            }

        private:
            /// FIXME: hardcoded
    };
}

