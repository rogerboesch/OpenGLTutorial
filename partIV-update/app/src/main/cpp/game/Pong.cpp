//
//  Pong.cpp
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

#include "Pong.hpp"
#include "RBRenderHelper.hpp"
#include "RBGame.hpp"
#include "RBMath.hpp"

#include <stdio.h>

#define kBALL_SIZE 8.0f
#define kBALL_SPEED 300.0f
#define kBALL_SPEED_MAX 300.0f

#define kPADDLE_HEIGHT 50.0f
#define kPADDLE_SPEED 600.0f

// Always define the global gGame in the derived game class
RBGame* gGame = new Pong();

// Test only
RBShader* s_shader = nullptr;

RBShader* Pong::CreateShader() {
   s_shader = new RBShader2D();
   return s_shader;
}

#pragma mark - Render loop

void Pong::CreateContent() {
    RBVec2D size = GetGamesSize();

    m_score1 = 0;
    m_score2 = 0;

    m_ball = new RBGameObject(size.width/2-kBALL_SIZE/2, size.height/2-kBALL_SIZE/2, kBALL_SIZE, kBALL_SIZE);
    m_ball->SetSpeed(kBALL_SPEED, 0);
    m_ball->SetColor(RBColorBlack);
    AddGameObject(m_ball);

    m_paddle1 = new RBGameObject(30, size.height/2-kPADDLE_HEIGHT/2, 10, kPADDLE_HEIGHT);
    m_paddle1->SetColor(RBColorBlack);
    AddGameObject(m_paddle1);

    m_paddle2 = new RBGameObject(size.width-40, size.height/2-kPADDLE_HEIGHT/2, 10, kPADDLE_HEIGHT);
    m_paddle2->SetColor(RBColorBlack);
    AddGameObject(m_paddle2);
}

void Pong::Update(float delay) {
    RBVec2D size = GetGamesSize();

    // Paddle 1 control
    if (KeyPressed(keyW)) {
        m_paddle1->SetSpeed(0, kPADDLE_SPEED);
    }
    else if (KeyPressed(keyS)) {
        m_paddle1->SetSpeed(0, -kPADDLE_SPEED);
    }
    else {
        m_paddle1->SetSpeed(0, 0);
    }

    // Paddle 2 control
    if (KeyPressed(keyUp)) {
        m_paddle2->SetSpeed(0, kPADDLE_SPEED);
    }
    else if (KeyPressed(keyDown)) {
        m_paddle2->SetSpeed(0, -kPADDLE_SPEED);
    }
    else {
        m_paddle2->SetSpeed(0, 0);
    }

    // Ball control
    if (m_paddle1->Collide(m_ball)) {
        RBVec2D speed = m_ball->GetSpeed();
        speed.x *= -1.1;
        
        float diff = (m_ball->GetCenter().y - m_paddle1->GetCenter().y)*2;
        speed.y = speed.y + diff;

        m_ball->SetSpeed(speed);
    }
    else if (m_paddle2->Collide(m_ball)) {
        RBVec2D speed = m_ball->GetSpeed();
        speed.x *= -1.1;

        float diff = (m_ball->GetCenter().y - m_paddle2->GetCenter().y)*2;
        speed.y = speed.y + diff;

        m_ball->SetSpeed(speed);
    }
    
    if (m_ball->GetPosition().y <= 0 || m_ball->GetPosition().y >= size.height-m_ball->GetSize().height) {
        RBVec2D speed = m_ball->GetSpeed();
        speed.y *= -1.1;
        m_ball->SetSpeed(speed);
    }

    // Limit ball speed
    LimitBallSpeed();
    
    // Check Ball
    if (m_ball->GetPosition().x <= 0) {
        m_score2++;
        Reset(1);
    }
    else if (m_ball->GetPosition().x >= size.width) {
        m_score1++;
        Reset(-1);
    }
}

void Pong::Render() {
    RBClearScreen(RBColorWhite);
    RBEnableBlending();

    RBVec2D size = GetGamesSize();

    // Draw center
    RBDrawRect(size.width/2-2, 0, 4, size.height, RBColorBlack);

    // Draw HUD
    RBDrawNumber(size.width/2-160, size.height-80, m_score1, RBColorBlack);
    RBDrawNumber(size.width/2+130, size.height-80, m_score2, RBColorBlack);
}

// -----------------------------------------------------------------------------
#pragma mark - Helper methods

void Pong::Reset(int direction) {
    RBVec2D size = GetGamesSize();

    m_ball->SetPosition(size.width/2-5, size.height/2-5);
    m_ball->SetSpeed(kBALL_SPEED*direction, 0);
    
    if (m_score1 > 9 || m_score2 > 9) {
        m_score1 = 0;
        m_score2 = 0;
    }
}

void Pong::LimitBallSpeed() {
    RBVec2D speed = m_ball->GetSpeed();

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

    m_ball->SetSpeed(speed);
}
