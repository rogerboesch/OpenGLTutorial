//
//  Game.cpp
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "Game.hpp"
#include "GameObject.hpp"

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
    
    Enable2D();
    
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

// -----------------------------------------------------------------------------
#pragma mark - Helper method

void Game::Enable2D() {
    glViewport(0, 0, _gameSize.width, _gameSize.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, _gameSize.width, 0.0f, _gameSize.height, 0.0f, 1.0f);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}
