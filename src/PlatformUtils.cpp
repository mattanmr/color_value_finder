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
#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>

namespace PlatformUtils {
    void GetCursorPosition(int& x, int& y) {
        CGEventRef event = CGEventCreate(NULL);
        CGPoint cursor = CGEventGetLocation(event);
        CFRelease(event);
        x = static_cast<int>(cursor.x);
        y = static_cast<int>(cursor.y);
    }
    
    void GetPixelColor(int x, int y, float& r, float& g, float& b) {
        // Create a 1x1 pixel image at the cursor location
        CGImageRef image = CGDisplayCreateImageForRect(CGMainDisplayID(), CGRectMake(x, y, 1, 1));
        
        if (image) {
            // Get pixel data
            CFDataRef data = CGDataProviderCopyData(CGImageGetDataProvider(image));
            const uint8_t* pixels = CFDataGetBytePtr(data);
            
            // macOS typically uses BGRA or RGBA format
            // Check bytes per pixel to determine format
            size_t bitsPerPixel = CGImageGetBitsPerPixel(image);
            size_t bytesPerPixel = bitsPerPixel / 8;
            
            if (bytesPerPixel >= 3) {
                // Assume BGRA or RGBA - most common on macOS
                r = pixels[0] / 255.0f;
                g = pixels[1] / 255.0f;
                b = pixels[2] / 255.0f;
            } else {
                r = g = b = 0.0f;
            }
            
            CFRelease(data);
            CGImageRelease(image);
        } else {
            r = g = b = 0.0f;
        }
    }
    
    bool IsLeftMouseButtonPressed() {
        return CGEventSourceButtonState(kCGEventSourceStateHIDSystemState, kCGMouseButtonLeft);
    }
    
    bool IsEscapeKeyPressed() {
        // Check for Escape key (keycode 53 on macOS)
        return CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, 53);
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
