//
//  RBColor.hpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
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
