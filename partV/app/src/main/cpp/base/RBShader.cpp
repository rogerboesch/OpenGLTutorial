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

#include <RBShader.hpp>
#include <cstdlib>
RBShader::RBShader() {}

RBShader::~RBShader() {}

GLuint RBShader::LoadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);

    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen) {
                char* buf = (char*)malloc(infoLen);

                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    free(buf);
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint RBShader::CreateProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, pVertexSource);

    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = LoadShader(GL_FRAGMENT_SHADER, pFragmentSource);

    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();

    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);

            if (bufLength) {
                char* buf = (char*) malloc(bufLength);

                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    free(buf);
                }
            }

            glDeleteProgram(program);
            program = 0;
        }
    }

    return program;
}

GLint RBShader::AssignAttribute(char* name) {
    return glGetAttribLocation(m_gl_program, name);
}

GLint RBShader::AssignUniform(char* name) {
    return glGetUniformLocation(m_gl_program, name);
}

void RBShader::MapUniform(GLint parameter, int value) {
    glUniform1f(parameter, value);
}

void RBShader::MapProjectionMatrix(RBMat4x4 matrix) {
    glUniformMatrix4fv(m_gl_projection, 1, GL_FALSE, (GLfloat*)&matrix.m[0]);
}

bool RBShader::Create(const char* pVertexSource, const char* pFragmentSource) {
    m_gl_program = CreateProgram(pVertexSource, pFragmentSource);

    if (!m_gl_program) {
        return false;
    }

    m_gl_position = AssignAttribute("vertexPosition");
    m_gl_color = AssignAttribute("vertexColor");
    m_gl_projection = AssignUniform("projectionMatrix");

    return true;
}

bool RBShader::Activate() {
    if (m_gl_program == -1) {
        return false;
    }

    glUseProgram(m_gl_program);

    return true;
}

void RBShader::DrawRectangle(float x, float y, float width, float height, RBColor color) {
    GLfloat vertices[] = {
            x,       y+height, 0.0f, // Upper left
            x+width, y+height, 0.0f, // Upper right
            x,       y,        0.0f, // Lower left
            x+width, y,        0.0f, // Lower right
    };

    glVertexAttribPointer(m_gl_position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(m_gl_position);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void RBShader::Enable2D(float width, float height) {
    glViewport(0, 0, width, height);
}

void RBShader::EnableBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RBShader::ClearScreen(RBColor color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
