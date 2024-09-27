//
//  RBRenderHelper.cpp
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

#include "RBRenderHelper.hpp"
#include "RBRenderer.hpp"

#include <ctype.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>

RBRenderer* RBRenderHelper::s_renderer = nullptr;

void RBRenderHelper::SetRenderer(RBRenderer *renderer) {
    s_renderer = renderer;
}

// Render characters

//  -     0
// | |   1 2
//  -     3
// | |   4 5
//  -     6

void RBRenderHelper::DrawSegments(int s0, int s1, int s2, int s3, int s4, int s5, int s6, float x, float y, RBColor color) {
    //  -     0
    // | |   1 2
    //  -     3
    // | |   4 5
    //  -     6
    
    if (s0) {
        RBRenderHelper::DrawRect(x + 5, y + 50, 20, 5, color);
    }

    if (s1) {
        RBRenderHelper::DrawRect(x, y + 30 , 5, 20, color);
    }

    if (s2) {
        RBRenderHelper::DrawRect(x + 25, y + 30, 5, 20, color);
    }

    if (s3) {
        RBRenderHelper::DrawRect(x + 5, y + 25, 20, 5, color);
    }

    if (s4) {
        RBRenderHelper::DrawRect(x, y + 5, 5, 20, color);
    }

    if (s5) {
        RBRenderHelper::DrawRect(x + 25, y + 5 ,5 , 20, color);
    }

    if (s6) {
        RBRenderHelper::DrawRect(x + 5, y, 20, 5, color);
    }
}

void RBRenderHelper::DrawNumber(float x ,float y ,int n, RBColor color) {
    switch(n) {
        case 0:
            RBRenderHelper::DrawSegments(1,1,1,0,1,1,1, x, y, color);
            break;

        case 1:
            RBRenderHelper::DrawSegments(0,0,1,0,0,1,0, x, y, color);
            break;
        
        case 2:
            RBRenderHelper::DrawSegments(1,0,1,1,1,0,1, x, y, color);
            break;
        
        case 3:
            RBRenderHelper::DrawSegments(1,0,1,1,0,1,1, x, y, color);
            break;
        
        case 4:
            RBRenderHelper::DrawSegments(0,1,1,1,0,1,0, x, y, color);
            break;
        
        case 5:
            RBRenderHelper::DrawSegments(1,1,0,1,0,1,1, x, y, color);
            break;
        
        case 6:
            RBRenderHelper::DrawSegments(1,1,0,1,1,1,1, x, y, color);
            break;
        
        case 7:
            RBRenderHelper::DrawSegments(1,0,1,0,0,1,0, x, y, color);
            break;
        
        case 8:
            RBRenderHelper::DrawSegments(1,1,1,1,1,1,1, x, y, color);
            break;
        
        case 9:
            RBRenderHelper::DrawSegments(1,1,1,1,0,1,1, x, y, color);
            break;
    }
}

void RBRenderHelper::DrawCharacter(float x ,float y ,char c, RBColor color) {
    c = toupper(c);
    
    switch (c) {
        case 'A':
            RBRenderHelper::DrawSegments(1,1,1,1,1,1,0, x, y, color);
            break;
        case 'B':
            RBRenderHelper::DrawSegments(0,1,0,1,1,1,1, x, y, color);
            break;
        case 'C':
            RBRenderHelper::DrawSegments(1,1,0,0,1,0,1, x, y, color);
            break;
        case 'D':
            RBRenderHelper::DrawSegments(0,0,1,1,1,1,1, x, y, color);
            break;
        case 'E':
            RBRenderHelper::DrawSegments(1,1,0,1,1,0,1, x, y, color);
            break;
        case 'F':
            RBRenderHelper::DrawSegments(1,1,0,1,1,0,0, x, y, color);
            break;
        case 'G':
            // Not possible
            break;
        case 'H':
            RBRenderHelper::DrawSegments(0,1,1,1,1,1,0, x, y, color);
            break;
        case 'I':
            RBRenderHelper::DrawSegments(0,0,1,0,0,1,0, x, y, color);
            break;
        case 'J':
            RBRenderHelper::DrawSegments(0,0,1,0,0,1,1, x, y, color);
            break;
        case 'K':
            // Not possible
            break;
        case 'L':
            RBRenderHelper::DrawSegments(0,1,0,0,1,0,1, x, y, color);
            break;
        case 'M':
            // Not possible
            break;
        case 'N':
            RBRenderHelper::DrawSegments(0,0,0,1,1,1,0, x, y, color);
            break;
        case 'O':
            RBRenderHelper::DrawSegments(0,0,0,1,1,1,1, x, y, color);
            break;
        case 'P':
            RBRenderHelper::DrawSegments(1,1,1,1,1,0,0, x, y, color);
            break;
        case 'Q':
            // Not possible
            break;
        case 'R':
            RBRenderHelper::DrawSegments(0,0,0,1,1,0,0, x, y, color);
            break;
        case 'S':
            RBRenderHelper::DrawSegments(1,1,0,1,0,1,1, x, y, color);
            break;
        case 'T':
            // Not possible
            break;
        case 'U':
            RBRenderHelper::DrawSegments(0,1,1,0,1,1,1, x, y, color);
            break;
        case 'V':
            // Not possible
            break;
        case 'W':
            // Not possible
            break;
        case 'X':
            // Not possible
            break;
        case 'Y':
            RBRenderHelper::DrawSegments(0,1,1,1,0,1,1, x, y, color);
            break;
        case 'Z':
            RBRenderHelper::DrawSegments(1,0,1,1,1,0,1, x, y, color);
            break;
    }
}

// Draw a string

void RBRenderHelper::DrawString(RBVec2D position , std::string str, RBColor color) {
    float x = position.x;

    for (unsigned i=0; i<str.length(); ++i) {
        char ch = str.at(i);
        int num = (int)ch;
        
        if (num >= 30 && num <= 39) {
            RBRenderHelper::DrawNumber(position.x, position.y, num, color);
            RBRenderHelper::DrawNumber(position.x, position.y, num, color);
        }
        else {
            RBRenderHelper::DrawCharacter(x, position.y, ch, color);
        }
        
        x += 40;
    }
}

// Draw a rectangle

void RBRenderHelper::DrawRect(RBVec2D position, RBVec2D size, RBColor color) {
    s_renderer->GetShader()->DrawRectangle(position, size, color);
}

void RBRenderHelper::DrawRect(float x, float y, float width, float height, RBColor color) {
    RBRenderHelper::DrawRect({x, y}, {width, height}, color);
}

// Draw a cube

void RBRenderHelper::DrawCube(RBVec3D position, RBVec3D rotation, RBVec3D scale, RBColor color) {
    s_renderer->GetShader()->DrawCube(position, rotation, scale, color);
}

// Helper methods

void RBRenderHelper::Enable2D(RBVec2D size) {
    glViewport(0, 0, (int)size.width, (int)size.height);
}

void RBRenderHelper::EnableBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RBRenderHelper::ClearScreen(RBColor color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
