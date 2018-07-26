//
//  AppDelegate.h
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RBNSOpenGLView.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property (strong, nonatomic) NSWindow* window;
@property (strong, nonatomic) RBNSOpenGLView* oglView;
@property (strong, nonatomic) NSMenu* menu;

@end

