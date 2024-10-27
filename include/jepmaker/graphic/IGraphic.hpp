/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** IGraphic
*/

#pragma once

#include <memory>
#include <vector>
#include <map>
// #include <cwchar>
#include "jepmod/exported.hpp"
#include "jepengine/types.hpp"

/**
 * Your library class need to inherit from the IGraphic interface.
 */
namespace jgo {

    /**
     * The graphic settings
     */
    struct GraphicSettings {
        bool is3D;
        bool isTTY;
    };

    enum MouseButton {
        LeftClick,
        RightClick,
        MiddleClick
    };

    class IGraphic {
        public:
            IGraphic() {}

            /**
             * Should open a window in the library.
             * 
             * It should also do all the startup stuff.
             */
            virtual void
            openWindow(
                std::string const &name,
                jgo::Rectangle const &rect
            ) = 0;

            /**
             * Get the settings of your graphic library.
             */
            virtual jgo::GraphicSettings
            getSettings(void) const = 0;

            /**
             * Preload all images.
             */
            virtual void
            preloadImages(std::vector<std::string> const &images) = 0;

            /**
             * Preload all images.
             */
            virtual void
            preloadModels(std::map<std::string, std::string> const &models) = 0;

            /**
             * Preaload all sounds.
             */
            virtual void
            preloadSounds(std::vector<std::string> const &sounds) = 0;

            /**
             * Get the user input keys pressed.
             */
            virtual std::vector<jgo::u32>
            getKeyPressed(void) = 0;

            /**
             * Should display the 'path' image (as texture) where the rectangle is.
             */
            virtual void
            drawImage(
                std::string const &path,
                
                jgo::Rectangle const &rect,
                jgo::Rectangle const &where,
                jgo::Vector2 const &scale
            ) = 0;

            /**
             * Draw a rerctangle somewhere.
             */
            virtual void drawRectangle(
                jgo::Rectangle const &rect,
                jgo::u32 color
            ) = 0;

            /**
             * Get the mouse position.
             */
            virtual jgo::Vector2 getMousePos(void) = 0;

            /**
             * Check if button is pressed, using bitshifting.
             */
            virtual bool
            isMousePressing(jgo::MouseButton const &button) = 0;

            /**
             * Should display the 'text' text where the rectangle is.
             */
            virtual void
            drawText(
                std::string const &text,
                jgo::Rectangle const &where,
                jgo::u32 color, // 0xaarrggbb
                std::string const &fontPath,
                std::size_t fontSize
            ) = 0;

            /**
             * Should display the 'model' which is a 3D model where the hitbox is.
             */
            virtual void
            drawModelEx(
                std::string const &path,
                jgo::HitBox const &where,
                float angle,
                jgo::u32 color,
                jgo::Vector2 const &scale
            ) = 0;

            /**
             * Should display the 'model' which is a 3D model where the hitbox is.
             *
             * But it doesnt care about rotation.
             */
            virtual void
            drawModel(
                std::string const &path,
                jgo::HitBox const &where,
                jgo::u32 color,
                jgo::Vector2 const &scale
            ) = 0;

            /**
             * Play a sound.
             */
            virtual void
            playSound(std::string const &sound, float volume) = 0;

            /**
             * @brief To Know if the window still opened
             * 
             * @return true 
             * @return false 
             */
            virtual bool isWindowOpen(void) = 0;

            /**
             * Just a little check to asure if your window is still alive.
             */
            virtual void update(void) = 0;

            /**
             * Should close all the ressources and the window.
             */
            virtual void
            closeWindow(void) = 0;

            /**
             * Set the background color
             */
            virtual void setBackgroundColor(jgo::u32 color) = 0;
    };
}