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

namespace input {
    enum InputState {
        IS_RELEASED = 0,
        IS_PRESSED_ONCE,
        IS_PRESSED,
        IS_RELEASED_ONCE,
        IS_MAX_SIZE
    };

    // lookat SDL3/SDL_scancode.h
    enum Keyboard {
        KB_UNKNOWN = 0,
        KB_A = 4,
        KB_B = 5,
        KB_C = 6,
        KB_D = 7,
        KB_E = 8,
        KB_F = 9,
        KB_G = 10,
        KB_H = 11,
        KB_I = 12,
        KB_J = 13,
        KB_K = 14,
        KB_L = 15,
        KB_M = 16,
        KB_N = 17,
        KB_O = 18,
        KB_P = 19,
        KB_Q = 20,
        KB_R = 21,
        KB_S = 22,
        KB_T = 23,
        KB_U = 24,
        KB_V = 25,
        KB_W = 26,
        KB_X = 27,
        KB_Y = 28,
        KB_Z = 29,
        KB_1 = 30,
        KB_2 = 31,
        KB_3 = 32,
        KB_4 = 33,
        KB_5 = 34,
        KB_6 = 35,
        KB_7 = 36,
        KB_8 = 37,
        KB_9 = 38,
        KB_0 = 39,
        KB_RETURN = 40,
        KB_ESCAPE = 41,
        KB_BACKSPACE = 42,
        KB_TAB = 43,
        KB_SPACE = 44,
        KB_MINUS = 45,
        KB_EQUALS = 46,
        KB_LEFTBRACKET = 47,
        KB_RIGHTBRACKET = 48,
        KB_BACKSLASH = 49,
        KB_NONUSHASH = 50,
        KB_SEMICOLON = 51,
        KB_APOSTROPHE = 52,
        KB_GRAVE = 53,
        KB_COMMA = 54,
        KB_PERIOD = 55,
        KB_SLASH = 56,
        KB_CAPSLOCK = 57,
        KB_F1 = 58,
        KB_F2 = 59,
        KB_F3 = 60,
        KB_F4 = 61,
        KB_F5 = 62,
        KB_F6 = 63,
        KB_F7 = 64,
        KB_F8 = 65,
        KB_F9 = 66,
        KB_F10 = 67,
        KB_F11 = 68,
        KB_F12 = 69,
        KB_PRINTSCREEN = 70,
        KB_SCROLLLOCK = 71,
        KB_PAUSE = 72,
        KB_INSERT = 73,
        KB_HOME = 74,
        KB_PAGEUP = 75,
        KB_DELETE = 76,
        KB_END = 77,
        KB_PAGEDOWN = 78,
        KB_RIGHT = 79,
        KB_LEFT = 80,
        KB_DOWN = 81,
        KB_UP = 82,
        KB_NUMLOCKCLEAR = 83,
        KB_KP_DIVIDE = 84,
        KB_KP_MULTIPLY = 85,
        KB_KP_MINUS = 86,
        KB_KP_PLUS = 87,
        KB_KP_ENTER = 88,
        KB_KP_1 = 89,
        KB_KP_2 = 90,
        KB_KP_3 = 91,
        KB_KP_4 = 92,
        KB_KP_5 = 93,
        KB_KP_6 = 94,
        KB_KP_7 = 95,
        KB_KP_8 = 96,
        KB_KP_9 = 97,
        KB_KP_0 = 98,
        KB_KP_PERIOD = 99,
        KB_NONUSBACKSLASH = 100,
        KB_APPLICATION = 101,
        KB_POWER = 102,
        KB_KP_EQUALS = 103,
        KB_F13 = 104,
        KB_F14 = 105,
        KB_F15 = 106,
        KB_F16 = 107,
        KB_F17 = 108,
        KB_F18 = 109,
        KB_F19 = 110,
        KB_F20 = 111,
        KB_F21 = 112,
        KB_F22 = 113,
        KB_F23 = 114,
        KB_F24 = 115,
        KB_EXECUTE = 116,
        KB_HELP = 117,    /**< AL Integrated Help Center */
        KB_MENU = 118,    /**< Menu (show menu) */
        KB_SELECT = 119,
        KB_STOP = 120,    /**< AC Stop */
        KB_AGAIN = 121,   /**< AC Redo/Repeat */
        KB_UNDO = 122,    /**< AC Undo */
        KB_CUT = 123,     /**< AC Cut */
        KB_COPY = 124,    /**< AC Copy */
        KB_PASTE = 125,   /**< AC Paste */
        KB_FIND = 126,    /**< AC Find */
        KB_MUTE = 127,
        KB_VOLUMEUP = 128,
        KB_VOLUMEDOWN = 129,
        KB_KP_COMMA = 133,
        KB_KP_EQUALSAS400 = 134,
        KB_INTERNATIONAL1 = 135,
        KB_INTERNATIONAL2 = 136,
        KB_INTERNATIONAL3 = 137, /**< Yen */
        KB_INTERNATIONAL4 = 138,
        KB_INTERNATIONAL5 = 139,
        KB_INTERNATIONAL6 = 140,
        KB_INTERNATIONAL7 = 141,
        KB_INTERNATIONAL8 = 142,
        KB_INTERNATIONAL9 = 143,
        KB_LANG1 = 144, /**< Hangul/English toggle */
        KB_LANG2 = 145, /**< Hanja conversion */
        KB_LANG3 = 146, /**< Katakana */
        KB_LANG4 = 147, /**< Hiragana */
        KB_LANG5 = 148, /**< Zenkaku/Hankaku */
        KB_LANG6 = 149, /**< reserved */
        KB_LANG7 = 150, /**< reserved */
        KB_LANG8 = 151, /**< reserved */
        KB_LANG9 = 152, /**< reserved */
        KB_ALTERASE = 153,    /**< Erase-Eaze */
        KB_SYSREQ = 154,
        KB_CANCEL = 155,      /**< AC Cancel */
        KB_CLEAR = 156,
        KB_PRIOR = 157,
        KB_RETURN2 = 158,
        KB_SEPARATOR = 159,
        KB_OUT = 160,
        KB_OPER = 161,
        KB_CLEARAGAIN = 162,
        KB_CRSEL = 163,
        KB_EXSEL = 164,
        KB_KP_00 = 176,
        KB_KP_000 = 177,
        KB_THOUSANDSSEPARATOR = 178,
        KB_DECIMALSEPARATOR = 179,
        KB_CURRENCYUNIT = 180,
        KB_CURRENCYSUBUNIT = 181,
        KB_KP_LEFTPAREN = 182,
        KB_KP_RIGHTPAREN = 183,
        KB_KP_LEFTBRACE = 184,
        KB_KP_RIGHTBRACE = 185,
        KB_KP_TAB = 186,
        KB_KP_BACKSPACE = 187,
        KB_KP_A = 188,
        KB_KP_B = 189,
        KB_KP_C = 190,
        KB_KP_D = 191,
        KB_KP_E = 192,
        KB_KP_F = 193,
        KB_KP_XOR = 194,
        KB_KP_POWER = 195,
        KB_KP_PERCENT = 196,
        KB_KP_LESS = 197,
        KB_KP_GREATER = 198,
        KB_KP_AMPERSAND = 199,
        KB_KP_DBLAMPERSAND = 200,
        KB_KP_VERTICALBAR = 201,
        KB_KP_DBLVERTICALBAR = 202,
        KB_KP_COLON = 203,
        KB_KP_HASH = 204,
        KB_KP_SPACE = 205,
        KB_KP_AT = 206,
        KB_KP_EXCLAM = 207,
        KB_KP_MEMSTORE = 208,
        KB_KP_MEMRECALL = 209,
        KB_KP_MEMCLEAR = 210,
        KB_KP_MEMADD = 211,
        KB_KP_MEMSUBTRACT = 212,
        KB_KP_MEMMULTIPLY = 213,
        KB_KP_MEMDIVIDE = 214,
        KB_KP_PLUSMINUS = 215,
        KB_KP_CLEAR = 216,
        KB_KP_CLEARENTRY = 217,
        KB_KP_BINARY = 218,
        KB_KP_OCTAL = 219,
        KB_KP_DECIMAL = 220,
        KB_KP_HEXADECIMAL = 221,
        KB_LCTRL = 224,
        KB_LSHIFT = 225,
        KB_LALT = 226, /**< alt, option */
        KB_LGUI = 227, /**< windows, command (apple), meta */
        KB_RCTRL = 228,
        KB_RSHIFT = 229,
        KB_RALT = 230, /**< alt gr, option */
        KB_RGUI = 231, /**< windows, command (apple), meta */
        KB_MODE = 257,
        KB_SLEEP = 258,                   /**< Sleep */
        KB_WAKE = 259,                    /**< Wake */
        KB_CHANNEL_INCREMENT = 260,       /**< Channel Increment */
        KB_CHANNEL_DECREMENT = 261,       /**< Channel Decrement */
        KB_MEDIA_PLAY = 262,          /**< Play */
        KB_MEDIA_PAUSE = 263,         /**< Pause */
        KB_MEDIA_RECORD = 264,        /**< Record */
        KB_MEDIA_FAST_FORWARD = 265,  /**< Fast Forward */
        KB_MEDIA_REWIND = 266,        /**< Rewind */
        KB_MEDIA_NEXT_TRACK = 267,    /**< Next Track */
        KB_MEDIA_PREVIOUS_TRACK = 268, /**< Previous Track */
        KB_MEDIA_STOP = 269,          /**< Stop */
        KB_MEDIA_EJECT = 270,         /**< Eject */
        KB_MEDIA_PLAY_PAUSE = 271,    /**< Play / Pause */
        KB_MEDIA_SELECT = 272,        /* Media Select */
        KB_AC_NEW = 273,              /**< AC New */
        KB_AC_OPEN = 274,             /**< AC Open */
        KB_AC_CLOSE = 275,            /**< AC Close */
        KB_AC_EXIT = 276,             /**< AC Exit */
        KB_AC_SAVE = 277,             /**< AC Save */
        KB_AC_PRINT = 278,            /**< AC Print */
        KB_AC_PROPERTIES = 279,       /**< AC Properties */
        KB_AC_SEARCH = 280,           /**< AC Search */
        KB_AC_HOME = 281,             /**< AC Home */
        KB_AC_BACK = 282,             /**< AC Back */
        KB_AC_FORWARD = 283,          /**< AC Forward */
        KB_AC_STOP = 284,             /**< AC Stop */
        KB_AC_REFRESH = 285,          /**< AC Refresh */
        KB_AC_BOOKMARKS = 286,
        KB_SOFTLEFT = 287,
        KB_SOFTRIGHT = 288,
        KB_CALL = 289,
        KB_ENDCALL = 290,
        KB_RESERVED = 400,
        KB_MAX_SIZE = 512 
    };

    enum MouseButtons {
        MB_LEFT = 0,
        MB_CENTER,
        MB_RIGHT,
        MB_MAX_SIZE
    };

    void init();
    void handleEvent(SDL_Event* e);
    void update();
    void release();

    bool isKeyReleased(Keyboard key);
    bool isKeyPressedOnce(Keyboard key);
    bool isKeyPressed(Keyboard key);
    bool isKeyReleasedOnce(Keyboard key);

    float getKeyReleasedValue(Keyboard key);
    float getKeyPressedOnceValue(Keyboard key);
    float getKeyPressedValue(Keyboard key);
    float getKeyReleasedOnceValue(Keyboard key);

    float getKeyReleasedAxis(Keyboard negative, Keyboard positive);
    float getKeyPressedOnceAxis(Keyboard negative, Keyboard positive);
    float getKeyPressedAxis(Keyboard negative, Keyboard positive);
    float getKeyReleasedOnceAxis(Keyboard negative, Keyboard positive);

    glm::vec2 toPosition();
    glm::vec2 toVelocity();

    bool isMouseButtonReleased(MouseButtons mb);
    bool isMouseButtonPressedOnce(MouseButtons mb);
    bool isMouseButtonPressed(MouseButtons mb);
    bool isMouseButtonReleasedOnce(MouseButtons mb);

    float getMouseButtonReleasedValue(MouseButtons mb);
    float getMouseButtonPressedOnceValue(MouseButtons mb);
    float getMouseButtonPressedValue(MouseButtons mb);
    float getMouseButtonReleasedOnceValue(MouseButtons mb);

    float getMouseButtonReleasedAxis(MouseButtons negative, MouseButtons positive);
    float getMouseButtonPressedOnceAxis(MouseButtons negative, MouseButtons positive);
    float getMouseButtonPressedAxis(MouseButtons negative, MouseButtons positive);
    float getMouseButtonReleasedOnceAxis(MouseButtons negative, MouseButtons positive);

    bool isGrab();
    void setGrab(bool grab);
    void toggleGrab();
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

// This is an imgui wrapper
namespace imw {
    void init();
    void handleEvent(SDL_Event* e);
    void release();
    void renderGUI(std::function<void()> cb);
}

#endif