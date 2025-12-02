#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ColorConverter.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.3 + GLSL 330
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 700, "Color Value Finder", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Application state
    RGB currentRGB(0.5f, 0.3f, 0.8f);
    char hexInput[8] = "#8D4DCC";
    
    float rgbInput[3] = {141.0f, 77.0f, 204.0f};
    float hsvInput[3] = {270.0f, 0.62f, 0.80f};
    float hslInput[3] = {270.0f, 0.54f, 0.55f};
    float cmykInput[4] = {0.31f, 0.62f, 0.0f, 0.20f};

    bool syncFromRGB = false;
    bool syncFromHex = false;
    bool syncFromHSV = false;
    bool syncFromHSL = false;
    bool syncFromCMYK = false;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main window
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Color Value Finder", nullptr, 
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

        ImGui::Text("Color Value Finder");
        ImGui::Separator();
        ImGui::Spacing();

        // Color preview
        ImGui::Text("Color Preview:");
        ImGui::ColorButton("##preview", ImVec4(currentRGB.r, currentRGB.g, currentRGB.b, 1.0f), 
            ImGuiColorEditFlags_NoAlpha, ImVec2(200, 100));
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // HEX Input
        ImGui::Text("HEX:");
        ImGui::SameLine();
        if (ImGui::InputText("##hex", hexInput, sizeof(hexInput), ImGuiInputTextFlags_CharsUppercase)) {
            syncFromHex = true;
        }
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // RGB Sliders
        ImGui::Text("RGB (0-255):");
        if (ImGui::SliderFloat("R##rgb", &rgbInput[0], 0.0f, 255.0f, "%.0f")) {
            syncFromRGB = true;
        }
        if (ImGui::SliderFloat("G##rgb", &rgbInput[1], 0.0f, 255.0f, "%.0f")) {
            syncFromRGB = true;
        }
        if (ImGui::SliderFloat("B##rgb", &rgbInput[2], 0.0f, 255.0f, "%.0f")) {
            syncFromRGB = true;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // HSV Sliders
        ImGui::Text("HSV:");
        if (ImGui::SliderFloat("H##hsv", &hsvInput[0], 0.0f, 360.0f, "%.0f°")) {
            syncFromHSV = true;
        }
        if (ImGui::SliderFloat("S##hsv", &hsvInput[1], 0.0f, 1.0f, "%.2f")) {
            syncFromHSV = true;
        }
        if (ImGui::SliderFloat("V##hsv", &hsvInput[2], 0.0f, 1.0f, "%.2f")) {
            syncFromHSV = true;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // HSL Sliders
        ImGui::Text("HSL:");
        if (ImGui::SliderFloat("H##hsl", &hslInput[0], 0.0f, 360.0f, "%.0f°")) {
            syncFromHSL = true;
        }
        if (ImGui::SliderFloat("S##hsl", &hslInput[1], 0.0f, 1.0f, "%.2f")) {
            syncFromHSL = true;
        }
        if (ImGui::SliderFloat("L##hsl", &hslInput[2], 0.0f, 1.0f, "%.2f")) {
            syncFromHSL = true;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // CMYK Sliders
        ImGui::Text("CMYK (0-100):");
        if (ImGui::SliderFloat("C##cmyk", &cmykInput[0], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }
        if (ImGui::SliderFloat("M##cmyk", &cmykInput[1], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }
        if (ImGui::SliderFloat("Y##cmyk", &cmykInput[2], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }
        if (ImGui::SliderFloat("K##cmyk", &cmykInput[3], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Color Picker
        ImGui::Text("Color Picker:");
        float pickerColor[3] = {currentRGB.r, currentRGB.g, currentRGB.b};
        if (ImGui::ColorPicker3("##picker", pickerColor, 
            ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoAlpha | 
            ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV)) {
            currentRGB.r = pickerColor[0];
            currentRGB.g = pickerColor[1];
            currentRGB.b = pickerColor[2];
            syncFromRGB = true;
            rgbInput[0] = currentRGB.r * 255.0f;
            rgbInput[1] = currentRGB.g * 255.0f;
            rgbInput[2] = currentRGB.b * 255.0f;
        }

        // Synchronization logic
        if (syncFromHex) {
            currentRGB = ColorConverter::HexToRGB(std::string(hexInput));
            rgbInput[0] = currentRGB.r * 255.0f;
            rgbInput[1] = currentRGB.g * 255.0f;
            rgbInput[2] = currentRGB.b * 255.0f;
            
            HSV hsv = ColorConverter::RGBToHSV(currentRGB);
            hsvInput[0] = hsv.h;
            hsvInput[1] = hsv.s;
            hsvInput[2] = hsv.v;
            
            HSL hsl = ColorConverter::RGBToHSL(currentRGB);
            hslInput[0] = hsl.h;
            hslInput[1] = hsl.s;
            hslInput[2] = hsl.l;
            
            CMYK cmyk = ColorConverter::RGBToCMYK(currentRGB);
            cmykInput[0] = cmyk.c;
            cmykInput[1] = cmyk.m;
            cmykInput[2] = cmyk.y;
            cmykInput[3] = cmyk.k;
            
            syncFromHex = false;
        }
        
        if (syncFromRGB) {
            currentRGB.r = rgbInput[0] / 255.0f;
            currentRGB.g = rgbInput[1] / 255.0f;
            currentRGB.b = rgbInput[2] / 255.0f;
            
            std::string hex = ColorConverter::RGBToHex(currentRGB);
            strncpy(hexInput, hex.c_str(), sizeof(hexInput) - 1);
            hexInput[sizeof(hexInput) - 1] = '\0';
            
            HSV hsv = ColorConverter::RGBToHSV(currentRGB);
            hsvInput[0] = hsv.h;
            hsvInput[1] = hsv.s;
            hsvInput[2] = hsv.v;
            
            HSL hsl = ColorConverter::RGBToHSL(currentRGB);
            hslInput[0] = hsl.h;
            hslInput[1] = hsl.s;
            hslInput[2] = hsl.l;
            
            CMYK cmyk = ColorConverter::RGBToCMYK(currentRGB);
            cmykInput[0] = cmyk.c;
            cmykInput[1] = cmyk.m;
            cmykInput[2] = cmyk.y;
            cmykInput[3] = cmyk.k;
            
            syncFromRGB = false;
        }
        
        if (syncFromHSV) {
            HSV hsv(hsvInput[0], hsvInput[1], hsvInput[2]);
            currentRGB = ColorConverter::HSVToRGB(hsv);
            
            rgbInput[0] = currentRGB.r * 255.0f;
            rgbInput[1] = currentRGB.g * 255.0f;
            rgbInput[2] = currentRGB.b * 255.0f;
            
            std::string hex = ColorConverter::RGBToHex(currentRGB);
            strncpy(hexInput, hex.c_str(), sizeof(hexInput) - 1);
            hexInput[sizeof(hexInput) - 1] = '\0';
            
            HSL hsl = ColorConverter::RGBToHSL(currentRGB);
            hslInput[0] = hsl.h;
            hslInput[1] = hsl.s;
            hslInput[2] = hsl.l;
            
            CMYK cmyk = ColorConverter::RGBToCMYK(currentRGB);
            cmykInput[0] = cmyk.c;
            cmykInput[1] = cmyk.m;
            cmykInput[2] = cmyk.y;
            cmykInput[3] = cmyk.k;
            
            syncFromHSV = false;
        }
        
        if (syncFromHSL) {
            HSL hsl(hslInput[0], hslInput[1], hslInput[2]);
            currentRGB = ColorConverter::HSLToRGB(hsl);
            
            rgbInput[0] = currentRGB.r * 255.0f;
            rgbInput[1] = currentRGB.g * 255.0f;
            rgbInput[2] = currentRGB.b * 255.0f;
            
            std::string hex = ColorConverter::RGBToHex(currentRGB);
            strncpy(hexInput, hex.c_str(), sizeof(hexInput) - 1);
            hexInput[sizeof(hexInput) - 1] = '\0';
            
            HSV hsv = ColorConverter::RGBToHSV(currentRGB);
            hsvInput[0] = hsv.h;
            hsvInput[1] = hsv.s;
            hsvInput[2] = hsv.v;
            
            CMYK cmyk = ColorConverter::RGBToCMYK(currentRGB);
            cmykInput[0] = cmyk.c;
            cmykInput[1] = cmyk.m;
            cmykInput[2] = cmyk.y;
            cmykInput[3] = cmyk.k;
            
            syncFromHSL = false;
        }
        
        if (syncFromCMYK) {
            CMYK cmyk(cmykInput[0], cmykInput[1], cmykInput[2], cmykInput[3]);
            currentRGB = ColorConverter::CMYKToRGB(cmyk);
            
            rgbInput[0] = currentRGB.r * 255.0f;
            rgbInput[1] = currentRGB.g * 255.0f;
            rgbInput[2] = currentRGB.b * 255.0f;
            
            std::string hex = ColorConverter::RGBToHex(currentRGB);
            strncpy(hexInput, hex.c_str(), sizeof(hexInput) - 1);
            hexInput[sizeof(hexInput) - 1] = '\0';
            
            HSV hsv = ColorConverter::RGBToHSV(currentRGB);
            hsvInput[0] = hsv.h;
            hsvInput[1] = hsv.s;
            hsvInput[2] = hsv.v;
            
            HSL hsl = ColorConverter::RGBToHSL(currentRGB);
            hslInput[0] = hsl.h;
            hslInput[1] = hsl.s;
            hslInput[2] = hsl.l;
            
            syncFromCMYK = false;
        }

        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
