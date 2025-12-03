#import <Foundation/Foundation.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>
#import <CoreGraphics/CoreGraphics.h>

#include "PlatformUtils.h"

#if defined(__APPLE__)
// Minimal macOS 15+ shim: compile-time presence, runtime-safe fallback.
namespace PlatformUtils {
void GetPixelColor_SC(int x, int y, float& r, float& g, float& b) {
    // TODO: Implement full ScreenCaptureKit pipeline. For now, return black to avoid crashes.
    r = g = b = 0.0f;
}
}

#endif
