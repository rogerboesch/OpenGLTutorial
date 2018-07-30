//
//  Pong.cpp
//  partII
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "Pong.hpp"
#include "RBRenderHelper.hpp"
#include "stdio.h"

#define kBALL_SPEED 200.0f
#define kPADDLE_SPEED 400.0f

// Always define the global gGame in the derived game class
Game* gGame = new Pong();

void Pong::CreateContent() {
    RBVector2 size = GetGamesSize();
    
    _ball = new GameObject(size.width/2-5, size.height/2-5, 10, 10);
    _ball->SetSpeed(kBALL_SPEED, 0);
    AddGameObject(_ball);
    
    _paddle1 = new GameObject(0, size.height/2-50, 10, 100);
    AddGameObject(_paddle1);

    _paddle2 = new GameObject(size.width-10, size.height/2-50, 10, 100);
    AddGameObject(_paddle2);
}

void Pong::Update(float delay) {
    RBVector2 size = GetGamesSize();

    // Paddle 1 control
    if (KeyPressed(keyW)) {
        _paddle1->SetSpeed(0, kPADDLE_SPEED);
    }
    else if (KeyPressed(keyS)) {
        _paddle1->SetSpeed(0, -kPADDLE_SPEED);
    }
    else {
        _paddle1->SetSpeed(0, 0);
    }

    // Paddle 2 control
    if (KeyPressed(keyUp)) {
        _paddle2->SetSpeed(0, kPADDLE_SPEED);
    }
    else if (KeyPressed(keyDown)) {
        _paddle2->SetSpeed(0, -kPADDLE_SPEED);
    }
    else {
        _paddle2->SetSpeed(0, 0);
    }

    // Ball control
    if (_paddle1->Collide(_ball)) {
        RBVector2 speed  =_ball->GetSpeed();
        speed.x *= -1.1;
        
        float diff = (_ball->GetCenter().y - _paddle1->GetCenter().y);
        speed.y = speed.y + diff;

        _ball->SetSpeed(speed);
    }
    else if (_paddle2->Collide(_ball)) {
        RBVector2 speed  =_ball->GetSpeed();
        speed.x *= -1.1;

        float diff = (_ball->GetCenter().y - _paddle2->GetCenter().y);
        speed.y = speed.y + diff;

        _ball->SetSpeed(speed);
    }
    
    if (_ball->GetPosition().y <= 0 || _ball->GetPosition().y >= size.height-_ball->GetSize().height) {
        RBVector2 speed  =_ball->GetSpeed();
        speed.y *= -1.1;
        _ball->SetSpeed(speed);
    }
    
    // Check Ball
    if (_ball->GetPosition().x <= 0) {
        _score2++;
        Reset(1);
    }
    else if (_ball->GetPosition().x >= size.width) {
        _score1++;
        Reset(-1);
    }
}

void Pong::Render() {
    RBVector2 size = GetGamesSize();

    // Draw HUD
    RBDrawNumber(size.width/2-40, size.height-80, _score1);
    RBDrawNumber(size.width/2+10, size.height-80, _score2);

    RBDrawRect(size.width/2-2, size.height-45, 5, 5);
    RBDrawRect(size.width/2-2, size.height-65, 5, 5);
}


void Pong::Reset(int direction) {
    RBVector2 size = GetGamesSize();

    _ball->SetPosition(size.width/2-5, size.height/2-5);
    _ball->SetSpeed(kBALL_SPEED*direction, 0);
    
    if (_score1 > 9 || _score2 > 9) {
        _score1 = 0;
        _score2 = 0;
    }
}
