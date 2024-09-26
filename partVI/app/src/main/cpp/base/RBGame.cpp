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

#include <RBGame.hpp>
#include <RBGameObject.hpp>
#include <RBRenderHelper.hpp>

void RBGame::AddGameObject(RBGameObject *object) {
    m_gameObjects->push_back(object);
}

RBGame::RBGame() {
    m_gameObjects = new std::vector<RBGameObject*>();
}

void RBGame::OnKey(KeyType key, bool pressed) {
    m_keyState[key] = pressed;
}

void RBGame::OnInit(RBRenderer* render) {
    m_render = render;

    m_gameSize.width = 0;
    m_gameSize.height = 0;
    
    m_keyState.fill(false);
}

void RBGame::OnUpdate(float delay) {
    Update(delay);
    
    for (auto i: *m_gameObjects) {
        i->Update(delay);
    }
}

void RBGame::OnRender() {
    Render();
    
    for (auto i: *m_gameObjects) {
        i->Render();
    }
}
