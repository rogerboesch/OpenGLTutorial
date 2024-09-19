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
    _gameObjects->push_back(object);
}

RBGame::RBGame() {
    _gameObjects = new std::vector<RBGameObject*>();
}

void RBGame::OnKey(KeyType key, bool pressed) {
    _keyState[key] = pressed;
}

void RBGame::OnInit(int width, int height) {
    _gameSize.width = width;
    _gameSize.height = height;
    
    _keyState.fill(false);
    
    RBEnable2D(_gameSize);
    
    // Create content
    CreateContent();
}

void RBGame::OnUpdate(float delay) {
    Update(delay);
    
    for (auto i: *_gameObjects) {
        i->Update(delay);
    }
}

void RBGame::OnRender() {
    Render();
    
    for (auto i: *_gameObjects) {
        i->Render();
    }
}
