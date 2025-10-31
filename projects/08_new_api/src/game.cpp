#include "game.hpp"
#include "sys.hpp"


namespace game {

    render::VertexBuffer vertices;
    render::VertexBuffer texCoords;
    render::IndexBuffer indencies;

    void renderGUI(std::function<void()> callback);

    float yrot = 0.0f;


    bool rotateX = false;
    bool rotateY = true;
    bool rotateZ = false;
    glm::vec4 color = glm::vec4(glm::vec3(100.0f, 149.0f, 237.0f) / 255.0f, 1.0f);


    void init() {
        // ImGui
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForOpenGL(app::getWindow(), app::getContext());
        ImGui_ImplOpenGL3_Init("#version 400");

        // Initialize Buffer + Textures
        // Vertices
        vertices.init();
        vertices.clear();
        vertices.add3(-1.0f, 1.0f, 0.0f);
        vertices.add3(1.0f, 1.0f, 0.0f);
        vertices.add3(-1.0f, -1.0f, 0.0f);
        vertices.add3(1.0f, -1.0f, 0.0f);
        vertices.update();
        // TexCoords
        texCoords.init();
        texCoords.clear();
        texCoords.add2(0.0f, 0.0f);
        texCoords.add2(1.0f, 0.0f);
        texCoords.add2(0.0f, 1.0f);
        texCoords.add2(1.0f, 1.0f);
        texCoords.update();
        // Indencies
        indencies.init();
        indencies.clear();
        indencies.add3(0, 1, 2);
        indencies.add3(2, 1, 3);
        indencies.update();
        render::addTexture("happy", "happyface.png");
    }

    void handleEvent(SDL_Event* e) {
        ImGui_ImplSDL3_ProcessEvent(e);
    }

    void update(float delta) {
        yrot += 64.0f * delta;

        if(yrot > 360.0f) {
            yrot -= 360.0f;
        }
    }

    void render() {
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), app::getAspect(), 1.0f, 1024.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model =
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(yrot), glm::vec3((rotateX) ? 1.0f : 0.0f, (rotateY) ? 1.0f : 0.0f, (rotateZ) ? 1.0f : 0.0f));

        
        render::clear(color);

        render::getMainShader()->bind();

        render::getMainShader()->setProjection(proj);
        render::getMainShader()->setView(view);
        render::getMainShader()->setModel(model);

        render::bindTexture("happy", GL_TEXTURE0);
        render::getMainShader()->draw(
            vertices,
            texCoords,
            indencies
        );
        render::unbindTextre(GL_TEXTURE0);

        render::getMainShader()->unbind();

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

    void release() {
        indencies.release();
        texCoords.release();
        vertices.release();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void setup(app::Config* config) {
        config->caption = "08_new_api";
        config->width = 1280;
        config->height = 720;

        config->initCB = init;
        config->handleEventCB = handleEvent;
        config->updateCB = update;
        config->renderCB = render;
        config->releaseCB = release;
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

}