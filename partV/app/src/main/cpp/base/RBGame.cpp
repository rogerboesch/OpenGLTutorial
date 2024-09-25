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
#include "RBGameActor.hpp"
#include "RBRenderHelper.hpp"
#include "RBRenderer.hpp"

void RBGame::AddActor(RBGameActor *object) {
    m_actors->push_back(object);
}

RBGame::RBGame() {
    m_actors = new std::vector<RBGameActor*>();
}

void RBGame::OnKey(KeyType key, bool pressed) {
    m_keyState[key] = pressed;
}

void RBGame::OnInit(RBRenderer* renderer) {
    m_renderer = renderer;
    CreateShader(m_renderer);

    m_gameSize.w = 0;
    m_gameSize.h = 0;
    
    m_keyState.fill(false);
}

void RBGame::OnUpdate(float delay) {
    Update(delay);
    
    for (auto i: *m_actors) {
        i->Update(delay);
    }
}

void RBGame::OnRender() {
    auto shader = m_renderer->GetShader();
    if (shader == nullptr) return;

    Render(shader, m_renderer->GetProjectionMatrix());
    
    for (auto i: *m_actors) {
        i->Render(shader, m_renderer->GetProjectionMatrix());
    }
}
