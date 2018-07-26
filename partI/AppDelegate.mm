//
//  AppDelegate.m
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

// -----------------------------------------------------------------------------
#pragma mark - UI

- (void)createMiniMenu {
    self.menu = [[NSMenu alloc] initWithTitle:@"MainMenu"];
    NSApp.mainMenu = self.menu;
    
    NSMenuItem *submenu = [self.menu addItemWithTitle:@"Application" action:nil keyEquivalent:@""];
    NSMenu *menu = [[NSMenu alloc] initWithTitle:@"Application"];
    [self.menu setSubmenu:menu forItem:submenu];

    NSString* title = @"Quit";
    NSMenuItem *item = [menu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];
    item.target = NSApp;
}

// -----------------------------------------------------------------------------

- (void)createWindow:(NSString *)title {
    NSRect contentRect = NSMakeRect(5, 110, 1024, 768);
    NSWindowStyleMask styleMask = NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable|NSWindowStyleMaskResizable;

    self.window = [[NSWindow alloc] initWithContentRect:contentRect styleMask:styleMask backing:NSBackingStoreBuffered defer:true];
    self.window.title = title;
    self.window.delegate = self;

    self.oglView = [[RBNSOpenGLView alloc] initWithFrame:self.window.contentView.bounds];
    [self.window.contentView addSubview:self.oglView];

    [self.window makeKeyAndOrderFront:nil];
}

// -----------------------------------------------------------------------------
#pragma mark - AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [self createWindow:@"OpenGL App"];
    [self createMiniMenu];
}

// -----------------------------------------------------------------------------

- (void)applicationWillTerminate:(NSNotification *)aNotification {}

// -----------------------------------------------------------------------------

@end
