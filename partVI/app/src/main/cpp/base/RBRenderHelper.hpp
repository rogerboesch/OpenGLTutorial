//
//  RBRenderHelper.hpp
//
//  The OpenGL Tutorial
//  This code was written as part of a tutorial at https://medium.com/@rogerboesch/
//
//  Created by Roger Boesch on 07/30/2018.
//
//  DISCLAIMER:
//  The intention of this tutorial is not to always write the best possible code but
//  to show different ways to create a game or app that even can be published.
//  I will also refactor a lot during the tutorial and improve things step by step
//  or even show completely different approaches.
//
//  Feel free to use the code in the way you want :)
//

#pragma once

#include "RBColor.hpp"
#include "RBMath.hpp"

#include <string>

void RBDrawRect(RBVec2D position, RBVec2D size, RBColor color);
void RBDrawString(RBVec2D position , std::string str, RBColor color);
void RBDrawCube(RBVec3D position, RBVec3D rotation, RBVec3D scale, RBColor color);

void RBEnable2D(RBVec2D size);
void RBEnableBlending();
void RBClearScreen(RBColor color);
