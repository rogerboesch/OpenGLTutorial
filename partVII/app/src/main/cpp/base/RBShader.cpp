//
//  RBShader.cpp
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

#include "RBShader.hpp"
#include "RBMath.hpp"
#include "RBLog.hpp"
#include "RBRenderer.hpp"

#include <cstdlib>

static auto gVertexShader2D =
        "attribute vec4 vertexPosition;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform vec4 vertexColor;\n"
        "varying vec4 v_color;\n"

        "void main() {\n"
        "  v_color = vertexColor;"
        "  gl_Position = vertexPosition * projectionMatrix * modelMatrix;\n"
        "}\n";

static auto gVertexShader3D =
        "attribute vec4 vertexPosition;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform vec4 vertexColor;\n"
        "varying vec4 v_color;\n"

        "void main() {\n"
        "  v_color = vertexColor;"
        "  gl_Position =  projectionMatrix * modelMatrix * vertexPosition;\n"
        "}\n";

static auto gFragmentShader =
        "precision mediump float;\n"
        "varying vec4 v_color;\n"

        "void main() {\n"
        "  gl_FragColor = v_color;\n"
        "}\n";

GLuint RBShader::LoadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);

    if (shader) {
        glShaderSource(shader, 1, &pSource, nullptr);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen) {
                char* buf = (char*)malloc(infoLen);

                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, nullptr, buf);

                    RBERROR(buf);

                    free(buf);
                }

                glDeleteShader(shader);
                shader = 0;

                return 0;
            }
        }
    }

    return shader;
}

GLuint RBShader::CreateProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, pVertexSource);

    if (!vertexShader) {
        RBERROR("Error loading VERTEX shader");
        return 0;
    }
    else {
        RBLOG("VERTEX shader loaded");
    }

    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, pFragmentSource);

    if (!fragmentShader) {
        RBERROR("Error loading FRAGMENT shader");
        return 0;
    }
    else {
        RBLOG("FRAGMENT shader loaded");
    }

    GLuint program = glCreateProgram();

    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);

            if (bufLength) {
                char* buf = (char*) malloc(bufLength);

                if (buf) {
                    glGetProgramInfoLog(program, bufLength, nullptr, buf);
                    RBERROR(buf);

                    free(buf);
                }
            }

            glDeleteProgram(program);
            program = 0;
            return 0;
        }
    }

    RBLOG("Program compiled");

    return program;
}

GLint RBShader::AssignAttribute(char* name) const {
    return glGetAttribLocation(m_gl_program, name);
}

GLint RBShader::AssignUniform(char* name) const {
    return glGetUniformLocation(m_gl_program, name);
}

void RBShader::MapScreenSize(RBVec2D size) {
    RBMat4x4 mat = {2.0f/size.width, 0.0f, 0.0f, -1.0f,
                    0.0f, 2.0f/size.height, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f};
    MapProjectionMatrix(mat);
    MapModelMatrix(RBMatrixMakeIdentity());
}

void RBShader::MapProjectionMatrix(RBMat4x4 matrix) const {
    if (m_gl_projection == -1) return;
    glUniformMatrix4fv(m_gl_projection, 1, GL_FALSE, (GLfloat*)&matrix.m[0]);
    RBRenderer::TestOpenGL();
}

void RBShader::MapModelMatrix(RBMat4x4 matrix) const {
    if (m_gl_model == -1) return;
    glUniformMatrix4fv(m_gl_model, 1, GL_FALSE, (GLfloat*)&matrix.m[0]);
    RBRenderer::TestOpenGL();
}

void RBShader::MapColor(RBColor color) const {
    if (m_gl_color == -1) return;
    glUniform4f(m_gl_color, color.r, color.g, color.b, color.a);
    RBRenderer::TestOpenGL();
}

bool RBShader::Create(bool is3D) {
    m_gl_program = CreateProgram(is3D ? gVertexShader3D : gVertexShader2D, gFragmentShader);

    if (!m_gl_program) {
        return false;
    }

    m_gl_position = AssignAttribute("vertexPosition");
    m_gl_color = AssignUniform("vertexColor");
    m_gl_projection = AssignUniform("projectionMatrix");
    m_gl_model = AssignUniform("modelMatrix");

    if (m_gl_color == -1 || m_gl_position == -1 || m_gl_projection == -1 || m_gl_model == -1) {
        RBERROR("Not all attributes/uniforms mapped");
    }
    else {
        RBLOG("All attributes/uniforms mapped");
    }

    return true;
}

bool RBShader::Activate() const {
    if (m_gl_program == -1) {
        return false;
    }

    glUseProgram(m_gl_program);

    return true;
}

void RBShader::DrawElements(const GLfloat* vertices, const GLubyte* indices, int count) const {
    glVertexAttribPointer(m_gl_position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(m_gl_position);

    glDrawElements(GL_LINES, count, GL_UNSIGNED_BYTE, indices);
}

void RBShader::DrawRectangle(RBVec2D position, RBVec2D size, RBColor color) const {
    MapColor(color);

    GLfloat vertices[] = {
            position.x,       position.y+size.height, 0.0f,         // Upper left
            position.x+size.width, position.y+size.height, 0.0f,    // Upper right
            position.x,       position.y,        0.0f,              // Lower left
            position.x+size.width, position.y,        0.0f,        // Lower right
    };

    glVertexAttribPointer(m_gl_position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(m_gl_position);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    RBRenderer::TestOpenGL();
}
