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

#include "RBGameObject.hpp"

#include <vector>
#include <array>

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

class RBRenderer;

class RBGame {
public:
    RBGame();

    void OnInit(RBRenderer* render);
    void OnUpdate(float delay);
    void OnRender();
    void OnKey(KeyType key, bool pressed);

    virtual void CreateContent() {}

public:
    bool KeyPressed(KeyType key) { return m_keyState[key]; }
    RBVec2D& GetGamesSize() { return m_gameSize; }
    void SetGameSize(int w, int h) { m_gameSize.width = w;m_gameSize.height = h; }

public:
    void AddGameObject(RBGameObject *object);

protected:
    virtual void Update(float delay) = 0;
    virtual void Render() = 0;

private:
    RBVec2D m_gameSize;
    std::vector<RBGameObject*> *m_gameObjects = nullptr;
    std::array<bool, 8> m_keyState;
    RBRenderer* m_render = nullptr;
};

