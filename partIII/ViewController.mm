//
//  ViewController.m
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "ViewController.h"
#include "EAGLView.h"
#include "TouchView.h"
#include "Game.hpp"

@interface ViewController() {
}

@property (strong, nonatomic) EAGLView *glView;
@property (strong, nonatomic) TouchView *leftTouchView;
@property (strong, nonatomic) TouchView *rightTouchView;

@end

@implementation ViewController

@synthesize glView = _glView;

// -----------------------------------------------------------------------------
#pragma mark - Construction / Destruction

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
}   

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];

    [self.glView start];
}

// -----------------------------------------------------------------------------

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.autoresizesSubviews = YES;
    self.view.backgroundColor = UIColor.redColor;
    
    self.glView = [[EAGLView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.glView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview: self.glView];
    
    CGRect rect = [[UIScreen mainScreen] bounds];
    rect.size.width = rect.size.width/2;
    self.leftTouchView = [[TouchView alloc] initWithFrame:rect];
    self.leftTouchView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview: self.leftTouchView];
    
    rect.origin.x += rect.size.width;
    self.rightTouchView = [[TouchView alloc] initWithFrame:rect];
    self.rightTouchView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview: self.rightTouchView];
    
    self.leftTouchView.number = 1;
    self.leftTouchView.pressUpCode = keyW;
    self.leftTouchView.pressDownCode = keyS;

    self.rightTouchView.number = 2;
    self.rightTouchView.pressUpCode = keyUp;
    self.rightTouchView.pressDownCode = keyDown;
}

// -----------------------------------------------------------------------------

@end

