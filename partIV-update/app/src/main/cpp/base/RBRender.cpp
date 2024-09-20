//
//  RBRender.cpp
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
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <math.h>

#include <RBGame.hpp>
#include <RBRender.hpp>

#include "AndroidOut.h"

#define PRINT_GL_STRING(s) {aout << #s": "<< glGetString(s) << std::endl;}
#define PRINT_GL_STRING_AS_LIST(s) { \
std::istringstream extensionStream((const char *) glGetString(s));\
std::vector<std::string> extensionList(\
        std::istream_iterator<std::string>{extensionStream},\
        std::istream_iterator<std::string>());\
aout << #s":\n";\
for (auto& extension: extensionList) {\
    aout << extension << "\n";\
}\
aout << std::endl;\
}

#define CORNFLOWER_BLUE 100 / 255.f, 149 / 255.f, 237 / 255.f, 1

extern RBGame *gGame;

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

RBRender::RBRender(android_app *app) {
    m_app = app;

    InitOpenGL();
    CreateShader();
    gGame->OnInit();
}

RBRender::~RBRender() {
    ClearOpenGL();
}

// Game loop

void RBRender::RenderFrame() {
    glUseProgram(m_gl_program);
    glClearColor(CORNFLOWER_BLUE);
    glClear(GL_COLOR_BUFFER_BIT);

    // enable alpha globally for now, you probably don't want to do this in a game
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    UpdateRenderArea();

    if (m_updateProjectionMatrix) {
        m_updateProjectionMatrix = false;

        // Set width and height
        RBVector2 size = gGame->GetGamesSize();
        glUniform1f(m_gl_width, size.width);
        glUniform1f(m_gl_height, size.height);
    }

    gGame->OnUpdate(1.0/60.0);
    gGame->OnRender();

    eglSwapBuffers(m_display, m_surface);
}

void RBRender::UserInput(int tag, int down, int x, int y) {
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

// OpenGL stuff

void RBRender::ClearOpenGL() {
    if (m_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_display, m_context);
            m_context = EGL_NO_CONTEXT;
        }
        if (m_surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_display, m_surface);
            m_surface = EGL_NO_SURFACE;
        }
        eglTerminate(m_display);
        m_display = EGL_NO_DISPLAY;
    }
}

void RBRender::InitOpenGL() {
    // Choose your render attributes
    constexpr EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    // The default display is probably what you want on Android
    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    // figure out how many configs there are
    EGLint numConfigs;
    eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);

    // get the list of configurations
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
            supportedConfigs.get(),
            supportedConfigs.get() + numConfigs,
            [&display](const EGLConfig &config) {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                    && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                    && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                    && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                    aout << "Found config with " << red << ", " << green << ", " << blue << ", "
                         << depth << std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    aout << "Found " << numConfigs << " configs" << std::endl;
    aout << "Chose " << config << std::endl;

    // create the proper window surface
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    EGLSurface surface = eglCreateWindowSurface(display, config, m_app->window, nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(display, config, nullptr, contextAttribs);

    // get some window metrics
    auto madeCurrent = eglMakeCurrent(display, surface, surface, context);
    assert(madeCurrent);

    m_display = display;
    m_surface = surface;
    m_context = context;

    // make width and height invalid so it gets updated in the first frame
    m_width = -1;
    m_height = -1;

    PRINT_GL_STRING(GL_VENDOR);
    PRINT_GL_STRING(GL_RENDERER);
    PRINT_GL_STRING(GL_VERSION);
    PRINT_GL_STRING_AS_LIST(GL_EXTENSIONS);
}

void RBRender::UpdateRenderArea() {
    EGLint width;
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height);

    if (width != m_width || height != m_height) {
        if (m_width == -1 && m_height == -1) {
            // First time
            gGame->SetGameSize(width, height);
            gGame->CreateContent();
        }

        m_width = width;
        m_height = height;
        glViewport(0, 0, width, height);

        // make sure that we lazily recreate the projection matrix before we render
        m_updateProjectionMatrix = true;
    }
}

GLuint RBRender::LoadShader(GLenum shaderType, const char* pSource) {
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

GLuint RBRender::CreateProgram(const char* pVertexSource, const char* pFragmentSource) {
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

void RBRender::CreateShader() {
    m_gl_program = CreateProgram(gVertexShader, gFragmentShader);

    if (!m_gl_program) {
        return;
    }

    m_gl_position = glGetAttribLocation(m_gl_program, "vPosition");
    m_gl_width = glGetUniformLocation(m_gl_program, "fWidth");
    m_gl_height = glGetUniformLocation(m_gl_program, "fHeight");
}

// Input handling
void RBRender::HandleInput() {
    // handle all queued inputs
    for (auto i = 0; i < m_app->motionEventsCount; i++) {

        // cache the current event
        auto &motionEvent = m_app->motionEvents[i];

        // cache the current action
        auto action = motionEvent.action;

        // Find the pointer index, mask and bitshift to turn it into a readable value
        auto pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        aout << "Pointer " << pointerIndex << ":";

        // get the x and y position of this event
        auto &pointer = motionEvent.pointers[pointerIndex];
        auto x = GameActivityPointerAxes_getX(&pointer);
        auto y = GameActivityPointerAxes_getY(&pointer);
        aout << "(" << x << ", " << y << ") ";

        // Only consider touchscreen events, like touches
        auto actionMasked = action & AINPUT_SOURCE_TOUCHSCREEN;

        // determine the kind of event it is
        switch (actionMasked) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN:
                aout << "Pointer Down";
                break;

            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
                aout << "Pointer Up";
                break;

            default:
                aout << "Pointer Move";
        }

        aout << std::endl;
    }

    // clear inputs, be careful as this will clear it for anyone listening to these events
    android_app_clear_motion_events(m_app);
}