//
//  RBGameObject.cpp
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

#include <RBGameObject.hpp>
#include <RBRenderHelper.hpp>

bool RBGameObject::Collide(RBGameObject* object) {
    return object->GetPosition().x + object->GetSize().width > _position.x &&
           object->GetPosition().y + object->GetSize().height > _position.y &&
    _position.x + _size.x > object->GetPosition().x &&
    _position.y + _size.height > object->GetPosition().height;
}

RBGameObject::RBGameObject() {
    _speed.x = 0;
    _speed.y = 0;
    _color = RBColor(1);
}

RBGameObject::RBGameObject(RBVector2 position, RBVector2 size) {
    _position = position;
    _size = size;
}

RBGameObject::RBGameObject(float x, float y, float width, float height) {
    _position.x = x;
    _position.y = y;
    _size.width = width;
    _size.height = height;
}

void RBGameObject::Update(float delay) {
    _position.x += _speed.x*delay;
    _position.y += _speed.y*delay;
}

void RBGameObject::Render() {
    RBDrawRect(_position, _size, _color);
}
