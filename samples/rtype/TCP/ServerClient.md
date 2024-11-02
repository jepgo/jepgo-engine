# Documentation: Multiplayer Game System

## Message Format

Each messages between the client and server ends with the delimiter `\x03`. This signifies the end of a message.

---

## Client Authentication

### Register / Login

#### **Request: Register/Login**

- **Register**: `21\x03`
- **Login**: `42\x03`

#### **Server Response: Username Prompt**

```
100 USERNAME=\x03
```
The server asks for the client's username.

#### **Client: Send Username**

The client sends their username to the server:

```
username\x03
```

#### **Server Response: Password Prompt**

```
110 PASSWORD=\x03
```
The server requests the client's password.

#### **Client: Send Password**

The client sends their password:

```
Password\x03
```

#### **Server Responses**

The server responds with one of the following:

- **Login successful**: 
  ```
  210 Login successful!\x03
  ```

- **Register successful**:
  ```
  220 Register successful!\x03
  ```

- **Username does not exist or Incorrect password**:
  ```
  410 Username does not exist or Incorrect password.\x03
  ```

- **Username already taken**:
  ```
  420 Username already.\x03
  ```

---

## Lobby Management

### Create Lobby

#### **Client: Create Lobby**

To create a new lobby, the client sends the following command:

```
250 CREATE LOBBY name\x03
```

Where `name` is the name of the new lobby.

#### **Server Response: Lobby Created**

If successful, the server responds with the ID of the newly created lobby and the current player count:

```
255 Lobby created with ID: id\x03
000 Player count: nb\x03
```

### Join Lobby

#### **Client: Join Lobby**

To join an existing lobby, the client sends the following command with the lobby's ID:

```
260 JOIN_LOBBY id\x03
```

#### **Server Responses**

- **Lobby successfully joined**:
  ```
  265 Lobby joined.\x03
  000 Player count: nb\x03
  ```

- **Lobby not found**:
  ```
  465 Lobby not found.\x03
  ```

### Leave Lobby

#### **Client: Leave Lobby**

To leave the current lobby, the client sends:

```
250 LEAVE_LOBBY name\x03
```

#### **Server Response: Left Lobby**

The server confirms the client has left the lobby:

```
000 Player count: nb\x03
255 Left lobby with ID: id\x03
```

---

## Game Session

### Start Game

#### **Client: Start Game**

The client can start the game by sending the following command:

```
290 PLAY\x03
```

#### **Server Responses**

The server responds with texture and path information required for the game:

```
200 TEXTURES\x03
Paths\x03
202\x03
```

---

## Summary of Commands

| **Client Command**                  | **Action**                            | **Server Response** |
|--------------------------------------|---------------------------------------|---------------------|
| `21\x03`                             | Register                              | `100 USERNAME=\x03` |
| `42\x03`                             | Login                                 | `100 USERNAME=\x03` |
| `username\x03`                       | Send username                         | `110 PASSWORD=\x03` |
| `password\x03`                       | Send password                         |  See responses above|
| `250 CREATE LOBBY name\x03`          | Create a new lobby                    | `255 Lobby created with ID: id\x03` |
| `260 JOIN_LOBBY id\x03`              | Join an existing lobby                | `265 Lobby joined.\x03` or `465 Lobby not found.\x03` |
| `250 LEAVE_LOBBY name\x03`           | Leave the lobby                       | `255 Left lobby with ID: id\x03` |
| `290 PLAY\x03`                       | Start the game                        | `200 TEXTURES\x03` |

---

This document provides the structure of client-server interactions within the multiplayer lobby system, including registering, joining and creating lobbies, and starting gameplay. All message transmissions are terminated by `\x03`.