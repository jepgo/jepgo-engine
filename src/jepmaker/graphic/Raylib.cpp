/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Raylib
*/

#include "raylib.h"
#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
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

        void InitAudio() override;

        /**
         * Should close all the ressources and the window.
         */
        void closeWindow(void) override;
    private:
        std::map<std::string, Texture2D> _images;
        std::map<std::string, Model> _models;
        std::map<std::string, Sound> _sounds;
};

void Raylib::openWindow(std::string const &name, jgo::Rectangle const &rect)
{
    InitWindow(rect.width, rect.height, name.c_str());
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
    for (std::size_t i = 0; i < images.size(); i++) {
        Texture2D tmp = LoadTexture(images[i].c_str());
        _images[images[i]] = std::move(tmp);
    }
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

std::vector<jgo::u32> Raylib::getKeyPressed(void)
{
    std::vector<jgo::u32> tmp;

    tmp.push_back(static_cast<jgo::u32>(GetKeyPressed()));
    return tmp;
}

void Raylib::drawImage(std::string const &path, jgo::Rectangle const &where, jgo::Vector2 const &scale)
{
    for (auto &image : _images) {
        if (image.first.compare(path) == 0) {
            float a = (where.width * scale.x);
            float b = (where.height * scale.y);
            DrawTexturePro(_images[path], Rectangle{where.x, where.y, where.width, where.height}, Rectangle{where.x, where.y, a, b}, {where.x / 2, where.y / 2}, 0, WHITE);
        }
    }
}

void Raylib::drawRectangle(jgo::Rectangle const &rect, jgo::u32 color)
{
    return;
}

jgo::Vector2 Raylib::getMousePos(void)
{
    return {0, 0};
}

bool Raylib::isMousePressing(jgo::MouseButton const &button)
{
    return false;
}

static Color ConvertToColor(std::uint32_t color)
{
    Color raylibColor;

    raylibColor.r = (color >> 24) & 0xFF;
    raylibColor.g = (color >> 16) & 0xFF;
    raylibColor.b = (color >> 8) & 0xFF;
    raylibColor.a = color & 0xFF;

    return raylibColor;
}

void Raylib::drawText(std::string const &text, jgo::Rectangle const &where, jgo::u32 color, std::string const &fontPath, std::size_t fontSize)
{
    DrawText(text.c_str(), (int)where.x, (int)where.y, fontSize, ConvertToColor(color));
}

void Raylib::drawModelEx(std::string const &path, jgo::HitBox const &where, float angle, jgo::u32 color, jgo::Vector2 const &scale)
{
    DrawModelEx(_models[path], (Vector3){where.pos.x / 2 + where.size.x, 600 - where.pos.x / 2 - where.size.y, 0}, Vector3{where.rotation.x, where.rotation.y, where.rotation.z}, angle, {scale.x, scale.y, scale.x}, WHITE);
}

void Raylib::drawModel(std::string const &path, jgo::HitBox const &where, jgo::u32 color, jgo::Vector2 const &scale)
{
    DrawModel(_models[path], (Vector3){where.pos.x / 2 + where.size.x, 600 - where.pos.x / 2 - where.size.y, 0}, scale.x, WHITE);
}

void Raylib::playSound(std::string const &sound, float volume)
{
    PlaySound(_sounds[sound]);
}

bool Raylib::isWindowOpen()
{
    return !WindowShouldClose();
}

void Raylib::InitAudio()
{
    InitAudioDevice();
}

void Raylib::closeWindow(void)
{
    CloseWindow();
}

exported(std::unique_ptr<jgo::IGraphic>) generate(void) {
    return std::make_unique<Raylib>(Raylib());
}
