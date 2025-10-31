#ifndef SYS_HPP
#define SYS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_opengl3.h"


namespace app {

    struct Config {
        std::string caption;
        uint32_t width;
        uint32_t height;

        std::function<void()> initCB;
        std::function<void(SDL_Event*)> handleEventCB;
        std::function<void(float)> updateCB;
        std::function<void()> renderCB;
        std::function<void()> releaseCB;
    };

    void init(Config* config);
    void update();
    void release();

    std::string getCaption();
    uint32_t getWidth();
    uint32_t getHeight();
    float getWidthFloat();
    float getHeightFloat();
    float getAspect();
    void exit();

    SDL_Window* getWindow();
    SDL_GLContext getContext();

}

#endif