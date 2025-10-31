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

std::string g_caption = "06_mipmap";
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
uint32_t main_u_tex0 = 0;

// Attributes
const uint32_t MAIN_A_VERTICES = 0;
//const uint32_t MAIN_A_COLORS = 1;
const uint32_t MAIN_A_TEXCOORDS = 1;

// Buffer
std::vector<glm::vec3> vertices_list;
uint32_t vertices_buffer = 0;
// Colors Buffer
/*
std::vector<glm::vec4> colors_list;
uint32_t colors_buffer = 0;
*/
std::vector<glm::vec2> texCoords_list;
uint32_t texCoords_id = 0;

// Index Buffer
std::vector<uint32_t> index_list;
uint32_t index_buffer = 0;

// Texture
uint32_t happyFaceTex = 0;

uint32_t _create_shader(GLenum type, std::string path);
uint32_t _create_program(std::vector<uint32_t> shaders);
void _delete_program(uint32_t id, std::vector<uint32_t> shaders);
uint32_t _create_texture2D(std::string path);

void renderGUI(std::function<void()> callback);

float yrot = 0.0f;


bool rotateX = false;
bool rotateY = true;
bool rotateZ = false;
glm::vec4 color = glm::vec4(glm::vec3(100.0f, 149.0f, 237.0f) / 255.0f, 1.0f);

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
    main_u_tex0 = glGetUniformLocation(main_prog, "tex0");
    glUniform1i(main_u_tex0, 0);

    // Setup Vertex Arrays
    glBindVertexArray(main_va);
    glEnableVertexAttribArray(MAIN_A_VERTICES);
    //glEnableVertexAttribArray(MAIN_A_COLORS);
    glEnableVertexAttribArray(MAIN_A_TEXCOORDS);
    glBindVertexArray(0);
    glUseProgram(0);



    // Do Vertices Buffer
    vertices_list.clear();
    vertices_list.push_back(glm::vec3(-1.0, 1.0, 0.0));
    vertices_list.push_back(glm::vec3(1.0, 1.0, 0.0));
    vertices_list.push_back(glm::vec3(-1.0, -1.0, 0.0));
    vertices_list.push_back(glm::vec3(1.0, -1.0, 0.0));

    glGenBuffers(1, &vertices_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices_list.size() * sizeof(glm::vec3), vertices_list.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*
    colors_list.clear();
    colors_list.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors_list.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors_list.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors_list.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

    glGenBuffers(1, &colors_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors_list.size() * sizeof(glm::vec4), colors_list.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    */


    texCoords_list.clear();
    texCoords_list.push_back(glm::vec2(0.0f, 0.0f));
    texCoords_list.push_back(glm::vec2(1.0f, 0.0f));
    texCoords_list.push_back(glm::vec2(0.0f, 1.0f));
    texCoords_list.push_back(glm::vec2(1.0f, 1.0f));

    glGenBuffers(1, &texCoords_id);
    glBindBuffer(GL_ARRAY_BUFFER, texCoords_id);
    glBufferData(GL_ARRAY_BUFFER, texCoords_list.size() * sizeof(glm::vec2), texCoords_list.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    index_list.clear();
    index_list.push_back(0);
    index_list.push_back(1);
    index_list.push_back(2);
    index_list.push_back(2);
    index_list.push_back(1);
    index_list.push_back(3);

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_list.size() * sizeof(uint32_t), index_list.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    happyFaceTex = _create_texture2D("happyface.png");


    // ImGui
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(g_window, g_context);
    ImGui_ImplOpenGL3_Init("#version 400");


}

void game_handleEvent(SDL_Event* e) {
    ImGui_ImplSDL3_ProcessEvent(e);
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
        glm::rotate(glm::mat4(1.0f), glm::radians(yrot), glm::vec3((rotateX) ? 1.0f : 0.0f, (rotateY) ? 1.0f : 0.0f, (rotateZ) ? 1.0f : 0.0f));

    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(main_prog);

    glUniformMatrix4fv(main_u_proj, 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(main_u_view, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(main_u_model, 1, GL_FALSE, &model[0][0]);

    glBindTexture(GL_TEXTURE_2D, happyFaceTex);

    glBindVertexArray(main_va);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glVertexAttribPointer(MAIN_A_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    //glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
    //glVertexAttribPointer(MAIN_A_COLORS, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, texCoords_id);
    glVertexAttribPointer(MAIN_A_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*
    glDrawArrays(GL_TRIANGLES, 0, vertices_list.size());
    */

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_TRIANGLES, index_list.size(), GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);



    renderGUI([&]() {

        ImGui::Begin("Hello, World");

        if(ImGui::Button("Hello")) {
            std::cout << "Hello, World\n";
        }

        ImGui::Checkbox("Rotate X", &rotateX);
        ImGui::Checkbox("Rotate Y", &rotateY);
        ImGui::Checkbox("Rotate Z", &rotateZ);

        ImGui::ColorPicker4("Clear Color", &color[0]);
        
        ImGui::End();
    });

}

void game_release() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    glDeleteTextures(1, &happyFaceTex);
    glDeleteBuffers(1, &index_buffer);
    glDeleteBuffers(1, &texCoords_id);
    //glDeleteBuffers(1, &colors_buffer);
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

uint32_t _create_texture2D(std::string path) {
    uint32_t temp = 0;

    SDL_Surface* surf = IMG_Load(path.c_str());

    if(surf == nullptr) {
        std::cout << path << " wasn't found\n";
        return 0;
    }

    glGenTextures(1, &temp);

    glBindTexture(GL_TEXTURE_2D, temp);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        surf->w, 
        surf->h, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        surf->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_DestroySurface(surf);
    return temp;
}

void renderGUI(std::function<void()> callback) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    callback();
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}