//  Pong.hpp
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

#include <RBGame.hpp>

class Pong : public RBGame {
private:
    RBGameObject* _ball;
    RBGameObject* _paddle1;
    RBGameObject* _paddle2;

    int _score1;
    int _score2;
    
private:
    void Reset(int direction);
    void LimitBallSpeed();

protected:
    virtual void CreateContent();
    virtual void Update(float delay);
    virtual void Render();
};
