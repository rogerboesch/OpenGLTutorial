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
#include "RBRenderHelper.hpp"
#include "RBGame.hpp"
#include "RBMath.hpp"

#include <stdio.h>

// Always define the global gGame in the derived game class
RBGame* gGame = new Cube3D();

#pragma mark - Render loop

void Cube3D::CreateContent() {
}

void Cube3D::Update(float delay) {
}

void Cube3D::Render() {
    RBClearScreen(RBColorRed);
    RBEnableBlending();
}
