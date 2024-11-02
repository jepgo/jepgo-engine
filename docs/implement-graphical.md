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
}

/**
 * Your generate function.
 */
exported(jgo::ptr<IGraphic>) generate(void) {
    return std::make_shared<IGraphic>(YourLib());
}
```