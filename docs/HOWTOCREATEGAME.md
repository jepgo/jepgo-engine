## Compilation

First, you need to clone the repository:
```bash
git clone git@github.com:EpitechPromo2027/B-CPP-500-PAR-5-1-rtype-elise.pipet.git R-Type
```

Whether you are on Windows or Linux, you need to have [CMake](https://cmake.org/) installed on your system to compile the project.

> [IMPORTANT]
> Some dependencies are managed by the CPM package manager, but some are low-level or platform-specific to be managed by CPM. You will need to install them manually on your system.

> Example on Linux: FLAC, X11..

> Example on Windows: OpenAL, OpenGL...

Then, you can compile the project using CMake, and it will download the dependencies for you.

#### List of dependencies:
- [Raylib](https://www.raylib.com/), for the graphic part
- [asio](https://think-async.com/Asio/), for the network part
- [SQLite](https://www.sqlite.org/index.html), for the database part (In development)
- [SQLiteORM](https://github.com/fnc12/sqlite_orm), for the database part (In development)
- [libconfig++](https://hyperrealm.github.io/libconfig/), for the configuration part

#### On Windows:
1. Launch Visual Studio
2. Open the project folder
3. Configure the project using CMake
4. Select the target you want to build (client, server, or both)
5. Click on the build button

#### On Linux:
```bash
mkdir build
cd build
cmake ../
cmake --build .
```

#### build.sh script

You can use the 'build.sh' script to compile the project, it automatically creates a 'build' folder and compiles the project in it. There is also a flag 'fclean' to remove entirely the 'build' folder if you need.
> If you're on Windows, you'll need a bash interpreter like Git Bash to run the script.
```bash	
./build.sh # Create build dir, configure and compile the project

./build.sh fclean # Remove entirely the build dir
```
## Usage
To launch the game you just have to use the following command:
```bash
./R-TYPE
```

## What's a ECS ?
A ECS means entity components systems.
The purpose of this practice is to create entities that are simply an ID or a number, allowing us to count them, and then add components to them, which are governed by systems, or in other words, rules. Components are just data that we want to assign to an entity. As for systems, they are simply rules that we want to apply to our game, based on the components that the entities possess. Let's take an example: I am a creator, and I decide to create a life. This life is nothing, it just has a name, number 1. Then I want this life to be able to walk, so I will give it the "legs" component. However, number 1 has legs, but it cannot walk yet because it doesn't know how to walk. So, I will teach it how to walk with a system that I will call "walking." If I now create a second life named number 2, I can also give it the "legs" component, which will allow it to walk using my walking system, or I can choose to give it nothing, or even create another component, like "speaking," and give it to it. I then create the "speaking" system, and that's it. Later, I can give number 1 the "speaking" component so that it, too, can speak.

## Why a ECS ?
The reasoning behind an ECS is quite simple. ECS allows for the generation of entities without having to manage each one individually, but instead by focusing on the behaviors that entities should have. The difference lies in the fact that if I decide during my program that a specific entity should be assigned or unassigned certain components, it is very easy to do with an ECS, unlike a classic OOP system. Moreover, it becomes very easy to add new features to our games. Since the data is separated from the functionality, we can either add new data or, using the existing data, introduce new functionality to our game via the systems.

## So let's have a code exemple
Managing entities is therefore quite simple; you just need a table that contains "gaps." The idea is simple: when an entity has a component, it has it, otherwise, there will be a gap. All of this is placed into what we will call a "Registry."
The creation of a component is quite simple. Let's say I want my entity to have a position and be able to display it. I will create two components: a Position and a Drawable, and I will create a system: DrawSystem:
```
class Positions {
    public:
        /**
         * @brief Construct a new Positions object
        *
        * @param x Position x of the object
        * @param y Position y of the Object
        */
        Positions(float x = 0, float y = 0) : x(x), y(y) {}
        ~Positions() {};
        Positions operator+(Positions const &pos) const
        {
            return Positions(this->x + pos.x, this->y + pos.y);
        }
        bool operator==(Positions const &pos) const
        {
            if (this->x == pos.x && this->y == pos.y)
                return true;
            return false;
        }
        float x;
        float y;
};

class Drawable {
    public:
        /**
        * @brief Construct a new Drawable object
        *
        * @param ind The index of the texture in the List of all the texture
        * @param r optional rectangle for The Sprite to Draw
        * @param s A Optional Vector of 2 float for the Scale
        */
        Drawable(std::size_t ind = 0, std::optional<Rectangle> r = std::nullopt, std::vector<float> s = {1, 1}) : index(ind), rect(r)
        {
            if (r.has_value())
                start = r.value().x;
            scale[0] = s[0];
            scale[1] = s[1];
        };
        ~Drawable() {
        };
        void change_ind(std::size_t ind) { index = ind; };
        std::size_t getIndex() { return index; };
        std::optional<Rectangle> &getRect() { return rect; };
        int start;
        float scale[2] = { 1, 1 };
        std::size_t index;
        std::optional<Rectangle> rect;
};
```
With these two components now complete, it's time to move on to the system:
```

static void draw(std::vector<Texture2D> &textures, Positions &pos, Drawable &draw)
    {
        if (rect.has_value()) {
            float a = (draw.rect.value().width * draw.scale[0]);
            float b = (draw.rect.value().height * draw.scale[1]);
            DrawTexturePro(textures[draw.index], draw.rect.value(), Rectangle{pos.x, pos.y, a, b}, {pos.x / 2, pos.y / 2}, 0, WHITE);
        } else {
            DrawTextureEx(textures[draw.index], {pos.x, pos.y}, 0.0f, draw.scale[0], WHITE);
        }
    }

/**
 * @brief The drawable System
 * 
 * @param window The window of the screen
 * @param r The Registry
 * @param texture The list of texture for all the sprite
 */
void DrawSystem::system(Register &r, std::vector<Texture2D> &texture)
{
    auto &pos = r.getComp<Positions>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < draw.size(); ++i) {
        if (draw[i].has_value() && pos[i].has_value()) {
            Draw(texture, pos[i].value(), );
        }
    }
}
```
So, to summarize what I just did: I created a Position class to manage the position of my entity, then a Drawable class that takes an index from a texture list, then a rectangle for the sprite (optional), and finally a scale vector. My system, for its part, takes the registry of all my entities and retrieves the list of all positions and drawables. It then iterates over all the drawables, checks if the entity has both a Drawable and a Position, and if so, it displays it, taking into account the data contained in the entity's Drawable class. In this example, I’m using Raylib as the graphics library. Of course, it actually goes through an interface that handles either SFML or Raylib (2D and 3D libraries).

## How to Add a Component ?
If you want to add your components to the engine, it's not very difficult. Let's say you have this component:
```
class Positions {
    public:
        /**
         * @brief Construct a new Positions object
        *
        * @param x Position x of the object
        * @param y Position y of the Object
        */
        Positions(float x = 0, float y = 0) : x(x), y(y) {}
        ~Positions() {};
        Positions operator+(Positions const &pos) const
        {
            return Positions(this->x + pos.x, this->y + pos.y);
        }
        bool operator==(Positions const &pos) const
        {
            if (this->x == pos.x && this->y == pos.y)
                return true;
            return false;
        }
        float x;
        float y;
};
```
For the needs of the engine, this file will need to be placed in a .hpp and a .cpp, meaning there will be Position.hpp and the definition in Position.cpp. Then, I will go to the engine's includeAll file and just add the name Position.hpp; the rest will take care of itself.
