//
//  RBRenderer.cpp
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

#include "RBGame.hpp"
#include "RBRenderer.hpp"

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <math.h>
#include <cassert>

#define BACKGROUND_COLOR 0.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f, 1

extern RBGame *g_game;
RBRenderer* g_renderer = nullptr;

RBRenderer::RBRenderer(android_app *app) {
    m_app = app;
    g_renderer = this;
    m_projectionMatrix = RBMatrixMakeIdentity();

    InitOpenGL();

    g_game->OnInit(this);
}

RBRenderer::~RBRenderer() {
    ClearOpenGL();
}

// Game loop

void RBRenderer::RenderFrame() {
    m_shader->Activate();

    glClearColor(BACKGROUND_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);

    // enable alpha globally for now, you probably don't want to do this in a game
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    UpdateRenderArea();

    if (m_updateProjectionMatrix) {
        m_updateProjectionMatrix = false;

        RBVec2D size = g_game->GetGamesSize();
        m_projectionMatrix = RBMatrixMakeOrtho(0, size.w, 0, size.h, 0.0f, 1.0f);
    }

    g_game->OnUpdate(1.0 / 60.0);
    g_game->OnRender();

    eglSwapBuffers(m_display, m_surface);
}

void RBRenderer::UserInput(int tag, int down, int x, int y) {
    RBVec2D size = g_game->GetGamesSize();

    if (tag == 1) {
        // Left
        if (down == 1) {
            if (y <= size.h/2) {
                // Top
                g_game->OnKey(keyW, true);
            }
            else {
                // Bottom
                g_game->OnKey(keyS, true);
            }
        }
        else {
            g_game->OnKey(keyW, false);
            g_game->OnKey(keyS, false);
        }
    }
    else if (tag == 2) {
        // Right
        if (down == 1) {
            if (y <= size.h/2) {
                // Top
                g_game->OnKey(keyUp, true);
            }
            else {
                // Bottom
                g_game->OnKey(keyDown, true);
            }
        }
        else {
            g_game->OnKey(keyUp, false);
            g_game->OnKey(keyDown, false);
        }
    }
}

// OpenGL stuff

void RBRenderer::ClearOpenGL() {
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

void RBRenderer::InitOpenGL() {
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

                    // aout << "Found config with " << red << ", " << green << ", " << blue << ", " << depth << std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    //aout << "Found " << numConfigs << " configs" << std::endl;
    //aout << "Chose " << config << std::endl;

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
}

void RBRenderer::UpdateRenderArea() {
    EGLint width;
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height);

    if (width != m_width || height != m_height) {
        if (m_width == -1 && m_height == -1) {
            // First time
            g_game->SetGameSize(width, height);
            g_game->CreateContent();
        }

        m_width = width;
        m_height = height;
        glViewport(0, 0, width, height);

        // make sure that we lazily recreate the projection matrix before we render
        m_updateProjectionMatrix = true;
    }
}

// Input handling
void RBRenderer::HandleInput() {
    // handle all queued inputs
    for (auto i = 0; i < m_app->motionEventsCount; i++) {

        // cache the current event
        auto &motionEvent = m_app->motionEvents[i];

        // cache the current action
        auto action = motionEvent.action;

        // Find the pointer index, mask and bitshift to turn it into a readable value
        auto pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        //aout << "Pointer " << pointerIndex << ":";

        // get the x and y position of this event
        auto &pointer = motionEvent.pointers[pointerIndex];
        auto x = GameActivityPointerAxes_getX(&pointer);
        auto y = GameActivityPointerAxes_getY(&pointer);
        //aout << "(" << x << ", " << y << ") ";

        // Only consider touchscreen events, like touches
        auto actionMasked = action & AINPUT_SOURCE_TOUCHSCREEN;

        // determine the kind of event it is
        switch (actionMasked) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN:
                //aout << "Pointer Down";
                break;

            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
                //aout << "Pointer Up";
                break;

            default:
                break;
                //aout << "Pointer Move";
        }

        //aout << std::endl;
    }

    // clear inputs, be careful as this will clear it for anyone listening to these events
    android_app_clear_motion_events(m_app);
}
