//
//  RBShader.hpp
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

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#pragma once

class RBShader {
public:
    RBShader();
    ~RBShader();

    bool Create();
    bool Activate();
    void MapSize(int width, int height);

private:
    GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource);
    GLuint LoadShader(GLenum shaderType, const char* pSource);

private:
    GLuint m_gl_program = -1;
    GLuint m_gl_position = -1;
    GLuint m_gl_width = -1;
    GLuint m_gl_height = -1;
};
