//
//  Game.cpp
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "Game.hpp"
#include "GameObject.hpp"
#include "RBRenderHelper.hpp"

// -----------------------------------------------------------------------------
#pragma mark - Game object related

void Game::AddGameObject(GameObject *object) {
    _gameObjects->push_back(object);
}

// -----------------------------------------------------------------------------
#pragma mark - Construction / Destruction

Game::Game() {
    _gameObjects = new std::vector<GameObject*>();
}

// -----------------------------------------------------------------------------
#pragma mark - Render loop

void Game::OnKey(KeyType key, bool pressed) {
    _keyState[key] = pressed;
}

void Game::OnInit(int width, int height) {
    _gameSize.width = width;
    _gameSize.height = height;
    
    _keyState.fill(false);
    
    RBEnable2D(_gameSize);
    
    // Create content
    CreateContent();
}

void Game::OnUpdate(float delay) {
    Update(delay);
    
    for (auto i: *_gameObjects) {
        i->Update(delay);
    }
}

void Game::OnRender() {
    Render();
    
    for (auto i: *_gameObjects) {
        i->Render();
    }
}
