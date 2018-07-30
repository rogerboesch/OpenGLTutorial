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

extern Game* gGame;

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

- (void)keyDown:(NSEvent *)event {
    NSLog(@"Key down: %d", event.keyCode);
}

// -----------------------------------------------------------------------------

- (void)keyUp:(NSEvent *)event {
    NSLog(@"Key up: %d", event.keyCode);
}

// -----------------------------------------------------------------------------
#pragma mark - Render loop

- (void)renderLoop {
    // Update game
    gGame->OnUpdate();

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

