#import <Foundation/Foundation.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CoreVideo.h>

#include <atomic>
#include <mutex>
#include <vector>

#include "PlatformUtils.h"

#if defined(__APPLE__)

// Objective-C++ collector for ScreenCaptureKit frames
@interface CVFFrameCollector : NSObject <SCStreamOutput>
@property(nonatomic, strong) SCStream *stream;
@property(nonatomic, strong) SCStreamConfiguration *config;
@property(nonatomic, strong) SCDisplay *display;
@property(nonatomic, strong) SCContentFilter *filter;
@property(nonatomic, assign) int width;
@property(nonatomic, assign) int height;
@end

// File-scope globals for buffer caching
static std::vector<uint8_t> gBuffer;
static std::mutex gBufferMutex;
static size_t gBytesPerRow = 0;

@implementation CVFFrameCollector

- (instancetype)initWithDisplay:(SCDisplay *)display {
    if ((self = [super init])) {
        _display = display;
        _config = [SCStreamConfiguration new];
        _config.pixelFormat = kCVPixelFormatType_32BGRA;
        _config.showsCursor = YES;
        _config.minimumFrameInterval = CMTimeMake(1, 60);
        _config.colorSpaceName = kCGColorSpaceSRGB;
        _width = (int)display.frame.size.width;
        _height = (int)display.frame.size.height;
        _config.width = _width;
        _config.height = _height;
        _filter = [[SCContentFilter alloc] initWithDisplay:display excludingWindows:@[]];
        _stream = [[SCStream alloc] initWithFilter:_filter configuration:_config delegate:nil];
    }
    return self;
}

- (BOOL)start:(NSError **)error {
    dispatch_queue_t q = dispatch_queue_create("cvf.scstream.queue", DISPATCH_QUEUE_SERIAL);
    BOOL ok = [_stream addStreamOutput:self type:SCStreamOutputTypeScreen sampleHandlerQueue:q error:error];
    if (!ok) return NO;
    __block BOOL started = NO;
    __block BOOL done = NO;
    [_stream startCaptureWithCompletionHandler:^(NSError * _Nullable err){
        started = (err == nil);
        done = YES;
    }];
    // Wait briefly for start
    const int maxWaitMs = 500;
    int waited = 0;
    while (!done && waited < maxWaitMs) { usleep(1000*10); waited += 10; }
    return started;
}

- (void)stop {
    [_stream stopCaptureWithCompletionHandler:^(NSError * _Nullable error){}];
}

- (void)stream:(SCStream *)stream didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer ofType:(SCStreamOutputType)type {
    if (type != SCStreamOutputTypeScreen) return;
    CVImageBufferRef img = CMSampleBufferGetImageBuffer(sampleBuffer);
    if (!img) return;
    CVPixelBufferLockBaseAddress(img, kCVPixelBufferLock_ReadOnly);
    void *base = CVPixelBufferGetBaseAddress(img);
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(img);
    size_t height = CVPixelBufferGetHeight(img);
    size_t total = bytesPerRow * height;
    if (base && total) {
        std::lock_guard<std::mutex> lock(gBufferMutex);
        gBuffer.resize(total);
        memcpy(gBuffer.data(), base, total);
        gBytesPerRow = bytesPerRow;
    }
    CVPixelBufferUnlockBaseAddress(img, kCVPixelBufferLock_ReadOnly);
}

@end

static CVFFrameCollector *gCollector = nil;
static std::once_flag gInitOnce;

static bool ensureCollector() {
    __block bool ok = false;
    std::call_once(gInitOnce, ^{
        __block NSError *err = nil;
        __block SCShareableContent *content = nil;
        dispatch_semaphore_t sem = dispatch_semaphore_create(0);
        [SCShareableContent getShareableContentWithCompletionHandler:^(SCShareableContent * _Nullable c, NSError * _Nullable e){
            content = c; err = e; dispatch_semaphore_signal(sem);
        }];
        // Wait up to 1s
        dispatch_time_t timeout = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC));
        dispatch_semaphore_wait(sem, timeout);
        if (!content || content.displays.count == 0) { gCollector = nil; return; }
        SCDisplay *disp = content.displays.firstObject;
        gCollector = [[CVFFrameCollector alloc] initWithDisplay:disp];
        ok = [gCollector start:&err];
        if (!ok) gCollector = nil;
    });
    return gCollector != nil;
}

namespace PlatformUtils {
void GetPixelColor_SC(int x, int y, float& r, float& g, float& b) {
    if (!ensureCollector() || !gCollector) { r = g = b = 0.0f; return; }
    int width = gCollector.width;
    int height = gCollector.height;
    if (x < 0) x = 0; if (y < 0) y = 0;
    if (x >= width) x = width - 1;
    if (y >= height) y = height - 1;
    std::lock_guard<std::mutex> lock(gBufferMutex);
    if (gBuffer.empty() || gBytesPerRow == 0) { r = g = b = 0.0f; return; }
    size_t idx = (size_t)y * gBytesPerRow + (size_t)x * 4;
    if (idx + 3 < gBuffer.size()) {
        b = gBuffer[idx + 0] / 255.0f;
        g = gBuffer[idx + 1] / 255.0f;
        r = gBuffer[idx + 2] / 255.0f;
    } else {
        r = g = b = 0.0f;
    }
}
}

#endif
