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
    GLFWwindow* window = glfwCreateWindow(900, 750, "Color Value Finder", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style with a modern, low-saturation gray scheme
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Rounding for a softer look
    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.TabRounding = 6.0f;
    
    // Spacing and padding for better visual balance
    style.WindowPadding = ImVec2(15, 15);
    style.FramePadding = ImVec2(8, 4);
    style.ItemSpacing = ImVec2(10, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.ScrollbarSize = 14.0f;
    style.GrabMinSize = 12.0f;
    
    // Custom color scheme - desaturated gray tone, clearer text
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]            = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_ChildBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_PopupBg]             = ImVec4(0.14f, 0.14f, 0.14f, 0.98f);
    colors[ImGuiCol_Border]              = ImVec4(0.35f, 0.35f, 0.35f, 0.60f);
    colors[ImGuiCol_FrameBg]             = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]      = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgActive]       = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBg]             = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgActive]       = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_MenuBarBg]           = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]         = ImVec4(0.10f, 0.10f, 0.10f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab]       = ImVec4(0.85f, 0.85f, 0.85f, 1.00f); // white-ish
    colors[ImGuiCol_ScrollbarGrabHovered]= ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_CheckMark]           = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]          = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // white handle
    colors[ImGuiCol_SliderGrabActive]    = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Button]              = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_ButtonHovered]       = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_ButtonActive]        = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_Header]              = ImVec4(0.28f, 0.28f, 0.28f, 0.90f);
    colors[ImGuiCol_HeaderHovered]       = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
    colors[ImGuiCol_HeaderActive]        = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_Separator]           = ImVec4(0.32f, 0.32f, 0.32f, 0.70f);
    colors[ImGuiCol_SeparatorHovered]    = ImVec4(0.44f, 0.44f, 0.44f, 0.90f);
    colors[ImGuiCol_SeparatorActive]     = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_ResizeGrip]          = ImVec4(0.70f, 0.70f, 0.70f, 0.50f);
    colors[ImGuiCol_ResizeGripHovered]   = ImVec4(0.85f, 0.85f, 0.85f, 0.70f);
    colors[ImGuiCol_ResizeGripActive]    = ImVec4(0.95f, 0.95f, 0.95f, 0.90f);
    colors[ImGuiCol_Tab]                 = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_TabHovered]          = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_TabActive]           = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    colors[ImGuiCol_Text]                = ImVec4(0.97f, 0.97f, 0.97f, 1.00f); // clearer text
    colors[ImGuiCol_TextDisabled]        = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_PlotLines]           = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]    = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_PlotHistogram]       = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]= ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

    // Improve text clarity: slightly increase global scale (true bold requires a bold font file)
    io.FontGlobalScale = 1.05f;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Application state - initialize from requested color #4CC2CC
    char hexInput[8] = "#4CC2CC";
    RGB currentRGB = ColorConverter::HexToRGB(std::string(hexInput));
    
    float rgbInput[3] = { currentRGB.r * 255.0f, currentRGB.g * 255.0f, currentRGB.b * 255.0f };
    HSV initHSV = ColorConverter::RGBToHSV(currentRGB);
    HSL initHSL = ColorConverter::RGBToHSL(currentRGB);
    CMYK initCMYK = ColorConverter::RGBToCMYK(currentRGB);
    float hsvInput[3] = { initHSV.h, initHSV.s, initHSV.v };
    float hslInput[3] = { initHSL.h, initHSL.s, initHSL.l };
    float cmykInput[4] = { initCMYK.c, initCMYK.m, initCMYK.y, initCMYK.k };

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

        // Create two columns for better layout
        ImGui::Columns(2, "mainColumns", false);
        ImGui::SetColumnWidth(0, 500);

        // Left column - Sliders and inputs
        ImGui::BeginChild("LeftPanel", ImVec2(0, 0), false);

        // Removed preview here; moved below the picker on the right
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // HEX Input
        ImGui::Text("HEX:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150);
        if (ImGui::InputText("##hex", hexInput, sizeof(hexInput), ImGuiInputTextFlags_CharsUppercase)) {
            syncFromHex = true;
        }
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // RGB Sliders
        ImGui::Text("RGB (0-255):");
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("R##rgb", &rgbInput[0], 0.0f, 255.0f, "%.0f")) {
            syncFromRGB = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("G##rgb", &rgbInput[1], 0.0f, 255.0f, "%.0f")) {
            syncFromRGB = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("B##rgb", &rgbInput[2], 0.0f, 255.0f, "%.0f")) {
            syncFromRGB = true;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // HSV Sliders
        ImGui::Text("HSV:");
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("H##hsv", &hsvInput[0], 0.0f, 360.0f, "%.0f°")) {
            syncFromHSV = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("S##hsv", &hsvInput[1], 0.0f, 1.0f, "%.2f")) {
            syncFromHSV = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("V##hsv", &hsvInput[2], 0.0f, 1.0f, "%.2f")) {
            syncFromHSV = true;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // HSL Sliders
        ImGui::Text("HSL:");
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("H##hsl", &hslInput[0], 0.0f, 360.0f, "%.0f°")) {
            syncFromHSL = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("S##hsl", &hslInput[1], 0.0f, 1.0f, "%.2f")) {
            syncFromHSL = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("L##hsl", &hslInput[2], 0.0f, 1.0f, "%.2f")) {
            syncFromHSL = true;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // CMYK Sliders
        ImGui::Text("CMYK (0-100):");
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("C##cmyk", &cmykInput[0], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("M##cmyk", &cmykInput[1], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("Y##cmyk", &cmykInput[2], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderFloat("K##cmyk", &cmykInput[3], 0.0f, 1.0f, "%.2f")) {
            syncFromCMYK = true;
        }

        ImGui::EndChild();

        // Right column - Color Picker
        ImGui::NextColumn();
        
        ImGui::BeginChild("RightPanel", ImVec2(0, 0), false);
        ImGui::Text("Color Picker:");
        ImGui::Spacing();
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
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Text("Color Preview:");
        // Full-width preview with subtle border and shadow
        float previewWidth = ImGui::GetContentRegionAvail().x;
        float previewHeight = 120.0f;
        ImVec2 cursor = ImGui::GetCursorScreenPos();
        ImVec2 pMin = ImVec2(cursor.x, cursor.y);
        ImVec2 pMax = ImVec2(cursor.x + previewWidth, cursor.y + previewHeight);
        ImDrawList* dl = ImGui::GetWindowDrawList();
        float rounding = ImGui::GetStyle().FrameRounding;
        ImU32 colShadow = ImGui::GetColorU32(ImVec4(0, 0, 0, 0.35f));
        ImU32 colBorder = ImGui::GetColorU32(ImVec4(0.28f, 0.32f, 0.45f, 0.8f));
        ImU32 colFill = ImGui::GetColorU32(ImVec4(currentRGB.r, currentRGB.g, currentRGB.b, 1.0f));
        // Shadow (slight offset)
        dl->AddRectFilled(ImVec2(pMin.x + 4, pMin.y + 6), ImVec2(pMax.x + 4, pMax.y + 6), colShadow, rounding);
        // Filled rectangle with border
        dl->AddRectFilled(pMin, pMax, colFill, rounding);
        dl->AddRect(pMin, pMax, colBorder, rounding, 0.0f, 2.0f);
        // Reserve layout space
        ImGui::InvisibleButton("##preview_swatch", ImVec2(previewWidth, previewHeight));
        ImGui::EndChild();

        ImGui::Columns(1);

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
        glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
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
