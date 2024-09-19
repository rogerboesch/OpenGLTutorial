//
//  RBGame.hpp
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

#pragma once

#include <vector>
#include <array>

#include <RBGameObject.hpp>

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

class RBGame
{
private:
    RBVector2 _gameSize;
    std::vector<RBGameObject*> *_gameObjects;
    std::array<bool, 8> _keyState;
    
public:
    RBGame();

    void OnInit(int width, int height);
    void OnUpdate(float delay);
    void OnRender();
    void OnKey(KeyType key, bool pressed);
   
public:
    bool KeyPressed(KeyType key) { return _keyState[key]; }
    RBVector2& GetGamesSize() { return _gameSize; }
    
public:
    void AddGameObject(RBGameObject *object);

protected:
    virtual void CreateContent() {}
    virtual void Update(float delay) {}
    virtual void Render() {}
};

