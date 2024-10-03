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

#include "RBGameObject.hpp"
#include "RBRenderHelper.hpp"
#include "RBLog.hpp"

bool RBGameObject::Collide(RBGameObject* object) {
    return object->GetPosition().x + object->GetSize().width > m_position.x &&
           object->GetPosition().y + object->GetSize().height > m_position.y &&
           m_position.x + m_size.x > object->GetPosition().x &&
           m_position.y + m_size.height > object->GetPosition().height;
}

RBGameObject::RBGameObject() {
    m_speed.x = 0;
    m_speed.y = 0;
    m_color = RBColorRed;
    m_tag = 0;
}

RBGameObject::RBGameObject(RBVec2D position, RBVec2D size) {
    m_position = position;
    m_size = size;
    m_speed = {0, 0};
    m_color = RBColorRed;
    m_tag = 0;
}

RBGameObject::RBGameObject(float x, float y, float width, float height) {
    m_position.x = x;
    m_position.y = y;
    m_size.width = width;
    m_size.height = height;
    m_speed = {0, 0};
    m_color = RBColorRed;
    m_tag = 0;
}

void RBGameObject::Update(float delta) {
    m_position.x += (m_speed.x * delta);
    m_position.y += (m_speed.y * delta);
}

void RBGameObject::Render() {
    RBRenderHelper::DrawRect(m_position, m_size, m_color);
}

void RBGameObject::Dump() {
    if (m_tag == 1) {
        RBLOG_4D("Pos/Speed", m_position.x, m_position.y, m_speed.x, m_speed.y);
    }
}