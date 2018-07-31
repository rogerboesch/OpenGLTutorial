//
//  RBNSOpenGLView.mm
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#import "RBNSOpenGLView.h"
#include "Game.hpp"

#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#include <mach/mach_time.h>

extern Game* gGame;

uint32_t lastTime = 0;

uint32_t getTimeMS() {
    const int64_t kOneMillion = 1000 * 1000;
    static mach_timebase_info_data_t s_timebase_info;
    
    if (s_timebase_info.denom == 0) {
        (void) mach_timebase_info(&s_timebase_info);
    }
    
    return (uint32_t)((mach_absolute_time() * s_timebase_info.numer) / (kOneMillion * s_timebase_info.denom));
}

@implementation RBNSOpenGLView

// -----------------------------------------------------------------------------
#pragma mark - Keyboard support

- (BOOL)acceptsFirstResponder {
    return YES;
}

// -----------------------------------------------------------------------------

- (BOOL)becomeFirstResponder {
    return YES;
}

// -----------------------------------------------------------------------------

- (BOOL)resignFirstResponder {
    return YES;
}

// -----------------------------------------------------------------------------

- (void)handleKey:(int)code pressed:(BOOL)pressed {
    switch (code) {
        case 123:
            gGame->OnKey(keyLeft, pressed);
            break;
        case 124:
            gGame->OnKey(keyRight, pressed);
            break;
        case 125:
            gGame->OnKey(keyDown, pressed);
            break;
        case 126:
            gGame->OnKey(keyUp, pressed);
            break;
        case 13:
            gGame->OnKey(keyW, pressed);
            break;
        case 0:
            gGame->OnKey(keyA, pressed);
            break;
        case 1:
            gGame->OnKey(keyS, pressed);
            break;
        case 2:
            gGame->OnKey(keyD, pressed);
            break;
    }
}

// -----------------------------------------------------------------------------

- (void)keyDown:(NSEvent *)event {
    NSLog(@"Key down: %d", event.keyCode);
    
    [self handleKey: event.keyCode pressed: true];
}

// -----------------------------------------------------------------------------

- (void)keyUp:(NSEvent *)event {
    NSLog(@"Key up: %d", event.keyCode);

    [self handleKey: event.keyCode pressed: false];
}

// -----------------------------------------------------------------------------
#pragma mark - Render loop

- (void)renderLoop {
    uint32_t time = getTimeMS();
    if (lastTime == 0) {
        lastTime = time;
    }
    
    float delay = (time-lastTime) / 1000.0;
    
    lastTime = getTimeMS();
    
    // Update game
    gGame->OnUpdate(delay);

    // Render game
    gGame->OnRender();
    
    // Flush all to context
    CGLContextObj ctx = 0;
    CGLFlushDrawable(ctx);
    glFlush();
    
    [self performSelector:@selector(renderLoop) withObject:nil afterDelay:1.0/kFRAMES_PER_SECOND];
}

// -----------------------------------------------------------------------------
#pragma mark - Initialisation

- (id)initWithFrame:(NSRect)frame {
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
        NSOpenGLProfileVersionLegacy,   // Important to work with current shader implementation
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    self = [super initWithFrame:frame pixelFormat:pixelFormat];
    
    [[self openGLContext] makeCurrentContext];
    
    // Initialising stuff
    int width = [self bounds].size.width;
    int height = [self bounds].size.height;

    gGame->OnInit(width, height);
    
    [self performSelector:@selector(renderLoop) withObject:nil afterDelay:1.0/kFRAMES_PER_SECOND];

    return self;
}

// -----------------------------------------------------------------------------

@end

