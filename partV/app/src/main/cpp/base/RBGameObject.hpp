//
//  RBGameObject.hpp
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

#include <RBVector2.hpp>
#include <RBColor.hpp>

class RBGameObject {
public:
    RBGameObject();
    RBGameObject(RBVector2 position, RBVector2 size);
    RBGameObject(float x, float y, float width, float height);

    virtual void Update(float delay);
    virtual void Render();

    bool Collide(RBGameObject *object);

public:
    void SetSpeed(float x, float y) { _speed.x = x; _speed.y = y; }
    void SetSpeed(RBVector2 speed) { _speed = speed; }
    RBVector2 GetSpeed() { return _speed; }

    void SetPosition(float x, float y) { _position.x = x; _position.y = y; }
    RBVector2 GetPosition() { return _position; }
    
    RBVector2 GetSize() { return _size; }
    RBVector2 GetCenter() { RBVector2 center(_position.x+_size.width/2, _position.y+_size.height/2); return center; }

    void SetColor(float r, float g, float b, float a) { _color.r = r; _color.g = g; _color.b = b; _color.a = a; }
    void SetColor(RBColor color) { _color.r = color.r; _color.g = color.g; _color.b = color.b; _color.a = color.a; }
    RBColor GetColor() { return _color; }

private:
    RBVector2 _position;
    RBVector2 _size;
    RBVector2 _speed;
    RBColor _color;
};
