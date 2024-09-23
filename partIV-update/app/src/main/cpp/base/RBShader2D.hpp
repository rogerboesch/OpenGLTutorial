//
//  RBShader2D.hpp
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

#include <RBShader.hpp>

#pragma once

class RBShader2D : public RBShader {
public:
    RBShader2D();
    ~RBShader2D() {}

    void MapSize(int width, int height);

private:
    GLint m_gl_position;
    GLint m_gl_width;
    GLint m_gl_height;
};
