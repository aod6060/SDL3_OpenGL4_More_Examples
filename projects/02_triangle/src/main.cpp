#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


std::string g_caption = "02_triangle";
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



// Shader
uint32_t main_vs = 0;
uint32_t main_fs = 0;
// Program
uint32_t main_prog = 0;
// Vertex Array
uint32_t main_va = 0;
// Program Setup
// Uniforms
uint32_t main_u_proj = 0;
uint32_t main_u_view = 0;
uint32_t main_u_model = 0;
// Attributes
const uint32_t MAIN_A_VERTICES = 0;
// Buffer
std::vector<glm::vec3> vertices_list;
uint32_t vertices_buffer = 0;

uint32_t _create_shader(GLenum type, std::string path);
uint32_t _create_program(std::vector<uint32_t> shaders);
void _delete_program(uint32_t id, std::vector<uint32_t> shaders);

float yrot = 0.0f;

void game_init() {
    glEnable(GL_DEPTH_TEST);

    main_vs = _create_shader(GL_VERTEX_SHADER, "main.vs.glsl");
    main_fs = _create_shader(GL_FRAGMENT_SHADER, "main.fs.glsl");

    main_prog = _create_program({main_vs, main_fs});

    glGenVertexArrays(1, &main_va);

    glUseProgram(main_prog);
    // Uniforms
    main_u_proj = glGetUniformLocation(main_prog, "proj");
    main_u_view = glGetUniformLocation(main_prog, "view");
    main_u_model = glGetUniformLocation(main_prog, "model");
    // Setup Vertex Arrays
    glBindVertexArray(main_va);
    glEnableVertexAttribArray(MAIN_A_VERTICES);
    glBindVertexArray(0);
    glUseProgram(0);



    // Do Vertices Buffer
    vertices_list.clear();
    vertices_list.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    vertices_list.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
    vertices_list.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));

    glGenBuffers(1, &vertices_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices_list.size() * sizeof(glm::vec3), vertices_list.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void game_handleEvent(SDL_Event* e) {

}

void game_update(float delta) {
    yrot += 64.0f * delta;

    if(yrot > 360.0f) {
        yrot -= 360.0f;
    }
}

void game_render() {

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)g_width / (float)g_height, 1.0f, 1024.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(yrot), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec4 color = glm::vec4(glm::vec3(100.0f, 149.0f, 237.0f) / 255.0f, 1.0f);
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(main_prog);

    glUniformMatrix4fv(main_u_proj, 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(main_u_view, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(main_u_model, 1, GL_FALSE, &model[0][0]);

    glBindVertexArray(main_va);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glVertexAttribPointer(MAIN_A_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, vertices_list.size());

    glBindVertexArray(0);

    glUseProgram(0);
}

void game_release() {
    glDeleteBuffers(1, &vertices_buffer);
    vertices_list.clear();
    glDeleteVertexArrays(1, &main_va);
    _delete_program(main_prog, {main_vs, main_fs});
    glDeleteShader(main_vs);
    glDeleteShader(main_fs);
}


uint32_t _create_shader(GLenum type, std::string path) {
    uint32_t temp = glCreateShader(type);

    // Load Source
    std::ifstream in(path);
    in.seekg(0, std::ios::end);
    size_t fsize = in.tellg();
    in.seekg(0, std::ios::beg);
    std::string src;
    src.resize(fsize);
    in.read(src.data(), src.size());
    in.close();

    std::cout << src << "\n";

    const char* c_src = src.c_str();

    glShaderSource(temp, 1, &c_src, nullptr);

    glCompileShader(temp);

    int32_t len = 0;
    glGetShaderiv(temp, GL_INFO_LOG_LENGTH, &len);

    if(len > 0) {
        std::string log;
        log.resize(len);
        glGetShaderInfoLog(temp, log.size(), nullptr, log.data());
        std::cout << log << "\n";
    }
    return temp;
}

uint32_t _create_program(std::vector<uint32_t> shaders) {
    uint32_t temp = glCreateProgram();

    std::for_each(shaders.begin(), shaders.end(), [&](uint32_t shader) {
        glAttachShader(temp, shader);
    });
    
    glLinkProgram(temp);

    int32_t len = 0;
    glGetProgramiv(temp, GL_INFO_LOG_LENGTH, &len);

    if(len > 0) {
        std::string log;
        log.resize(len);
        glGetProgramInfoLog(temp, log.size(), nullptr, log.data());
        std::cout << log << "\n";
    }

    return temp;
}

void _delete_program(uint32_t id, std::vector<uint32_t> shaders) {
    std::for_each(shaders.begin(), shaders.end(), [&](uint32_t shader) {
        glDetachShader(id, shader);
    });
    glDeleteProgram(id);
}
