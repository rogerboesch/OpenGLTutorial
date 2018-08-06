//
//  RBRenderHelper.hpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#include <string>
#include "RBVector2.hpp"
#include "RBColor.hpp"

void RBDrawRect(RBVector2 position, RBVector2 size, RBColor color);
void RBDrawRect(float x, float y, float width, float height, RBColor color);
void RBDrawNumber(float x , float y , int n, RBColor color);
void RBDrawCharacter(float x , float y , char c, RBColor color);
void RBDrawString(float x , float y , std::string str, RBColor color);

void RBEnable2D(RBVector2 size);
void RBEnable2D(float width, float height);
void RBEnableBlending();
void RBClearScreen(RBColor color);
