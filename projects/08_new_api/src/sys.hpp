#ifndef SYS_HPP
#define SYS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
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

namespace render {

    struct IShader {
        virtual void init() = 0;
        virtual void release() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    enum BufferSize {
        BUFFER_SIZE_1 = 0,
        BUFFER_SIZE_2,
        BUFFER_SIZE_3,
        BUFFER_SIZE_4,
        BUFFER_SIZE_MAX_SIZE
    };

    struct VertexBuffer {
        uint32_t id = 0;
        std::vector<float> list;

        void clear();
        void add1(float x);
        void add2(float x, float y);
        void add2(const glm::vec2& v);
        void add3(float x, float y, float z);
        void add3(const glm::vec3& v);
        void add4(float x, float y, float z, float w);
        void add4(const glm::vec4& v);

        void add1List(std::vector<float>& l);
        void add2List(std::vector<glm::vec2>& l);
        void add3List(std::vector<glm::vec3>& l);
        void add4List(std::vector<glm::vec4>& l);

        void init();
        void release();
        void update();
        void bind();
        void unbind();

        size_t typeSize();
        size_t dataSize();
        
        size_t elementCount(BufferSize bs);
    };

    struct IndexBuffer {
        uint32_t id = 0;
        std::vector<uint32_t> list;

        void clear();
        void add1(uint32_t x);
        void add2(uint32_t x, uint32_t y);
        void add2(const glm::ivec2& v);
        void add3(uint32_t x, uint32_t y, uint32_t z);
        void add3(const glm::ivec3& v);
        void add4(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
        void add4(const glm::ivec4& v);

        void add1List(std::vector<uint32_t>& l);
        void add2List(std::vector<glm::ivec2>& l);
        void add3List(std::vector<glm::ivec3>& l);
        void add4List(std::vector<glm::ivec4>& l);

        void init();
        void release();
        void update();
        void bind();
        void unbind();

        size_t typeSize();
        size_t dataSize();
        
        size_t elementCount(BufferSize bs);
    };

    struct MainShader : public IShader {
        // Shader
        uint32_t vs = 0;
        uint32_t fs = 0;
        // Program
        uint32_t prog = 0;
        // Vertex Array
        uint32_t va = 0;
        // Program Setup
        // Uniforms
        uint32_t u_proj = 0;
        uint32_t u_view = 0;
        uint32_t u_model = 0;
        uint32_t u_tex0 = 0;

        // Attributes
        const uint32_t A_VERTICES = 0;
        const uint32_t A_TEXCOORDS = 1;

        virtual void init();
        virtual void release();
        virtual void bind();
        virtual void unbind();

        void setProjection(const glm::mat4& m);
        void setView(const glm::mat4& m);
        void setModel(const glm::mat4& m);

        // I'll need to add in
        // vertices ~ VertexBuffer
        // texCoords ~ VertexBuffer
        // indexBuffer ~ IndexBuffer
        void draw(
            VertexBuffer& vertices,
            VertexBuffer& texCoords,
            IndexBuffer& indencies
        );
    };


    void init();
    void release();

    void clear(const glm::vec4& clearColor);

    MainShader* getMainShader();

    void addTexture(std::string name, std::string path);
    void bindTexture(std::string name, GLenum active);
    void unbindTextre(GLenum active);
}

#endif