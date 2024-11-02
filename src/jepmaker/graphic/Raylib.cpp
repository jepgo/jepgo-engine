/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Raylib
*/

#include <functional>
#include <iostream>
#include "raylib.h"
#include "jepmod/exported.hpp"
#include "jepmaker/graphic/IGraphic.hpp"

class Raylib: public jgo::IGraphic {
    public:
        /**
         * Should open a window in the library.
         * 
         * It should also do all the startup stuff.
         */
        void openWindow(std::string const &name, jgo::Rectangle const &rect) override;

        /**
         * Get the settings of your graphic library.
         */
        jgo::GraphicSettings getSettings(void) const override;

        /**
         * Preload all images.
         */
        void preloadImages(std::vector<std::string> const &images) override;

        /**
         * Preload all images.
         */
        void preloadModels(std::map<std::string, std::string> const &models) override;

        /**
         * Preaload all sounds.
         */
        void preloadSounds(std::vector<std::string> const &sounds) override;

        /**
         * Get the user input keys pressed.
         */
        std::vector<jgo::u32> getKeyPressed(void) override;

        /**
         * Should display the 'path' image (as texture) where the rectangle is.
         */
        void drawImage(
            std::string const &path,
            jgo::Rectangle const &rect,
            jgo::Rectangle const &where,
            jgo::Vector2 const &scale
        ) override;

        /**
         * Draw a rerctangle somewhere.
         */
        void drawRectangle(jgo::Rectangle const &rect, jgo::u32 color) override;

        /**
         * Get the mouse position.
         */
        jgo::Vector2 getMousePos(void) override;

        /**
         * Check if button is pressed, using bitshifting.
         */
        bool isMousePressing(jgo::MouseButton const &button) override;

        /**
         * Should display the 'text' text where the rectangle is.
         */
        void drawText(
            std::string const &text,
            jgo::Rectangle const &where,
            jgo::u32 color, // 0xaarrggbb
            std::string const &fontPath,
            std::size_t fontSize
        ) override;

        /**
         * Should display the 'model' which is a 3D model where the hitbox is.
         */
        void drawModelEx(
            std::string const &path,
            jgo::HitBox const &where,
            float angle,
            jgo::u32 color,
            jgo::Vector2 const &scale
        ) override;

        /**
         * Should display the 'model' which is a 3D model where the hitbox is.
         *
         * But it doesnt care about rotation.
         */
        void drawModel(
            std::string const &path,
            jgo::HitBox const &where,
            jgo::u32 color,
            jgo::Vector2 const &scale
        ) override;

        /**
         * Play a sound.
         */
        void playSound(std::string const &sound, float volume) override;

        /**
         * @brief To Know if the window is still opened
         * 
         * @return true 
         * @return false 
         */
        bool isWindowOpen() override;

        /**
         * Should close all the ressources and the window.
         */
        void closeWindow(void) override;

        /**
         * Update all textures and draw them here.
         */
        void update(void) override;

        /**
         * Set the background color
         */
        void setBackgroundColor(jgo::u32 color) override;

    private:
        std::map<std::string, Texture2D> _images;
        std::vector<std::string> _imagesToLoad;
        std::map<std::string, Model> _models;
        std::map<std::string, Sound> _sounds;
        Color _backgroundColor = BLACK;

        struct _Argument {
            enum {
                AT_Image,
                AT_Text,
                AT_Model,
                AT_Rectangle,
            } type;
            std::string path;
            jgo::Rectangle rects[2];
            jgo::Vector2 vec;
            std::string text;
            Color color;
            std::size_t size;
        };
        std::vector<_Argument> _actions;
};

void Raylib::openWindow(std::string const &name, jgo::Rectangle const &rect)
{
    InitWindow(rect.width, rect.height, name.c_str());
    InitAudioDevice();

    for (std::size_t i = 0; i < _imagesToLoad.size(); i++) {
        Texture2D tmp = LoadTexture(_imagesToLoad[i].c_str());
        _images[_imagesToLoad[i]] = std::move(tmp);
    }
}

jgo::GraphicSettings Raylib::getSettings(void) const
{
    jgo::GraphicSettings tmp;

    tmp.is3D = true;
    tmp.isTTY = false;
    return tmp;
}

void Raylib::preloadImages(std::vector<std::string> const &images)
{
    _imagesToLoad = images;
}

void Raylib::preloadModels(std::map<std::string, std::string> const &models)
{
    for (auto &mod : models) {
        Model tmp = LoadModel(mod.first.c_str());
        Texture2D tex = LoadTexture(mod.second.c_str());
        tmp.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
        _models[mod.first] = std::move(tmp);
    }
}

void Raylib::preloadSounds(std::vector<std::string> const &sounds)
{
    for (const auto& filename : sounds) {
        Sound buffer = LoadSound(filename.c_str());
        _sounds[filename] = std::move(buffer);
    }
}

static std::vector<int> Keys(void)
{
    return {KeyboardKey::KEY_A, KeyboardKey::KEY_B, KeyboardKey::KEY_C, KeyboardKey::KEY_D, KeyboardKey::KEY_SPACE, KeyboardKey::KEY_UP, KeyboardKey::KEY_DOWN, KeyboardKey::KEY_LEFT, KeyboardKey::KEY_RIGHT};
}

std::vector<jgo::u32> Raylib::getKeyPressed(void)
{
    std::vector<int> t = Keys();
    std::vector<jgo::u32> tmp;

    for (auto &i : t) {
        if (IsKeyDown(i))
            tmp.push_back(static_cast<jgo::u32>(i));
    }
    return tmp;
}

jgo::Vector2 Raylib::getMousePos(void)
{
    return {0, 0};
}

bool Raylib::isMousePressing(jgo::MouseButton const &button)
{
    return false;
}

static Color u32tocolor(jgo::u32 i) {
    return {
        static_cast<jgo::u8>((i >> 16) & 0xff),
        static_cast<jgo::u8>((i >> 8) & 0xff),
        static_cast<jgo::u8>(i & 0xff),
        static_cast<jgo::u8>((i >> 24) & 0xff)
    };
}

void Raylib::drawImage(std::string const &path, jgo::Rectangle const &rect, jgo::Rectangle const &where, jgo::Vector2 const &scale)
{
    _Argument e {
        .type = _Argument::AT_Image,
        .path = path,
        .rects = {rect, where},
        .vec = scale,
    };
    _actions.push_back(e);
}

void Raylib::drawRectangle(jgo::Rectangle const &rect, jgo::u32 color)
{
    _Argument e {
        .type = _Argument::AT_Rectangle,
        .rects = { rect, rect },
        .color = u32tocolor(color)
    };
    _actions.push_back(e);
}

void Raylib::drawText(std::string const &text, jgo::Rectangle const &where, jgo::u32 color, std::string const &fontPath, std::size_t fontSize)
{
    _Argument arg {
        .type = _Argument::AT_Text,
        .path = fontPath,
        .rects = { where, where },
        .text = text,
        .color = u32tocolor(color),
        .size = fontSize
    };

    _actions.push_back(arg);
}

void Raylib::drawModelEx(std::string const &path, jgo::HitBox const &where, float angle, jgo::u32 color, jgo::Vector2 const &scale)
{
    // _actions.push_back([&](){
    //     DrawModelEx(_models[path], (Vector3){where.pos.x / 2 + where.size.x, 600 - where.pos.x / 2 - where.size.y, 0}, Vector3{where.rotation.x, where.rotation.y, where.rotation.z}, angle, {scale.x, scale.y, scale.x}, WHITE);
    // });
}

void Raylib::drawModel(std::string const &path, jgo::HitBox const &where, jgo::u32 color, jgo::Vector2 const &scale)
{
    // _actions.push_back([&](){
    //     DrawModel(_models[path], (Vector3){where.pos.x / 2 + where.size.x, 600 - where.pos.x / 2 - where.size.y, 0}, scale.x, WHITE);
    // });
}

void Raylib::playSound(std::string const &sound, float volume)
{
    PlaySound(_sounds[sound]);
}

bool Raylib::isWindowOpen()
{
    return !WindowShouldClose();
}

void Raylib::setBackgroundColor(jgo::u32 i)
{
    _backgroundColor = u32tocolor(i);
}

void Raylib::update()
{
    BeginDrawing();
    ClearBackground(_backgroundColor);
    for (_Argument const &e : _actions)
        switch (e.type) {

            // draw image
            case _Argument::AT_Image:
                if (e.rects[0].x == -1)
                    DrawTextureEx(_images[e.path], Vector2{e.rects[1].x, e.rects[1].y}, 0, e.vec.x, WHITE);
            DrawTexturePro(
                _images[e.path],
                Rectangle{e.rects[0].x, e.rects[0].y, e.rects[0].width, e.rects[0].height},
                Rectangle{e.rects[1].x, e.rects[1].y, e.rects[1].width, e.rects[1].height},
                {e.rects[1].x / 2, e.rects[1].y / 2},
                0,
                WHITE
            );
            break;

            // draw rectangle
            case _Argument::AT_Rectangle:
            DrawRectangle(
                static_cast<int>(e.rects[0].x),
                static_cast<int>(e.rects[0].y),
                static_cast<int>(e.rects[0].width),
                static_cast<int>(e.rects[0].height),
                e.color
            );
            break;

            // the rest im lazy to handle
            default:
            break;
            
        }
    _actions.clear();
    EndDrawing();
}

void Raylib::closeWindow(void)
{
    CloseWindow();
    CloseAudioDevice();
}

exported(jgo::ptr<jgo::IGraphic>) createLibrary(void) {
    return std::make_shared<Raylib>(Raylib());
}
