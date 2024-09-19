//
//  RBColor.hpp
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

#include <cstring>
#include <assert.h>

class RBColor {
public:
    union {
        float value[4];
        struct { float r, g, b, a; };
    };
    
    float& operator [](const size_t i) { assert(i < 2); return value[i]; }
    const float& operator [](const size_t i) const { assert(i < 2); return value[i]; }
    
public:
    explicit RBColor() : r(0), g(0), b(0), a(1) { }
    explicit RBColor(const float& n) : r(n), g(n), b(n), a(1) { }
    explicit RBColor(const float& r, const float& g, const float& b, const float& a) : r(r), g(g), b(b), a(a) { }
};

extern RBColor RBColorBlack;
extern RBColor RBColorWhite;
extern RBColor RBColorGrayLight;
extern RBColor RBColorRed;
