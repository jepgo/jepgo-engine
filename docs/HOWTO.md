## External Components

If you want to dig deeper in game developpement, you will reach a point where
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
    client.ecs.creatEntity();
    client.ecs.emplace_comp(client.ecs.currentEntity, Stamina());
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

