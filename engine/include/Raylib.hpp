/*
** EPITECH PROJECT, 2024
** GUI [WSL: Fedora]
** File description:
** RayLib
*/

#pragma once

#include <iostream>
#include <raylib.h>
#include <raymath.h>

class RayLib {
    public:
        RayLib(std::size_t height, std::size_t len, std::string name);
        ~RayLib();
        constexpr inline void SetCamPosition(Vector3 vec) {cam.position = vec;};
        inline void Start3DMode() {BeginMode3D(cam);};
        constexpr inline void SetCamTarget(Vector3 vec) {cam.target = vec;};
        constexpr inline void SetCamUp(Vector3 vec) {cam.up = vec;};
        constexpr inline void SetCamFovy(float vec) {cam.fovy = vec;};
        constexpr inline void SetCamProjection(CameraProjection pro) {cam.projection = pro;};
        inline void SetFps(std::size_t fps) {SetTargetFPS(fps);};
        inline void UpdateCam(CameraMode mode) {UpdateCamera(&cam, mode);};
        inline void StartDrawing() {BeginDrawing();};
        inline void ClearBack(Color color) {ClearBackground(color);};
        inline void DrawMyModel(Model &mod, Vector3 vec, float scale, Color c) {DrawModel(mod, vec, scale, c);};
        inline void Drawgrid(int slice, float grid) {DrawGrid(slice, grid);};
        inline void StopDrawing() {EndDrawing();};
        inline void Stop3DMode() {EndMode3D();};
        inline void Drawtext(std::string content, int x, int y, int font, Color color) {DrawText(content.c_str(), x, y, font, color);};
        inline void Drawfps(int x, int y) {DrawFPS(x, y);};
        inline void SetWindow(std::size_t height, std::size_t len) {SetWindowSize(height, len);};
        inline void SetMonitor() {int monitor = GetCurrentMonitor(); SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor)); moni = true;};
        Camera cam;
        bool moni = false;
    private:
};