//
//  RBRenderer.hpp
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
#include <RBShader.hpp>

#pragma once

struct android_app;

class RBGame;

class RBRenderer {
public:
    explicit RBRenderer(android_app *app);
    ~RBRenderer();

public:
    void RenderFrame();
    void HandleInput();
    void UserInput(bool left, bool down, float x, float y);
    RBShader* GetShader() { return m_shader; }
    void SetShader(RBShader* shader) { m_shader = shader; }

public:
    static void TestOpenGL();

private:
    void InitOpenGL();
    void ClearOpenGL();
    void CreateShader();
    void UpdateRenderArea();
    GLuint LoadShader(GLenum shaderType, const char* pSource);
    GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource);

private:
    android_app *m_app = nullptr;
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    EGLint m_width = 0;
    EGLint m_height = 0;
    bool m_updateProjectionMatrix = false;

    RBShader* m_shader = nullptr;
    RBGame* m_game = nullptr;
};
