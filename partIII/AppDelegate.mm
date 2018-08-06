//
//  AppDelegate.m
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//
//  Based on code done by tjgrant@tatewake.com
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

@synthesize window = mWindow;
@synthesize viewController = mViewController;

// -----------------------------------------------------------------------------

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.viewController = [[ViewController alloc] initWithNibName:nil bundle:nil];
    
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;

}

// -----------------------------------------------------------------------------

@end
