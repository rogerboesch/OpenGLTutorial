//
//  RBGame.cpp
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
#include "RBGameObject.hpp"
#include "RBRenderer.hpp"
#include "RBRenderHelper.hpp"
#include "RBShader.hpp"
#include "RBLog.hpp"

void RBGame::AddGameObject(RBGameObject *object) {
    m_gameObjects->push_back(object);
}

RBGame::RBGame() {
    m_renderer = nullptr;

    m_gameSize.width = 0;
    m_gameSize.height = 0;
    m_keyState.fill(false);

    m_gameObjects = new std::vector<RBGameObject*>();
}

RBShader* RBGame::GetShader() {
    return m_renderer->GetShader();
}

void RBGame::ProcessKey(KeyType key, bool pressed) {
    m_keyState[key] = pressed;
}

void RBGame::Initialize(RBRenderer* renderer) {
    m_renderer = renderer;
    m_clock.Reset();
}

void RBGame::Frame() {
    float delta = m_clock.Delta();
    OnUpdate(delta);

    for (auto i: *m_gameObjects) {
        i->Update(delta);
    }

    OnRender();
    
    for (auto i: *m_gameObjects) {
        i->Render();
    }
}
