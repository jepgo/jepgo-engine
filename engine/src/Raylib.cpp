/*
** EPITECH PROJECT, 2024
** GUI [WSL: Fedora]
** File description:
** RayLib
*/

#include "Raylib.hpp"

RayLib::RayLib(std::size_t height, std::size_t len, std::string name)
{
    InitWindow(height, len, name.c_str());
    InitAudioDevice();
    cam.position = {50.0f, 50.0f, 50.0f};
    cam.target = {0.0f, 0.0f, 0.0f};
    cam.up = {0.0f, 1.0f, 0.0f};
    cam.fovy = 90.f;
    cam.projection = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);
}

RayLib::~RayLib()
{
    CloseWindow();
}