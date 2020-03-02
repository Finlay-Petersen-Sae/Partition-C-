// ImGui - standalone example application for Glfw + OpenGL 2, using fixed pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "TiledWorldGenerator.h"
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

auto lastElapsedTime = 0LL;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    TiledWorldGenerator worldGen;

    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Tiled World Generator", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);

    ImVec4 clear_color = ImColor(114, 144, 154);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();

        // Draw the setup window (not-resizable or movable, ignores ini settings)
        ImGuiWindowFlags setupWindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
        ImGui::SetNextWindowSize(ImVec2(300,720), ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Setup", nullptr, setupWindowFlags);

        // world configuration block
        if (ImGui::CollapsingHeader("World Configuration", ImGuiTreeNodeFlags_DefaultOpen))
        {
            // Draw the world configuration section
            ImGui::SliderInt("Length", &worldGen.Length, 1, 60);
            ImGui::SliderInt("Width", &worldGen.Width, 1, 60);
        }

        // tile configuration block
        if (ImGui::CollapsingHeader("Tile Configuration", ImGuiTreeNodeFlags_DefaultOpen))
        {
            for(AvailableTile* tile : worldGen.TilePalette)
            {
                if (ImGui::TreeNode(tile->Name.c_str()))
                {
                    ImVec4 tileColour = tile->Colour;
                    ImGui::ColorEdit3("Colour", (float*)&tileColour);
                    tile->Colour = ImColor(tileColour);
                    ImGui::SliderInt("Frequency", &(tile->Frequency), 1, 1000);
                    ImGui::SliderFloat("Strength", &(tile->FieldStrength), 0, 50.0f);
                    ImGui::SliderFloat("Range", &(tile->FieldRange), -1000.0f, 1000.0f);
                    ImGui::TreePop();
                }
            }
        }

        // Check if we need to run the generation the world
        if (ImGui::Button("Generate"))
        {
            // generate the world
            worldGen.Generate();
        }

        if (ImGui::Button("Rebuild Field"))
        {
            // grab the start time
            high_resolution_clock::time_point startTime = high_resolution_clock::now();

            worldGen.CalculateField();
            
            // grab the end time
            high_resolution_clock::time_point endTime = high_resolution_clock::now();

            // update the last elapsed time
            lastElapsedTime = duration_cast<microseconds>(endTime - startTime).count();
        }

        ImGui::Checkbox("Show field", &(worldGen.ShowField));

        ImGui::Text("Time: %lld microseconds", lastElapsedTime);
        
        ImGui::End();

        // Draw the level window
        ImGui::SetNextWindowSize(ImVec2(1280-300,720), ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(300, 0));
        ImGui::Begin("Level", nullptr, setupWindowFlags);

        worldGen.DrawWorld();
            
        ImGui::End();

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();

    return 0;
}
