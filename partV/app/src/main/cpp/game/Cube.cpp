//
//  Cube.cpp
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

#include "Cube.hpp"
#include "RBGame.hpp"
#include "RBRenderer.hpp"
#include "RBRenderHelper.hpp"
#include "RBShader3D.hpp"

#include <stdio.h>

// Always define the global g_game in the derived game class
RBGame* g_game = new Cube();

// Choose a shader here
void Cube::CreateShader(RBRenderer* renderer) {
    auto shader = new RBShader3D();
    renderer->SetShader(shader);
}

#pragma mark - Render loop

void Cube::CreateContent() {
    m_cube = new RBCube();
    m_cube->SetSpeed({1.0, 1.0, 0.0});
    AddActor(m_cube);
}

void Cube::Update(float delay) {
}

void Cube::Render(RBShader* shader, RBMat4x4 projectionMatrix) {
    RBShader::ClearScreen(RBColorWhite);
}
