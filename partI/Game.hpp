//
//  Game.hpp
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>

#define kFRAMES_PER_SECOND 60

class Game
{
public:
    Game();

    void onInit();
    void onUpdate();
    void onRender();
};

