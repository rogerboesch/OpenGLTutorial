//
//  GameObject.cpp
//
//  Created by Roger Boesch on 30.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "GameObject.hpp"
#include "RBRenderHelper.hpp"

// -----------------------------------------------------------------------------
#pragma mark - Collision

bool GameObject::Collide(GameObject* object) {
    return object->GetPosition().x + object->GetSize().width > _position.x &&
    object->GetPosition().y + object->GetSize().height > _position.y &&
    _position.x + _size.x > object->GetPosition().x &&
    _position.y + _size.height > object->GetPosition().height;
}

// -----------------------------------------------------------------------------
#pragma mark - Construction

GameObject::GameObject() {
    _speed.x = 0;
    _speed.y = 0;
}

GameObject::GameObject(RBVector2 position, RBVector2 size) {
    _position = position;
    _size = size;
}

GameObject::GameObject(float x, float y, float width, float height) {
    _position.x = x;
    _position.y = y;
    _size.width = width;
    _size.height = height;
}

// -----------------------------------------------------------------------------
#pragma mark - Render loop

void GameObject::Update(float delay) {
    _position.x += _speed.x*delay;
    _position.y += _speed.y*delay;
}

void GameObject::Render() {
    RBDrawRect(_position, _size);
}
