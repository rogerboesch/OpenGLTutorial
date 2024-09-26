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

#include <cstdlib>

static auto gVertexShader =
        "attribute vec4 vertexPosition;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform vec4 vertexColor;\n"
        "varying vec4 v_color;\n"

        "void main() {\n"
        "  v_color = vertexColor;"
        "  gl_Position = projectionMatrix * modelMatrix * vertexPosition;\n"
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
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
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

GLint RBShader::AssignAttribute(char* name) {
    return glGetAttribLocation(m_gl_program, name);
}

GLint RBShader::AssignUniform(char* name) {
    return glGetUniformLocation(m_gl_program, name);
}

void RBShader::MapScreenSize(int width, int height) {
    RBMat4x4 mat = {2.0f/width, 0.0f, 0.0f, -1.0f,
                    0.0f, 2.0f/height, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f};
    MapProjectionMatrix(mat);
}

void RBShader::MapProjectionMatrix(RBMat4x4 matrix) {
    if (m_gl_projection == -1) return;
    glUniformMatrix4fv(m_gl_projection, 1, GL_FALSE, (GLfloat*)&matrix.m[0]);
}

void RBShader::MapModelMatrix(RBMat4x4 matrix) {
    if (m_gl_model == -1) return;
    glUniformMatrix4fv(m_gl_model, 1, GL_FALSE, (GLfloat*)&matrix.m[0]);
}

void RBShader::MapColor(RBColor color) {
    if (m_gl_color == -1) return;
    glUniform4f(m_gl_color, color.r, color.g, color.b, color.a);
}

bool RBShader::Create() {
    m_gl_program = CreateProgram(gVertexShader, gFragmentShader);

    if (!m_gl_program) {
        return false;
    }

    m_gl_position = AssignAttribute("vertexPosition");
    m_gl_color = AssignUniform("vertexColor");
    m_gl_projection = AssignUniform("projectionMatrix");
    m_gl_model = AssignUniform("modelMatrix");

    if (m_gl_color == -1 || m_gl_position == -1 || m_gl_projection == -1) {
        RBERROR("Not all attributes/uniforms mapped");
    }
    else {
        RBLOG("All attributes/uniforms mapped");
    }

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
    MapColor(color);

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

void RBShader::DrawCube(RBVec3D position, RBVec3D rotation, RBVec3D scale, RBColor color) {
    static const GLfloat verticesCube[] = {
            -0.5f, 0.5f, 0.5f,     //  0: Front-top-left
            0.5f, 0.5f, 0.5f,      //  1: Front-top-right
            -0.5f, -0.5f, 0.5f,    //  2: Front-bottom-left
            0.5f, -0.5f, 0.5f,     //  3: Front-bottom-right
            0.5f, -0.5f, -0.5f,    //  4: Back-bottom-right
            0.5f, 0.5f, 0.5f,      //  5: Front-top-right
            0.5f, 0.5f, -0.5f,     //  6: Back-top-right
            -0.5f, 0.5f, 0.5f,     //  7: Front-top-left
            -0.5f, 0.5f, -0.5f,    //  8: Back-top-left
            -0.5f, -0.5f, 0.5f,    //  9: Front-bottom-left
            -0.5f, -0.5f, -0.5f,   // 10: Back-bottom-left
            0.5f, -0.5f, -0.5f,    // 11: Back-bottom-right
            -0.5f, 0.5f, -0.5f,    // 12: Back-top-left
            0.5f, 0.5f, -0.5f      // 13: Back-top-right
    };

    static const GLubyte indicesCube[] = {
            2,3,3,1,1,0,0,2,
            10,11,11,13,13,12,12,10,
            0,12,2,10,
            1,13,3,11
    };

    MapColor(color);

    RBMat4x4 transform = RBMatrixMakeIdentity();

    RBMat4x4 translation = RBMatrixMakeTranslation(position.x, position.y, position.z);
    RBMat4x4 rotationX = RBMatrixMakeRotationX(RAD_TO_DEG(rotation.x));
    RBMat4x4 rotationY = RBMatrixMakeRotationY(RAD_TO_DEG(rotation.y));
    RBMat4x4 rotationZ = RBMatrixMakeRotationZ(RAD_TO_DEG(rotation.z));

    transform = RBMatrixMultiplyMatrix(transform, rotationX);
    transform = RBMatrixMultiplyMatrix(transform, rotationY);
    transform = RBMatrixMultiplyMatrix(transform, rotationZ);
    transform = RBMatrixMultiplyMatrix(transform, translation);

    // TODO: Add scaling
    MapModelMatrix(transform);

    glVertexAttribPointer(m_gl_position, 3, GL_FLOAT, GL_FALSE, 0, verticesCube);
    glEnableVertexAttribArray(m_gl_position);

    glDrawElements(GL_LINES, sizeof(indicesCube)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indicesCube);
}
