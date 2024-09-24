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

#include <RBRenderHelper.hpp>
#include <RBRender.hpp>

#include <ctype.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>

extern RBRender* g_renderer;

// -----------------------------------------------------------------------------
#pragma mark - Render (colored) rectangles

void RBDrawRect(RBVec2D position, RBVec2D size, RBColor color) {
    RBDrawRect(position.x, position.y, size.w, size.h, color);
}

// -----------------------------------------------------------------------------
#pragma mark - Render characters
    
//  -     0
// | |   1 2
//  -     3
// | |   4 5
//  -     6

void RBDrawSegments(int s0, int s1, int s2, int s3, int s4, int s5, int s6, float x, float y, RBColor color) {
    //  -     0
    // | |   1 2
    //  -     3
    // | |   4 5
    //  -     6
    
    if (s0) {
        RBDrawRect(x + 5, y + 50, 20, 5, color);
    }

    if (s1) {
        RBDrawRect(x, y + 30 , 5, 20, color);
    }

    if (s2) {
        RBDrawRect(x + 25, y + 30, 5, 20, color);
    }

    if (s3) {
        RBDrawRect(x + 5, y + 25, 20, 5, color);
    }

    if (s4) {
        RBDrawRect(x, y + 5, 5, 20, color);
    }

    if (s5) {
        RBDrawRect(x + 25, y + 5 ,5 , 20, color);
    }

    if (s6) {
        RBDrawRect(x + 5, y, 20, 5, color);
    }
}

void RBDrawNumber(float x ,float y ,int n, RBColor color) {
    switch(n) {
        case 0:
            RBDrawSegments(1,1,1,0,1,1,1, x, y, color);
            break;

        case 1:
            RBDrawSegments(0,0,1,0,0,1,0, x, y, color);
            break;
        
        case 2:
            RBDrawSegments(1,0,1,1,1,0,1, x, y, color);
            break;
        
        case 3:
            RBDrawSegments(1,0,1,1,0,1,1, x, y, color);
            break;
        
        case 4:
            RBDrawSegments(0,1,1,1,0,1,0, x, y, color);
            break;
        
        case 5:
            RBDrawSegments(1,1,0,1,0,1,1, x, y, color);
            break;
        
        case 6:
            RBDrawSegments(1,1,0,1,1,1,1, x, y, color);
            break;
        
        case 7:
            RBDrawSegments(1,0,1,0,0,1,0, x, y, color);
            break;
        
        case 8:
            RBDrawSegments(1,1,1,1,1,1,1, x, y, color);
            break;
        
        case 9:
            RBDrawSegments(1,1,1,1,0,1,1, x, y, color);
            break;
    }
}

void RBDrawCharacter(float x ,float y ,char c, RBColor color) {
    c = toupper(c);
    
    switch (c) {
        case 'A':
            RBDrawSegments(1,1,1,1,1,1,0, x, y, color);
            break;
        case 'B':
            RBDrawSegments(0,1,0,1,1,1,1, x, y, color);
            break;
        case 'C':
            RBDrawSegments(1,1,0,0,1,0,1, x, y, color);
            break;
        case 'D':
            RBDrawSegments(0,0,1,1,1,1,1, x, y, color);
            break;
        case 'E':
            RBDrawSegments(1,1,0,1,1,0,1, x, y, color);
            break;
        case 'F':
            RBDrawSegments(1,1,0,1,1,0,0, x, y, color);
            break;
        case 'G':
            // Not possible
            break;
        case 'H':
            RBDrawSegments(0,1,1,1,1,1,0, x, y, color);
            break;
        case 'I':
            RBDrawSegments(0,0,1,0,0,1,0, x, y, color);
            break;
        case 'J':
            RBDrawSegments(0,0,1,0,0,1,1, x, y, color);
            break;
        case 'K':
            // Not possible
            break;
        case 'L':
            RBDrawSegments(0,1,0,0,1,0,1, x, y, color);
            break;
        case 'M':
            // Not possible
            break;
        case 'N':
            RBDrawSegments(0,0,0,1,1,1,0, x, y, color);
            break;
        case 'O':
            RBDrawSegments(0,0,0,1,1,1,1, x, y, color);
            break;
        case 'P':
            RBDrawSegments(1,1,1,1,1,0,0, x, y, color);
            break;
        case 'Q':
            // Not possible
            break;
        case 'R':
            RBDrawSegments(0,0,0,1,1,0,0, x, y, color);
            break;
        case 'S':
            RBDrawSegments(1,1,0,1,0,1,1, x, y, color);
            break;
        case 'T':
            // Not possible
            break;
        case 'U':
            RBDrawSegments(0,1,1,0,1,1,1, x, y, color);
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
            RBDrawSegments(0,1,1,1,0,1,1, x, y, color);
            break;
        case 'Z':
            RBDrawSegments(1,0,1,1,1,0,1, x, y, color);
            break;
    }
}

// -----------------------------    ------------------------------------------------
#pragma mark - Render string

void RBDrawString(float x , float y , std::string str, RBColor color) {
    for (unsigned i=0; i<str.length(); ++i) {
        char ch = str.at(i);
        int num = (int)ch;
        
        if (num >= 30 && num <= 39) {
            RBDrawNumber(x, y, num, color);
        }
        else {
            RBDrawCharacter(x, y, ch, color);
        }
        
        x += 40;
    }
}

// -----------------------------------------------------------------------------
#pragma mark - OpenGL Helper method

void RBDrawRect(float x, float y, float width, float height, RBColor color) {
    if (g_renderer == nullptr) return;
    if (g_renderer->GetShader() == nullptr) return;

    g_renderer->GetShader()->DrawRectangle(x, y, width, height, color);
}
