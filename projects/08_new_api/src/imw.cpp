#include "sys.hpp"

namespace imw {
    void init() {
        // ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();
        ImGui_ImplSDL3_InitForOpenGL(app::getWindow(), app::getContext());
        ImGui_ImplOpenGL3_Init("#version 400");
    }

    void handleEvent(SDL_Event* e) {
        ImGui_ImplSDL3_ProcessEvent(e);
    }

    void release() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void renderGUI(std::function<void()> cb) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        cb();
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}