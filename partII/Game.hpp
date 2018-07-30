//
//  Game.hpp
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#include <vector>
#include <array>

#include "GameObject.hpp"

#define kFRAMES_PER_SECOND 60

enum KeyType {
    keyUp = 0,
    keyLeft,
    keyDown,
    keyRight,
    keyW,
    keyA,
    keyS,
    keyD,
};

class Game
{
private:
    RBVector2 _gameSize;
    std::vector<GameObject*> *_gameObjects;
    std::array<bool, 8> _keyState;
    
public:
    Game();

    void OnInit(int width, int height);
    void OnUpdate(float delay);
    void OnRender();
    void OnKey(KeyType key, bool pressed);
    void Enable2D();
   
public:
    bool KeyPressed(KeyType key) { return _keyState[key]; }
    RBVector2& GetGamesSize() { return _gameSize; }
    
public:
    void AddGameObject(GameObject *object);

protected:
    virtual void CreateContent() {}
    virtual void Update(float delay) {}
    virtual void Render() {}
};

