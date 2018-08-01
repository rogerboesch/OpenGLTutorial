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

#define kBALL_SIZE 8.0f
#define kBALL_SPEED 300.0f
#define kBALL_SPEED_MAX 300.0f

#define kPADDLE_HEIGHT 50.0f
#define kPADDLE_SPEED 600.0f

// Always define the global gGame in the derived game class
Game* gGame = new Pong();

// -----------------------------------------------------------------------------
#pragma mark - Render loop

void Pong::CreateContent() {
    RBVector2 size = GetGamesSize();
    
    _score1 = 0;
    _score2 = 0;

    _ball = new GameObject(size.width/2-kBALL_SIZE/2, size.height/2-kBALL_SIZE/2, kBALL_SIZE, kBALL_SIZE);
    _ball->SetSpeed(kBALL_SPEED, 0);
    _ball->SetColor(1, 1, 1, 1);
    AddGameObject(_ball);
    
    _paddle1 = new GameObject(30, size.height/2-kPADDLE_HEIGHT/2, 10, kPADDLE_HEIGHT);
    _paddle1->SetColor(1, 1, 1, 1);
    AddGameObject(_paddle1);

    _paddle2 = new GameObject(size.width-40, size.height/2-kPADDLE_HEIGHT/2, 10, kPADDLE_HEIGHT);
    _paddle2->SetColor(1, 1, 1, 1);
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
        
        float diff = (_ball->GetCenter().y - _paddle1->GetCenter().y)*2;
        speed.y = speed.y + diff;

        _ball->SetSpeed(speed);
    }
    else if (_paddle2->Collide(_ball)) {
        RBVector2 speed  =_ball->GetSpeed();
        speed.x *= -1.1;

        float diff = (_ball->GetCenter().y - _paddle2->GetCenter().y)*2;
        speed.y = speed.y + diff;

        _ball->SetSpeed(speed);
    }
    
    if (_ball->GetPosition().y <= 0 || _ball->GetPosition().y >= size.height-_ball->GetSize().height) {
        RBVector2 speed  =_ball->GetSpeed();
        speed.y *= -1.1;
        _ball->SetSpeed(speed);
    }

    // Limit ball speed
    LimitBallSpeed();
    
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
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    RBVector2 size = GetGamesSize();

    RBColor white(1);
    RBColor ltGray(1,1,1,0.2);

    // Draw center
    RBDrawRect(size.width/2-2, 0, 4, size.height, ltGray);

    // Draw HUD
    RBDrawNumber(size.width/2-160, size.height-80, _score1, white);
    RBDrawNumber(size.width/2+130, size.height-80, _score2, white);
}

// -----------------------------------------------------------------------------
#pragma mark - Helper methods

void Pong::Reset(int direction) {
    RBVector2 size = GetGamesSize();

    _ball->SetPosition(size.width/2-5, size.height/2-5);
    _ball->SetSpeed(kBALL_SPEED*direction, 0);
    
    if (_score1 > 9 || _score2 > 9) {
        _score1 = 0;
        _score2 = 0;
    }
}

void Pong::LimitBallSpeed() {
    RBVector2 speed = _ball->GetSpeed();

    if (speed.x > kBALL_SPEED_MAX) {
        speed.x = kBALL_SPEED_MAX;
    }
    else if (speed.x < -kBALL_SPEED_MAX) {
        speed.x = -kBALL_SPEED_MAX;
    }

    if (speed.y > kBALL_SPEED_MAX) {
        speed.y = kBALL_SPEED_MAX;
    }
    else if (speed.y < -kBALL_SPEED_MAX) {
        speed.y = -kBALL_SPEED_MAX;
    }
    
    _ball->SetSpeed(speed);
}
