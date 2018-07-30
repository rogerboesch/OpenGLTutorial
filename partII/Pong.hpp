//
//  Pong.hpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#include "Game.hpp"

class Pong : public Game {
private:
    GameObject* _ball;
    GameObject* _paddle1;
    GameObject* _paddle2;

    int _score1;
    int _score2;
    
private:
    void Reset(int direction);

protected:
    virtual void CreateContent();
    virtual void Update(float delay);
    virtual void Render();
};
