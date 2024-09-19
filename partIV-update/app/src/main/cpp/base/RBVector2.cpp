//
//  RBVector.cpp
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

#include <RBVector2.hpp>
#include <math.h>

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
