//
//  RBGameActor.hpp
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

#include "RBMath.hpp"
#include "RBColor.hpp"
#include "RBShader.hpp"

class RBGameActor {
public:
    RBGameActor();
    RBGameActor(RBVec3D position, RBVec3D size);

    virtual void Update(float delay);
    virtual void Render(RBShader* shader, RBMat4x4 projectionMatrix) {}

    virtual bool TestCollisionAABB(RBGameActor* actor);

    void Dump();

// Transform
protected:
    void SetTransform(RBMat4x4 mat) { m_transform = mat; }

public:
    RBMat4x4 GetTransform() { return m_transform; }

    void SetPosition(RBVec3D position) { m_position = position; }
    RBVec3D GetPosition() { return m_position; }

    RBVec3D GetScale() { return m_scale; }
    RBVec3D GetSize();
    RBVec3D GetCenter() { return {m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_position.z + m_scale.z / 2}; }

    void SetRotation(RBVec3D rotation) { m_rotation = rotation; }
    RBVec3D GetRotation() { return m_rotation; }

    void SetSpeed(RBVec3D speed) { m_speed = speed; }
    RBVec3D GetSpeed() { return m_speed; }

    void SetRotationSpeed(RBVec3D speed) { m_rotationSpeed = speed; }
    RBVec3D GetRotationSpeed() { return m_rotationSpeed; }

    void RotateTo(RBVec3D vector);
    void ScaleTo(float scale);

// Material
public:
    void SetColor(RBColor color) { m_color.r = color.r; m_color.g = color.g; m_color.b = color.b; m_color.a = color.a; }
    RBColor GetColor() { return m_color; }

// Other
public:
    void SetHidden(bool hidden) { m_hidden = hidden; }
    bool IsHidden() { return m_hidden; }

private:
    RBMat4x4 m_transform;       // Saved for optimisation purposes

    RBVec3D m_position;
    RBVec3D m_scale;
    RBVec3D m_speed;
    RBVec3D m_rotation;         // Stored as degrees
    RBVec3D m_rotationSpeed;
    RBColor m_color;
    bool m_hidden;
};
