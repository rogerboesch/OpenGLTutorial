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

#include <RBMath.hpp>
#include <RBColor.hpp>

class RBGameObject {
public:
    RBGameObject();
    RBGameObject(RBVec2D position, RBVec2D size);
    RBGameObject(float x, float y, float width, float height);

    virtual void Update(float delay);
    virtual void Render();

    bool Collide(RBGameObject *object);

public:
    void SetSpeed(float x, float y) { m_speed.x = x; m_speed.y = y; }
    void SetSpeed(RBVec2D speed) { m_speed = speed; }
    RBVec2D GetSpeed() { return m_speed; }

    void SetPosition(float x, float y) { m_position.x = x; m_position.y = y; }
    RBVec2D GetPosition() { return m_position; }

    RBVec2D GetSize() { return m_size; }
    RBVec2D GetCenter() { return {m_position.x + m_size.w / 2, m_position.y + m_size.h / 2}; }

    void SetColor(float r, float g, float b, float a) { m_color.r = r; m_color.g = g; m_color.b = b; m_color.a = a; }
    void SetColor(RBColor color) { m_color.r = color.r; m_color.g = color.g; m_color.b = color.b; m_color.a = color.a; }
    RBColor GetColor() { return m_color; }

private:
    RBVec2D m_position;
    RBVec2D m_size;
    RBVec2D m_speed;
    RBColor m_color;
};
