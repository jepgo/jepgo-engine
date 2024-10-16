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
#include "jepmod/DLLoader.hpp"

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
                bool use3D = false;
            } settings;

            struct {
                Camera camera = { 0 };
                inline auto init(unsigned int h, unsigned int w) -> void {
                    camera.position = { h / 2.0f, w / 2.0f, 500.0f };
                    camera.target = { h / 2.0f, w / 2.0f, 0.0f };
                    camera.up = { 0.0f, 1.0f, 0.0f };
                    camera.fovy = w;
                    camera.projection = CAMERA_ORTHOGRAPHIC;
                    SetTargetFPS(60);
                }
            } tools3D;

            struct {
                unsigned int width = 800;
                unsigned int heigth = 600;
                std::string name = "Can you consider giving me a name ?";
            } window;

            /// FIXME: hardcoded
            struct AllSystems {
                AllSystems(void)
                : addDmg(.1), test(1), game(.1), move(.01), moveTo(.3), draw3D(0, 0.1) {
                    return;
                }
                AllSystems(double a, double b, double c, double d, double e, double f, double g)
                : addDmg(a), test(b), game(c), move(d), moveTo(e), draw3D(f, g) {
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
                Draw3DSystem draw3D;
            } systems;

            /* The 2D Textures. */
            std::vector<Texture2D> textures;
            void getAllTextures(std::vector<std::string> list) {
                textures.reserve(list.size());
                for (std::size_t i = 0; i < list.size(); i++) {
                    Texture2D tmp = LoadTexture(list[i].c_str());
                    textures.push_back(std::move(tmp));
                }
            }

            /* The 3D Textures. */
            std::vector<Model> models;
            void getAllModels(std::map<std::string, std::string> const &mods) {
                for (auto const &mod : mods) {
                    Model tmp = LoadModel(mod.first.c_str());
                    Texture2D tex = LoadTexture(mod.second.c_str());
                    tmp.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
                    models.push_back(std::move(tmp));
                }
            }


            auto useExternal(std::string const &str) -> void;

            auto getExternalComponent(std::string const &str) -> bool;

        private:
            std::optional<jmod::DLLoader> _loader;
    };
}

