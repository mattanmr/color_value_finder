#pragma once

namespace PlatformUtils {
    // Get current cursor position in screen coordinates
    void GetCursorPosition(int& x, int& y);
    
    // Sample pixel color at screen coordinates (x, y)
    // Returns RGB values in range [0.0, 1.0]
    void GetPixelColor(int x, int y, float& r, float& g, float& b);
    
    // Check if left mouse button is currently pressed
    bool IsLeftMouseButtonPressed();
    
    // Check if Escape key is currently pressed
    bool IsEscapeKeyPressed();
}
