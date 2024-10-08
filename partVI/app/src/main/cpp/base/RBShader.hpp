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

#pragma once

#include "RBColor.hpp"
#include "RBMath.hpp"

#include <EGL/egl.h>
#include <GLES3/gl3.h>

class RBShader {
public:
    RBShader() {}
    ~RBShader() {}

    bool Create(bool is3D);
    bool Activate() const;

    void MapScreenSize(RBVec2D size);
    void MapProjectionMatrix(RBMat4x4 matrix) const;
    void MapModelMatrix(RBMat4x4 matrix) const;
    void MapColor(RBColor color) const;

public:
    void DrawRectangle(RBVec2D position, RBVec2D size, RBColor color) const;

    void DrawElements(const GLfloat* vertices, const GLubyte* indices, int count) const;

protected:
    GLint AssignAttribute(char* name) const;
    GLint AssignUniform(char* name) const;

private:
    static GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource);
    static GLuint LoadShader(GLenum shaderType, const char* pSource);

private:
    GLuint m_gl_program = -1;
    GLint m_gl_position = -1;
    GLint m_gl_projection = -1;
    GLint m_gl_model = -1;
    GLint m_gl_color = -1;
};
