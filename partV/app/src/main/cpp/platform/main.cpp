//
//  main.cpp
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

#include "RBRenderer.hpp"
#include "RBLog.hpp"

#include <jni.h>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            pApp->userData = new RBRenderer(pApp);  // Create renderer
            break;
        case APP_CMD_TERM_WINDOW:
            if (pApp->userData) {
                //
                auto *pRenderer = reinterpret_cast<RBRenderer *>(pApp->userData);
                pApp->userData = nullptr;
                delete pRenderer;   // Destroy renderer
            }
            break;
        default:
            break;
    }
}

void android_main(struct android_app *pApp) {
    // Can be removed, useful to ensure your code is running
    RBLOG("Welcome to android_main");

    pApp->onAppCmd = handle_cmd;

    int events;
    android_poll_source *pSource;

    do {
        // Handle events
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }

        // Call renderer
        if (pApp->userData) {
            auto *pRenderer = reinterpret_cast<RBRenderer *>(pApp->userData);

            pRenderer->HandleInput();   // Handle user input
            pRenderer->RenderFrame();   // Render a frame
        }
    } while (!pApp->destroyRequested);  // Quit if requested
}

}