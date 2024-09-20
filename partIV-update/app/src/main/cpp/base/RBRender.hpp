//
//  RBRender.hpp
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

struct android_app;

class RBRender {
public:
    RBRender(android_app *app);
    ~RBRender();

public:
    void RenderFrame();
    void HandleInput();
    void UserInput(int tag, int down, int x, int y);

private:
    void InitOpenGL();
    void ClearOpenGL();
    void CreateShader();
    void UpdateRenderArea();
    GLuint LoadShader(GLenum shaderType, const char* pSource);
    GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource);

private:
    android_app *m_app;
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    EGLint m_width;
    EGLint m_height;
    bool m_updateProjectionMatrix;

    RBShader* m_shader = nullptr;
};
