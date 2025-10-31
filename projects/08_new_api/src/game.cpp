#include "game.hpp"
#include "glm/ext/quaternion_geometric.hpp"
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
    
    int i = 0;

    void init() {
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

        imw::renderGUI([&]() {

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
}