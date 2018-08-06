//
//  TouchView.mm
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#import "TouchView.h"
#include "Game.hpp"

extern Game* gGame;

@interface TouchView ()
@property (nonatomic) BOOL pressUp;
@end

@implementation TouchView

// -----------------------------------------------------------------------------

#pragma mark - Multitouch handling

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch* touch = [[event touchesForView:self] anyObject];
    CGPoint touchAt = [touch locationInView:self];

    if (touchAt.y <= [[UIScreen mainScreen] bounds].size.height/2) {
        NSLog(@"Touch up %d", self.number);
        self.pressUp = true;
        gGame->OnKey(self.pressUpCode, true);
    }
    else {
        NSLog(@"Touch down %d", self.number);
        self.pressUp = false;
        gGame->OnKey(self.pressDownCode, true);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event {
    NSLog(@"Touch release %d", self.number);
    
    if (self.pressUp) {
        gGame->OnKey(self.pressUpCode, false);
    }
    else {
        gGame->OnKey(self.pressDownCode, false);
    }
}

@end
