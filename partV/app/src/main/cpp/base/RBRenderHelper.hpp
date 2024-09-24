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

#include <string>
#include <RBMath.hpp>
#include <RBColor.hpp>

void RBDrawRect(RBVec2D position, RBVec2D size, RBColor color);
void RBDrawRect(float x, float y, float width, float height, RBColor color);
void RBDrawNumber(float x , float y , int n, RBColor color);
void RBDrawCharacter(float x , float y , char c, RBColor color);
void RBDrawString(float x , float y , std::string str, RBColor color);
