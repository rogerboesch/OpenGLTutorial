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

class RBRenderer;

class RBRenderHelper {
public:
    static void DrawRect(RBVec2D position, RBVec2D size, RBColor color);
    static void DrawCube(RBVec3D position, RBVec3D rotation, RBVec3D scale, RBColor color);
    static void DrawString(RBVec2D position , std::string str, RBColor color);
    static void DrawNumber(float x , float y , int n, RBColor color);

    static void Enable2D(RBVec2D size);
    static void EnableBlending();
    static void ClearScreen(RBColor color);

    static void SetRenderer(RBRenderer* renderer);

private:
    static void DrawRect(float x, float y, float width, float height, RBColor color);
    static void DrawCharacter(float x , float y , char c, RBColor color);
    static void DrawSegments(int s0, int s1, int s2, int s3, int s4, int s5, int s6, float x, float y, RBColor color);

private:
    static RBRenderer* s_renderer;
};
