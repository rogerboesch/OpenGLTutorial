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
#include "RBRenderHelper.hpp"
#include "RBGame.hpp"
#include "RBShader3D.hpp"
#include "stdio.h"

// Always define the global gGame in the derived game class
RBGame* gGame = new Cube();

RBShader* Cube::CreateShader() {
    return new RBShader3D();
}

#pragma mark - Render loop

void Cube::CreateContent() {
}

void Cube::Update(float delay) {
}

void Cube::Render() {
    RBClearScreen(RBColorWhite);
    RBEnableBlending();
}
