## How to create my own Graphic Library

Your graphical library should have the following functions as exported:
```cpp
#include <memory>
// #include <cwchar>
#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
#include "jepmaker/graphic/IGraphic.hpp"

/**
 * Your library class need to inherit from the IGraphic interface.
 */
class YourLib: public IGraphic {
    public:
        /**
         * Should open a window in the library.
         * 
         * It should also do all the startup stuff.
         */
        void openWindow(std::string const &name, jgo::Rectangle const &rect);

        /**
         * Get the settings of your graphic library.
         */
        jgo::GraphicSettings const &getSettings(void);

        /**
         * Preload all images.
         */
        void preloadImages(std::vector<std::string> const &images);

        /**
         * Preload all images.
         */
        void preloadModels(std::vector<std::string> const &models);

        /**
         * Preaload all sounds.
         */
        void preloadSounds(std::vector<std::string> const &sounds);

        /**
         * Get the user input keys pressed.
         */
        std::vector<jgo::u32> getKeyPressed(void);

        /**
         * Should display the 'path' image (as texture) where the rectangle is.
         */
        void drawImage(
            std::string const &path,
            jgo::Rectangle const &where,
            jgo::Vector2 const &scale,
        );

        /**
         * Draw a rerctangle somewhere.
         */
        void drawRectangle(jgo::Rectangle const &rect, jgo::u32 color);

        /**
         * Get the mouse position.
         */
        jgo::Vector2 getMousePos(void);

        /**
         * Check if button is pressed, using bitshifting.
         */
        bool isMousePressing(jgo::MouseButton const &button);

        /**
         * Should display the 'text' text where the rectangle is.
         */
        void drawText(
            std::string const &text,
            jgo::Rectangle const &where,
            jgo::u32 color, // 0xaarrggbb
            std::string const &fontPath,
            std::size_t fontSize
        );

        /**
         * Should display the 'model' which is a 3D model where the hitbox is.
         */
        void drawModelEx(
            std::string const &path,
            jgo::HitBox const &where,
            float angle,
            jgo::u32 color
        );

        /**
         * Should display the 'model' which is a 3D model where the hitbox is.
         *
         * But it doesnt care about rotation.
         */
        void drawModel(
            std::string const &path,
            jgo::HitBox const &where,
            jgo::u32 color
        );

        /**
         * Play a sound.
         */
        void playSound(std::string const &sound, float volume);

        /**
         * Should close all the ressources and the window.
         */
        void closeWindow(void);
}

/**
 * Your generate function.
 */
exported(std::unique_ptr<IGraphic>) generate(void) {
    return std::make_unique<IGraphic>(YourLib());
}
```