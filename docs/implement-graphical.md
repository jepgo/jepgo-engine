## How to create my own Graphic Library

Your graphical library should have the following functions as exported:
```cpp
#include <memory>
#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
#include "jepmod/IGraphic.hpp"

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
         * Should display the 'path' image (as texture) where the rectangle is.
         */
        void drawImage(std::string const &path, jgo::Rectangle const &where);

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
        void drawModel(std::string const &path, jgo::HitBox const &where);

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