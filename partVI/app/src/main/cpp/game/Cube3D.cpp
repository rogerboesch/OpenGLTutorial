//
//  Cube3D.cpp
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

#include "Cube3D.hpp"
#include "RBRenderer.hpp"
#include "RBRenderHelper.hpp"
#include "RBGame.hpp"
#include "RBMath.hpp"
#include "RBShader.hpp"
#include "RBLog.hpp"

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <stdio.h>

extern GLint s_gl_position;

// Always define the global gGame in the derived game class
RBGame* gGame = new Cube3D();

extern RBRenderer* gRender;

void Cube3D::CreateContent() {
    RBLOG("Cube3D::CreateContent()");
}

void Cube3D::SizeChanged() {
    RBLOG("Cube3D::SizeChanged()");

    auto shader = gRender->GetShader();
    shader->Activate();

    auto size = gGame->GetGamesSize();
    float aspect = std::max(1.0f, size.width/size.height);
    RBMat4x4 perspective = RBMatrixMakeProjection3D(45.0f, aspect, 0.1f, 200.0f);
    shader->MapProjectionMatrix(perspective);
}

void Cube3D::Update(float delay) {
    m_totalTime += delay;

    if (KeyPressed(keyW)) {
        m_offsetZ1 += 0.15f;
    }
    else if (KeyPressed(keyS)) {
        m_offsetZ1 -= 0.15f;
    }

    if (KeyPressed(keyUp)) {
        m_offsetZ2 += 0.15f;
    }
    else if (KeyPressed(keyDown)) {
        m_offsetZ2 -= 0.15f;
    }
}

void Cube3D::Render() {
    RBClearScreen(RBColorBlack);
    RBEnableBlending();

    float rotate = m_totalTime * 0.03f;

    RBDrawCube({-1.5f, 0.0f, -(5.0f+m_offsetZ1)}, {0.0f, -rotate, 0.0f}, {1.0f,1.0f,1.0f}, RBColorRed);
    RBDrawCube({1.5f, 0.0f, -(5.0f+m_offsetZ2)}, {0.0f, rotate, 0.0f}, {1.0f,1.0f,1.0f}, RBColorGreen);
}
