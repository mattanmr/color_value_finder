#include "PlatformUtils.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

namespace PlatformUtils {
    void GetCursorPosition(int& x, int& y) {
        POINT pt;
        ::GetCursorPos(&pt);
        x = pt.x;
        y = pt.y;
    }
    
    void GetPixelColor(int x, int y, float& r, float& g, float& b) {
        HDC hdc = GetDC(NULL);
        if (hdc) {
            COLORREF c = GetPixel(hdc, x, y);
            ReleaseDC(NULL, hdc);
            r = ((c) & 0xFF) / 255.0f;
            g = ((c >> 8) & 0xFF) / 255.0f;
            b = ((c >> 16) & 0xFF) / 255.0f;
        } else {
            r = g = b = 0.0f;
        }
    }
    
    bool IsLeftMouseButtonPressed() {
        return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    }
    
    bool IsEscapeKeyPressed() {
        return (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
    }
}

#elif defined(__APPLE__)
// macOS: Eyedropper feature not yet implemented
namespace PlatformUtils {
    void GetCursorPosition(int& x, int& y) {
        x = y = 0;
    }
    
    void GetPixelColor(int x, int y, float& r, float& g, float& b) {
        r = g = b = 0.0f;
    }
    
    bool IsLeftMouseButtonPressed() {
        return false;
    }
    
    bool IsEscapeKeyPressed() {
        return false;
    }
}

#else
// Fallback for unsupported platforms
namespace PlatformUtils {
    void GetCursorPosition(int& x, int& y) {
        x = y = 0;
    }
    
    void GetPixelColor(int x, int y, float& r, float& g, float& b) {
        r = g = b = 0.0f;
    }
    
    bool IsLeftMouseButtonPressed() {
        return false;
    }
    
    bool IsEscapeKeyPressed() {
        return false;
    }
}
#endif
