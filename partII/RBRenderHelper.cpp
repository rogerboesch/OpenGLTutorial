//
//  RBRenderHelper.cpp
//  partII
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "RBRenderHelper.hpp"

// -----------------------------------------------------------------------------
#pragma mark - Render (colored) rectangles

void RBDrawRect(RBVector2 position, RBVector2 size) {
    RBDrawRect(position.x, position.y, size.width, size.height);
}

void RBDrawRect(float x, float y, float width, float height) {
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
    
    glVertex2f(x, y);                     // Bottom left
    glVertex2f(x + width, y);             // Bottom right
    glVertex2f(x + width, y + height);    // Top right
    glVertex2f(x, y + height);            // Top left
    
    glEnd();
}

// -----------------------------------------------------------------------------
#pragma mark - Render numbers

void RBDrawSegments(int s0, int s1, int s2, int s3, int s4, int s5, int s6, float x, float y) {
    //  -     0
    // | |   1 2
    //  -     3
    // | |   4 5
    //  -     6
    
    if (s0) {
        RBDrawRect(x + 5, y + 50, 20, 5);
    }

    if (s1) {
        RBDrawRect(x, y + 30 , 5, 20);
    }

    if (s2) {
        RBDrawRect(x + 25, y + 30, 5, 20);
    }

    if (s3) {
        RBDrawRect(x + 5, y + 25, 20, 5);
    }

    if (s4) {
        RBDrawRect(x, y + 5, 5, 20);
    }

    if (s5) {
        RBDrawRect(x + 25, y + 5 ,5 , 20);
    }

    if (s6) {
        RBDrawRect(x + 5, y, 20, 5);
    }
}

void RBDrawNumber(float x , float y , int n) {
    switch(n) {
        case 0:
            RBDrawSegments(1,1,1,0,1,1,1, x, y);
            break;

        case 1:
            RBDrawSegments(0,0,1,0,0,1,0, x, y);
            break;
        
        case 2:
            RBDrawSegments(1,0,1,1,1,0,1, x, y);
            break;
        
        case 3:
            RBDrawSegments(1,0,1,1,0,1,1, x, y);
            break;
        
        case 4:
            RBDrawSegments(0,1,1,1,0,1,0, x, y);
            break;
        
        case 5:
            RBDrawSegments(1,1,0,1,0,1,1, x, y);
            break;
        
        case 6:
            RBDrawSegments(1,1,0,1,1,1,1, x, y);
            break;
        
        case 7:
            RBDrawSegments(1,0,1,0,0,1,0, x, y);
            break;
        
        case 8:
            RBDrawSegments(1,1,1,1,1,1,1, x, y);
            break;
        
        case 9:
            RBDrawSegments(1,1,1,1,0,1,1, x, y);
            break;
    }
}

