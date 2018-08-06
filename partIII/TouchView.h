//
//  TouchView.h
//
//  Created by Roger Boesch on 11.03.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#import <UIKit/UIKit.h>
#import "Game.hpp"

@interface TouchView : UIView {
}

@property (nonatomic) int number;
@property (nonatomic) KeyType pressUpCode;
@property (nonatomic) KeyType pressDownCode;

@end
