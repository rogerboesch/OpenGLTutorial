//
//  RBVector2.cpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "RBVector2.hpp"
#include "math.h"

RBVector2 operator* (const float &s, const RBVector2 &v) {
    return v * s;    
}

float RBVector2::length() const {
    return sqrtf(lengthSquared());
}

float RBVector2::lengthSquared() const {
    return dot(*this);
}

float RBVector2::distance(const RBVector2 &p1) const {
    return sqrtf((*this).distanceSquared(p1));
}

float RBVector2::distanceSquared(const RBVector2 &p1) const {
    return (p1 - (*this)).lengthSquared();
}

float RBVector2::dot(const RBVector2 &v2) const {
    return x * v2.x + y * v2.y;
}

RBVector2 RBVector2::normalize() const {
    return (*this) / length();
}
