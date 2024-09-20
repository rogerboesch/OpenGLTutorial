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


auto gVertexShader =
        "attribute vec4 vPosition;\n"
        "uniform float fWidth;\n"
        "uniform float fHeight;\n"

        "void main() {\n"
        "  mat4 projectionMatrix = mat4(2.0/fWidth, 0.0, 0.0, -1.0,\n"
        "                              0.0, 2.0/fHeight, 0.0, -1.0,\n"
        "                              0.0, 0.0, -1.0, 0.0,\n"
        "                              0.0, 0.0, 0.0, 1.0);\n"

        "  gl_Position = vPosition;\n"
        "  gl_Position *= projectionMatrix;\n"
        "}\n";

auto gFragmentShader =
        "precision mediump float;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "}\n";

RBShader::RBShader() {
}

RBShader::~RBShader() {
}

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

bool RBShader::Create() {
    m_gl_program = CreateProgram(gVertexShader, gFragmentShader);

    if (!m_gl_program) {
        return false;
    }

    m_gl_position = glGetAttribLocation(m_gl_program, "vPosition");
    m_gl_width = glGetUniformLocation(m_gl_program, "fWidth");
    m_gl_height = glGetUniformLocation(m_gl_program, "fHeight");

    return true;
}

bool RBShader::Activate() {
    if (m_gl_program == -1) {
        return false;
    }

    glUseProgram(m_gl_program);

    return true;
}

void RBShader::MapSize(int width, int height) {
    glUniform1f(m_gl_width, width);
    glUniform1f(m_gl_height, height);
}