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

#include <string>
#include "RBVector2.hpp"
#include "RBColor.hpp"

void RBDrawRect(RBVector2 position, RBVector2 size, RBColor color);
void RBDrawRect(float x, float y, float width, float height, RBColor color);
void RBDrawNumber(float x , float y , int n, RBColor color);
void RBDrawCharacter(float x , float y , char c, RBColor color);
void RBDrawString(float x , float y , std::string str, RBColor color);
