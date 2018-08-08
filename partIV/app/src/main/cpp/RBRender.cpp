//
//  RBRender.cpp
//  Android, OpenGL ES 2 (Shader based)
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include <jni.h>
#include <GLES2/gl2.h>
#include <math.h>

#include "Game.hpp"
extern Game *gGame;

GLuint gProgram;
GLuint gPosition;
GLuint gWidth;
GLuint gHeight;


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

GLuint loadShader(GLenum shaderType, const char* pSource) {
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
                char* buf = (char*) malloc(infoLen);

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

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);

    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);

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

bool setupGraphics(int w, int h) {
    gProgram = createProgram(gVertexShader, gFragmentShader);

    if (!gProgram) {
        return false;
    }

    gPosition = glGetAttribLocation(gProgram, "vPosition");
    gWidth = glGetUniformLocation(gProgram, "fWidth");
    gHeight = glGetUniformLocation(gProgram, "fHeight");

    glViewport(0, 0, w, h);

    gGame->OnInit((float)w, (float)h);

    return true;
}

void renderFrame() {
    glUseProgram(gProgram);

    RBVector2 size = gGame->GetGamesSize();

    // Set width and height
    glUniform1f(gWidth, size.width);
    glUniform1f(gHeight, size.height);

    gGame->OnUpdate(1.0/60.0);
    gGame->OnRender();
}

void userInput(int tag, int down, int x, int y) {
    RBVector2 size = gGame->GetGamesSize();

    if (tag == 1) {
        // Left
        if (down == 1) {
            if (y <= size.height/2) {
                // Top
                gGame->OnKey(keyW, true);
            }
            else {
                // Bottom
                gGame->OnKey(keyS, true);
            }
        }
        else {
            gGame->OnKey(keyW, false);
            gGame->OnKey(keyS, false);
        }
    }
    else if (tag == 2) {
        // Right
        if (down == 1) {
            if (y <= size.height/2) {
                // Top
                gGame->OnKey(keyUp, true);
            }
            else {
                // Bottom
                gGame->OnKey(keyDown, true);
            }
        }
        else {
            gGame->OnKey(keyUp, false);
            gGame->OnKey(keyDown, false);
        }
    }
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_touch(JNIEnv * env, jobject obj, jint tag, jint down, jint x, jint y);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height) {
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj) {
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_touch(JNIEnv * env, jobject obj, jint tag, jint down, jint x, jint y) {
    userInput(tag, down, x, y);
}
