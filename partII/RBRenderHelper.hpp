//
//  RBRenderHelper.hpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>

#include "RBVector2.hpp"

void RBDrawRect(RBVector2 position, RBVector2 size);
void RBDrawRect(float x, float y, float width, float height);
void RBDrawNumber(float x , float y , int n);
