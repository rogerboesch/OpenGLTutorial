//
//  RBRenderHelper.cpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "RBRenderHelper.hpp"

#include <ctype.h>
#import <OpenGLES/ES1/glext.h>

// -----------------------------------------------------------------------------
#pragma mark - Render (colored) rectangles

void RBDrawRect(RBVector2 position, RBVector2 size, RBColor color) {
    RBDrawRect(position.x, position.y, size.width, size.height, color);
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

// -----------------------------------------------------------------------------
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
    GLfloat vertices[] = {
        x,       y+height, 0.0f, // Upper left
        x+width, y+height, 0.0f, // Upper right
        x,       y,        0.0f, // Lower left
        x+width, y,        0.0f, // Lower right
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(color.r, color.g, color.b, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void RBEnable2D(float width, float height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}

void RBEnable2D(RBVector2 size) {
    RBEnable2D(size.width, size.height);
}

void RBEnableBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RBClearScreen(RBColor color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
