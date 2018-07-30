//
//  GameObject.hpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#pragma once

#include "RBVector2.hpp"

class GameObject {
public:
    GameObject();
    GameObject(RBVector2 position, RBVector2 size);
    GameObject(float x, float y, float width, float height);

    virtual void Update(float delay);
    virtual void Render();

    bool Collide(GameObject *object);

public:
    void SetSpeed(float x, float y) { _speed.x = x; _speed.y = y; }
    void SetSpeed(RBVector2 speed) { _speed = speed; }
    RBVector2 GetSpeed() { return _speed; }

    void SetPosition(float x, float y) { _position.x = x; _position.y = y; }
    RBVector2 GetPosition() { return _position; }
    
    RBVector2 GetSize() { return _size; }
    RBVector2 GetCenter() { RBVector2 center(_position.x+_size.width/2, _position.y+_size.height/2); return center; }
    
private:
    RBVector2 _position;
    RBVector2 _size;
    RBVector2 _speed;
};
