#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


std::string g_caption = "01_Blank_Window";
uint32_t g_width = 1280;
uint32_t g_height = 720;

SDL_Window* g_window = nullptr;
SDL_GLContext g_context = nullptr;
bool g_running = true;


void game_init();
void game_handleEvent(SDL_Event* e);
void game_update(float delta);
void game_render();
void game_release();

int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    g_window = SDL_CreateWindow(
        g_caption.c_str(),
        g_width,
        g_height,
        SDL_WINDOW_OPENGL
    );

    g_context = SDL_GL_CreateContext(g_window);
    glewInit();


    game_init();

    SDL_Event event;

    uint32_t pre_time = SDL_GetTicks();
    uint32_t curr_time = 0;
    float delta = 0.0f;


    while(g_running) {
        curr_time = SDL_GetTicks();
        delta = (curr_time - pre_time) / 1000.0f;
        pre_time = curr_time;

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                g_running = false;
            }

            game_handleEvent(&event);
        }

        game_update(delta);
        game_render();

        SDL_GL_SwapWindow(g_window);
    }

    game_release();

    SDL_GL_DestroyContext(g_context);
    SDL_DestroyWindow(g_window);
    SDL_Quit();

    return 0;
}


void game_init() {
    glEnable(GL_DEPTH_TEST);

}

void game_handleEvent(SDL_Event* e) {

}

void game_update(float delta) {
    std::cout << "Delta: " << delta << "\n";
}

void game_render() {
    glm::vec4 color = glm::vec4(glm::vec3(100.0f, 149.0f, 237.0f) / 255.0f, 1.0f);
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
}

void game_release() {

}
