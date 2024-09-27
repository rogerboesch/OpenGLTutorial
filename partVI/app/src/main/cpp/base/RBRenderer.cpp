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
#include "RBRenderHelper.hpp"
#include "RBLog.hpp"

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <math.h>

extern RBGame* game_main(RBRenderer* renderer);

#define BACKGROUND_COLOR 0.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f, 1

RBRenderer::RBRenderer(android_app *app) {
    m_app = app;

    InitOpenGL();
    CreateShader();

    // Initialize helper
    RBRenderHelper::SetRenderer(this);

    // Initialize game
    m_game = game_main(this);
    m_game->OnInit(this);
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

        // Set width and height
        RBVec2D size = m_game->GetGamesSize();
        m_shader->MapScreenSize(size);

        // Call game id it's needed to update something
        m_game->SizeChanged();
    }

    m_game->OnUpdate(1.0/60.0);
    m_game->OnRender();

    eglSwapBuffers(m_display, m_surface);
}

void RBRenderer::UserInput(bool left, bool down, float x, float y) {
    RBVec2D size = m_game->GetGamesSize();

    if (left) {
        // Left
        if (down) {
            if (y <= size.height/2) {
                // Top
                m_game->OnKey(keyW, true);
            }
            else {
                // Bottom
                m_game->OnKey(keyS, true);
            }
        }
        else {
            m_game->OnKey(keyW, false);
            m_game->OnKey(keyS, false);
        }
    }
    else {
        // Right
        if (down) {
            if (y <= size.height/2) {
                // Top
                m_game->OnKey(keyUp, true);
            }
            else {
                // Bottom
                m_game->OnKey(keyDown, true);
            }
        }
        else {
            m_game->OnKey(keyUp, false);
            m_game->OnKey(keyDown, false);
        }
    }
}

// OpenGL stuff

void RBRenderer::TestOpenGL() {
    GLenum err;
    char msg[1024];
    while (( err = glGetError()) != GL_NO_ERROR) {
        sprintf(msg, "OpenGL error: %d", err);
        RBERROR(msg);
    }
}

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

                    char msg[1024];
                    sprintf(msg, "Found config with %d,%d,%d (%d)", red, blue, green, depth);
                    RBLOG(msg);

                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }

                RBERROR("Error getting display config");
                return false;
            });

    char msg[1024];
    sprintf(msg, "Found %d configs", numConfigs);
    RBLOG(msg);

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
            m_game->SetGameSize(width, height);
            m_game->CreateContent();
        }

        m_width = width;
        m_height = height;
        glViewport(0, 0, width, height);

        // make sure that we lazily recreate the projection matrix before we render
        m_updateProjectionMatrix = true;

        char msg[1024];
        sprintf(msg, "Screen changed to %d x %d", width, height);
        RBLOG(msg)
    }
}

void RBRenderer::CreateShader() {
    auto shader = new RBShader();
    shader->Create();
    m_shader = shader;
}

// Input handling
void RBRenderer::HandleInput() {
    auto *inputBuffer = android_app_swap_input_buffers(m_app);
    if (!inputBuffer) {
        // no inputs yet.
        return;
    }

    // handle all queued inputs
    for (auto i = 0; i < inputBuffer->motionEventsCount; i++) {
        // cache the current event
        auto &motionEvent = inputBuffer->motionEvents[i];

        // cache the current action
        auto action = motionEvent.action;

        // Find the pointer index, mask and bitshift to turn it into a readable value
        auto pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

        // get the x and y position of this event
        auto &pointer = motionEvent.pointers[pointerIndex];
        auto x = GameActivityPointerAxes_getX(&pointer);
        auto y = GameActivityPointerAxes_getY(&pointer);

        // Only consider touchscreen events, like touches
        // auto actionMasked = action & AINPUT_SOURCE_TOUCHSCREEN;
        // We use this to also receive AMOTION_EVENT_ACTION_POINTER_UP
        auto actionMasked = action;

        bool leftSide = x < m_game->GetGamesSize().width/2 ? true: false;

        // determine the kind of event it is
        switch (actionMasked) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN:
                RBLOG_2D("Pointer down", x, y);
                UserInput(leftSide, true, x, y);
                break;

            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
                RBLOG_2D("Pointer up", x, y);
                UserInput(leftSide, false, x, y);
                break;

            default:
                RBLOG_2D("Pointer move", x, y);
                break;
        }
    }

    // clear inputs, be careful as this will clear it for anyone listening to these events
    android_app_clear_motion_events(inputBuffer);
}
