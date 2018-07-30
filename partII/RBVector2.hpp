//
//  RBVector2.hpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#include <cstring>
#include <assert.h>

class RBVector4f;
class RBMatrix2x2f;
class RBMatrix4x4f;

class RBVector2 {
public:
    union {
        float value[2];
        struct { float x, y; };
        struct { float r, g; };
        struct { float s, t; };
        struct { float width, height; };
    };
    
    float& operator [](const size_t i) { assert(i < 2); return value[i]; }
    const float& operator [](const size_t i) const { assert(i < 2); return value[i]; }
    
    RBVector2 operator +(const RBVector2& b) const { return RBVector2(x + b.x, y + b.y); }
    RBVector2 operator -(const RBVector2& b) const { return RBVector2(x - b.x, y - b.y); }
    RBVector2 operator *(const RBVector2& b) const { return RBVector2(x * b.x, y * b.y); }
    RBVector2 operator /(const RBVector2& b) const { return RBVector2(x / b.x, y / b.y); }
    RBVector2 operator -() const /* Unary minus */ { return RBVector2(-x, -y); }
    RBVector2 operator *(const float& b) const { return RBVector2(x * b, y * b); }
    RBVector2 operator /(const float& b) const { return RBVector2(x / b, y / b); }
    
    bool operator ==(const RBVector2& b) const { return (x == b.x) && (y == b.y); }
    bool operator !=(const RBVector2& b) const { return !(*this == b); }
    
    RBVector2& operator +=(const RBVector2& b) { *this = *this + b; return *this; }
    RBVector2& operator -=(const RBVector2& b) { *this = *this - b; return *this; }
    RBVector2& operator *=(const RBVector2& b) { *this = *this * b; return *this; }
    RBVector2& operator /=(const RBVector2& b) { *this = *this / b; return *this; }
    RBVector2& operator *=(const float& b) { *this = *this * b; return *this; }
    RBVector2& operator /=(const float& b) { *this = *this / b; return *this; }
    
public:
    explicit RBVector2() : x(0), y(0) { }
    explicit RBVector2(const float& n) : x(n), y(n) { }
    explicit RBVector2(const float& nx, const float& ny) : x(nx), y(ny) { }
    
public:
    float length() const;
    float lengthSquared() const;
    float distance(const RBVector2 &p1) const;
    float distanceSquared(const RBVector2 &p1) const;
    float dot(const RBVector2 &v2) const;
    RBVector2 normalize() const;
};

RBVector2 operator* (const float &s, const RBVector2 &v);
