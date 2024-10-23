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
To launch the server, you can use the following command:
```bash
./r-type_server [port]
```

To launch the client, you can use the following command:
```bash
./r-type_client [ip] [port]
```

## External Components

If you want to dig deeper in game development, you will reach a point where
it would be necessary for you to use your own components. Jepgo have an api for
you to do that. Let's understand using an example:

Let's say you have this component:
```cpp
// in StaminaComponent.hpp

class Stamina {
    public:
        inline Stamina(unsigned short int num) noexcept {
            _stamina = num;
        }
        inline auto getStamina(void) const noexcept -> unsigned short int {
            return _stamina;
        }
    private:
        unsigned short _stamina;
}
```

### Singleplayer experience

If your game only include a client (single player game), you can simply use
your component like any other, by including your file:
```cpp
// in game.client.cpp

#include "jepgame/gamemaker/Client.hpp"
#include "StaminaComponent.hpp"

exported(void) onStart(jgo::Client &client)
{
    client.ecs.createEntity();
    client.ecs.emplaceComp(client.ecs.currentEntity, Stamina());
}
```

### Muliplayer experience

> [!IMPORTANT]
> If you want to use components in multiplayer experiences, they **CAN NOT**
> handle pointers, vectors and any form of non-static sized variables. <br>
> They can only support fixed-sized variables.

However, it's not that simple using multiplayer. Why ? Because you will have
to send the components one by one from the server to the client.

1. You will firstly place your Components somewhere you know about (for
example where you have your `game.server.cpp` file)

2. Then you will have to use external components in your server:
```cpp
// in game.server.cpp

#include "jepgame/gamemaker/external.hpp" // include external before server
#include "jepgame/gamemaker/Server.hpp"

exported(void) onStart(jgo::Server &server)
{
    client.ecs.useExternal("StaminaComponent.hpp");
}
```

3. You can then send the external components in your update function, or
anywhere you want:
```cpp
exported(void) onUpdate(jgo::Server &server)
{
    client.sendAllExternal(); // use sendAll for all External components
}
```

4. The, in your client, you will have to also enable **THE SAME EXTERNALS**
that you used in your client.
```cpp
// in game.client.cpp

#include "jepgame/gamemaker/external.hpp"
#include "jepgame/gamemaker/Client.hpp"

exported(void) onStart(jgo::Client &client)
{
    client.ecs.useExternal("StaminaComponent.hpp");
}
```

5. Notify that you can receive some external components in your client:
```cpp
exported(void) onServerMessage(jgo::Client &client, std::string const &msg)
{
    if (client.isExternalComponent(msg))
        return;
    // continue treating components
}
```

The code will automatically fill your components for you !

## Add new source files
> [IMPORTANT]
> Whenever a change has been made in the CMakeLists.txt, you will have to clean the CMake caches and recompile the project.

If you want to add new source files, you can simply add them to the `src` folder in the corresponding part of the project (engine, jepgame, jepmod...).

Then you'll need to add them in the CMakeLists.txt, at the end of the add_executable() or add_library() corresponding to the part of the project you added the files to.

Example if you want to add a 'example.cpp' file to the engine:
```cmake
add_library(jepengine STATIC
    ...
    ...
    ...
    ${EngineSRC}/Draw3DSystem.cpp
    ${EngineSRC}/Rotation3DSystem.cpp
    ${EngineSRC}/example.cpp
)
```

## Add new dependencies to CPM package manager
> [IMPORTANT]
> Whenever a change has been made in the CMakeLists.txt, you will have to clean the CMake caches and recompile the project.

If you want to add new dependencies, you can simply add them to the `CMakeLists.txt` file in the corresponding part of the project (engine, jepgame, jepmod...).

You'll need to add them in the `CMakeLists.txt` file, and add a `CPMAddPackage()` call with the package name and the version you want to use.

Example if you want to add the `fmt` library to the engine:
```cmake
CPMAddPackage(
    NAME fmt # Name of the package
    GIT_REPOSITORY https://github.com/fmtlib/fmt # URL to the repository
    GIT_TAG 11.0.2 # Version of the package (usually findable on the package's GitHub page)
)
```

Then you can link the library to the project by adding the following line in the `target_link_libraries()` call:
```cmake
target_link_libraries(jepengine PRIVATE fmt) # here the flag is 'fmt' but it is dependent on the package
```