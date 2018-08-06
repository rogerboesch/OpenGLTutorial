//
//  EAGLView.h
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@interface EAGLView : UIView {
    
@private
    GLint backingWidth;
    GLint backingHeight;
    EAGLContext *context;
    GLuint viewRenderbuffer, viewFramebuffer;
    GLuint depthRenderbuffer;
    
    NSTimeInterval renderInterval;
}

- (void)start;
- (void)stop;

@end
