#import <Foundation/Foundation.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>
#import <CoreGraphics/CoreGraphics.h>

#include "PlatformUtils.h"

#if defined(__APPLE__)
// Objective-C++ helper capturing the screen using ScreenCaptureKit and sampling a pixel.
// Minimal implementation: starts a stream for the main display and keeps the latest frame buffer.

@interface CVFFrameCollector : NSObject<SCStreamOutput>
@property(nonatomic, strong) SCStream *stream;
@property(nonatomic, strong) SCStreamConfiguration *config;
@property(nonatomic, strong) SCDisplay *display;
@property(atomic) CGRect frameRect; // current frame rect
@property(atomic) std::vector<uint8_t> lastBytes;
@end

@implementation CVFFrameCollector
- (instancetype)initWithDisplay:(SCDisplay *)display {
    if ((self = [super init])) {
        _display = display;
        _config = [SCStreamConfiguration new];
        _config.pixelFormat = kCVPixelFormatType_32BGRA;
        _config.showsCursor = YES;
        _config.minimumFrameInterval = CMTimeMake(1, 30);
        _config.colorSpaceName = kCGColorSpaceSRGB;
        _config.width = (int)display.frame.size.width;
        _config.height = (int)display.frame.size.height;
        _frameRect = CGRectMake(0, 0, _config.width, _config.height);
    }
    return self;
}

- (BOOL)start:(NSError **)error {
    SCShareableContent *content = [SCShareableContent currentShareableContent:error];
    if (!content) return NO;
    // Pick the main display (matching provided display id)
    SCDisplay *target = nil;
    for (SCDisplay *d in content.displays) {
        if (d.displayID == _display.displayID) { target = d; break; }
    }
    if (!target) target = content.displays.firstObject;
    if (!target) return NO;

    _stream = [[SCStream alloc] initWithFilter:[SCContentFilter filterWithDisplay:target excludingWindows:@[]] configuration:_config delegate:self];
    return [_stream startCapture:error];
}

- (void)stop {
    [_stream stopCapture:nil];
}

- (void)stream:(SCStream *)stream didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer ofType:(SCStreamOutputType)type {
    if (type != SCStreamOutputTypeScreen) return;
    CVImageBufferRef img = CMSampleBufferGetImageBuffer(sampleBuffer);
    if (!img) return;
    CVPixelBufferLockBaseAddress(img, kCVPixelBufferLock_ReadOnly);
    void *base = CVPixelBufferGetBaseAddress(img);
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(img);
    size_t width = CVPixelBufferGetWidth(img);
    size_t height = CVPixelBufferGetHeight(img);
    size_t total = bytesPerRow * height;
    if (base && total) {
        @autoreleasepool {
            try {
                lastBytes.resize(total);
                memcpy(lastBytes.data(), base, total);
            } catch (...) {}
        }
    }
    CVPixelBufferUnlockBaseAddress(img, kCVPixelBufferLock_ReadOnly);
}
@end

static CVFFrameCollector *gCollector = nil;
static bool ensureCollectorStarted() {
    if (gCollector) return true;
    NSError *err = nil;
    SCShareableContent *content = [SCShareableContent currentShareableContent:&err];
    if (!content || content.displays.count == 0) return false;
    gCollector = [[CVFFrameCollector alloc] initWithDisplay:content.displays.firstObject];
    return [gCollector start:&err];
}

// Implement namespaced symbol to be linked from C++
namespace PlatformUtils {
void GetPixelColor_SC(int x, int y, float& r, float& g, float& b) {
        // Use ScreenCaptureKit frame buffer when available
        if (!ensureCollectorStarted() || !gCollector) {
            r = g = b = 0.0f;
            return;
        }
        // ScreenCaptureKit delivers frames in display coordinates; sample BGRA at (x,y)
        const std::vector<uint8_t> &buf = gCollector.lastBytes;
        if (buf.empty()) { r = g = b = 0.0f; return; }
        // Clamp coordinates
        int width = (int)gCollector.config.width;
        int height = (int)gCollector.config.height;
        if (x < 0) x = 0; if (y < 0) y = 0;
        if (x >= width) x = width - 1;
        if (y >= height) y = height - 1;
        size_t bytesPerRow = (size_t)gCollector.config.width * 4; // BGRA
        size_t idx = (size_t)y * bytesPerRow + (size_t)x * 4;
        if (idx + 3 < buf.size()) {
            b = buf[idx + 0] / 255.0f;
            g = buf[idx + 1] / 255.0f;
            r = buf[idx + 2] / 255.0f;
        } else {
            r = g = b = 0.0f;
        }
}

#endif
