/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** clientTCP
*/

#include <iostream>
#include <map>
#include "clientTCP.hpp"
#include "Raylib.hpp"

/**
 * @enum ClientState
 * @brief customer status based on actions taken
 * 
 * @var ClientState CHOOSE_ACTION
 * @brief login or register menu
 * 
 * @var ClientState LOGIN_REGISTER
 * @brief login and register page
 * 
 * @var ClientState SUCCESS
 * @brief Login/Register successful!
 * 
 * @var ClientState IN_LOBBY
 * @brief lobby page
 * 
 * @var ClientState PLAYING
 * @brief textures received and game launch
 * 
 * @var ClientState LOBBY_MENU
 * @brief create or choose a lobby page
 */
enum ClientState
{
	CHOOSE_ACTION,
	LOGIN_REGISTER,
	SUCCESS,
	IN_LOBBY,
	PLAYING,
	LOBBY_MENU
};

/**
 * @brief the state according to the server message
 *
 */
std::map<std::string, ClientState> stateOpcode =
	{
		{"410 Username does not exist or Incorrect password.", LOGIN_REGISTER},
		{"420 Username already exists.", LOGIN_REGISTER},
		{"210 Login successful!", SUCCESS},
		{"220 Registration successful!", SUCCESS}};

/**
 * @brief handle the selection register login
 *
 * @param loginButton
 * @param registerButton
 * @param client
 * @param state
 */
void HandleSelectLoginRegister(BoxRaylib &loginButton,
							   BoxRaylib &registerButton,
							   Client &client,
							   ClientState &state)
{
	Text().drawText("Do you want to Login or Register ?", 180, 150, 20, 80, 80, 80, 255);

	loginButton.drawBox("Login", 200, 200, 200, 255, 80, 80, 80, 255);
	registerButton.drawBox("Register", 200, 200, 200, 255, 80, 80, 80, 255);
	if (loginButton.isPressed())
	{
		client.sendMessage("42");
		state = LOGIN_REGISTER;
	}
	if (registerButton.isPressed())
	{
		client.sendMessage("21");
		state = LOGIN_REGISTER;
	}
	return;
}

/**
 * @brief handle the action in the page register or login
 *
 * @param state state of the window page
 * @param usernameBox input box username
 * @param passwordBox input box password
 * @param confirmButton button confirm
 * @param client socket client
 */
void handleLoginRegister(ClientState &state, InputBoxRaylib &usernameBox,
						 InputBoxRaylib &passwordBox, BoxRaylib &confirmButton, Client &client)
{
	BoxRaylib back(0, 0, 150, 40);
	back.drawBox("Back", 200, 200, 200, 255, 80, 80, 80, 255);
	Text().drawText("Username:", 200, 150, 20, 80, 80, 80, 255);
	usernameBox.draw();
	Text().drawText("Password:", 200, 240, 20, 80, 80, 80, 255);
	passwordBox.draw(true);

	confirmButton.drawBox("Confirm", 200, 200, 200, 255, 80, 80, 80, 255);

	if (confirmButton.isPressed())
	{
		std::string r = client.receiveMessage();
		client.sendMessage(usernameBox.getText());
		r = client.receiveMessage();
		client.sendMessage(passwordBox.getText());
		std::string response = client.receiveMessage();
		std::cout << "Server Response: " << response << std::endl;

		state = stateOpcode[response];
		if (state != SUCCESS)
			Text().drawText(response, 200, 100, 20, 230, 41, 55, 255);
	}

	if (back.isPressed())
		state = CHOOSE_ACTION;
	return;
}

/**
 * @brief Handle the state when the client is in the lobby.
 *
 * @param state Client state
 * @param client Client object to communicate with the server
 * @param playButton Button to trigger the game start
 */
void handleLobby(ClientState &state, Client &client, BoxRaylib &playButton)
{
	Text().drawText("Lobby Id :" + std::to_string(client.lobby_id), 250, 150, 30, 80, 80, 80, 255);
	Text().drawText("You are in the lobby.", 250, 120, 30, 80, 80, 80, 255);
	Text().drawText("Nb Players in Lobby: " + std::to_string(client.nb_players_in_my_lobby), 250, 250, 30, 80, 80, 80, 255);

	BoxRaylib leaveLobbyButton(320, 200, 150, 40);
	leaveLobbyButton.drawBox("Leave Looby", 200, 200, 200, 255, 230, 41, 55, 255);
	playButton.drawBox("Play", 200, 200, 200, 255, 80, 80, 80, 255);

	if (leaveLobbyButton.isPressed())
	{
		client.sendMessage("270 LEAVE_LOBBY " + std::to_string(client.lobby_id));
		client.receiveMessage();
		state = LOBBY_MENU;
	}

	if (playButton.isPressed())
	{
		client.sendMessage("290 PLAY");
		std::string response = client.receiveMessage();
		std::cout << "Server Response: " << response << std::endl;

		if (response.starts_with("200 TEXTURES"))
		{
			size_t id_pos = response.find("nb=");
			id_pos += 3;
			int num_textures = std::stoi(response.substr(id_pos));
			for (int i = 0; i < num_textures; ++i)
			{
				std::string texture = client.receiveMessage();
				std::cout << "Received texture: " << texture << std::endl;
			}
			client.receiveMessage();
			state = PLAYING;
		}
	}
}

/**
 * @brief handle menu lobby
 *
 * @param state
 * @param client
 */
void handleLobbyMenu(ClientState &state, Client &client, InputBoxRaylib &lobbyIDBox, InputBoxRaylib &lobbyNameBox)
{
	BoxRaylib createLobbyButton(200, 250, 150, 40);
	BoxRaylib joinLobbyButton(400, 250, 150, 40);
	
	Text().drawText("Lobby Menu", 300, 150, 20, 80, 80, 80, 255);
	createLobbyButton.drawBox("Create Lobby", 200, 200, 200, 255, 80, 80, 80, 255);
	joinLobbyButton.drawBox("Join Lobby", 200, 200, 200, 255, 80, 80, 80, 255);
	Text().drawText("Lobby Name :", 200, 300, 20, 80, 80, 80, 255);
	lobbyNameBox.draw();
	Text().drawText("Lobby Id :", 400, 300, 20, 80, 80, 80, 255);
	lobbyIDBox.draw();

	if (createLobbyButton.isPressed())
	{
		client.sendMessage("250 CREATE_LOBBY " + lobbyNameBox.getText());
		std::string response = client.receiveMessage();
		std::cout << "Lobby created: " << response << std::endl;

		size_t id_pos = response.find("ID: ");
		id_pos += 4;
		client.lobby_id = std::stoi(response.substr(id_pos));
		state = IN_LOBBY;
	}
	if (joinLobbyButton.isPressed())
	{
		std::string lobbyID = lobbyIDBox.getText();
		client.sendMessage("260 JOIN_LOBBY " + lobbyID);
		std::string response = client.receiveMessage();
		if (response == "Lobby not found.")
		{
			Text().drawText(response, 200, 100, 20, 230, 41, 55, 255);
		}
		else
		{
			std::cout << "Joined lobby: " << response << std::endl;
			client.lobby_id = std::atoi(lobbyID.c_str());
			state = IN_LOBBY;
		}
	}
}

/**
 * @brief Handle lobby updates by listening for server messages
 * 
 * @param client The TCP client instance
 * @param state Current state of the client
 */
void handleLobbyUpdates(Client &client, ClientState &state)
{
    while (state == IN_LOBBY)
    {
        std::string message = client.receiveMessage();
        
        if (message.find("Player count:") != std::string::npos) {
            std::cout << "Lobby update: " << message << std::endl;
			client.nb_players_in_my_lobby = std::stoi(message.substr(message.find(":") + 1));
        } else if (message.find("START_GAME") != std::string::npos) {
            std::cout << "Game is starting!" << std::endl;
            state = SUCCESS;
        }
		else if (message.find("Left lobby") != std::string::npos) {
			state = LOBBY_MENU;
		}
    }
	return;
}

int launchClient(int ac, char **av)
{
	const int screenWidth = 800;
	const int screenHeight = 600;
	Raylib ray;
	ray.Init(screenWidth, screenHeight, "R-Type");

	ClientState state = CHOOSE_ACTION;
	InputBoxRaylib usernameBox(200, 180, 150, 40);
	InputBoxRaylib passwordBox(200, 270, 150, 40);
	InputBoxRaylib lobbyIDBox(400, 330, 150, 40);
	InputBoxRaylib lobbyNameBox(200, 330, 150, 40);

	BoxRaylib loginButton(200, 250, 150, 40);
	BoxRaylib registerButton(400, 250, 150, 40);
	BoxRaylib confirmButton(320, 350, 150, 40);
	BoxRaylib playButton(320, 400, 150, 40);

	std::string address(av[1]);
	Client client(address, std::atoi(av[2]));
	std::thread updateLobby;
	ray.setFramePerSec(60);

	while (!ray.windowClosed())
	{
		usernameBox.handleInput();
		passwordBox.handleInput();
		lobbyIDBox.handleInput();
		lobbyNameBox.handleInput();

		if (lobbyIDBox.isPressed()) {
			usernameBox.isActive = false;
			passwordBox.isActive = false;
			lobbyNameBox.isActive = false;
			lobbyIDBox.isActive = true;
		}
		if (lobbyNameBox.isPressed()) {
			usernameBox.isActive = false;
			passwordBox.isActive = false;
			lobbyIDBox.isActive = false;
			lobbyNameBox.isActive = true;
		}
		if (usernameBox.isPressed())
		{
			usernameBox.isActive = true;
			passwordBox.isActive = false;
		}
		if (passwordBox.isPressed())
		{
			usernameBox.isActive = false;
			passwordBox.isActive = true;
		}

		ray.beginDraw();
		ray.clearWindowIn(245, 245, 245, 255);

		if (state == CHOOSE_ACTION)
		{
			HandleSelectLoginRegister(loginButton, registerButton, client, state);
		}
		else if (state == LOGIN_REGISTER)
		{
			handleLoginRegister(state, usernameBox, passwordBox, confirmButton, client);
		}
		else if (state == SUCCESS)
		{
			Text().drawText("Login/Register successful!", 250, 250, 30, 80, 80, 80, 255);
			state = LOBBY_MENU;
		}
		else if (state == IN_LOBBY)
		{
			handleLobby(state, client, playButton);
			if (!updateLobby.joinable()) {
                updateLobby = std::thread(handleLobbyUpdates, std::ref(client), std::ref(state));
            }
		}
		else if (state == LOBBY_MENU)
		{
			handleLobbyMenu(state, client, lobbyIDBox, lobbyNameBox);
		}
		else if (state == PLAYING)
		{
			Text().drawText("Playing the game!", 250, 250, 30, 80, 80, 80, 255);
		}
		ray.endDraw();
	}
	if (updateLobby.joinable())
		updateLobby.join();
	ray.closeWindow();
	return 0;
}

int main(int ac, char **av)
{
	launchClient(ac, av);
	return 0;
}
