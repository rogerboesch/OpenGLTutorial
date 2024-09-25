//
//  RBGameActor.cpp
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

#include "RBGameActor.hpp"
#include "RBRenderHelper.hpp"

RBGameActor::RBGameActor() {
    m_position = { 0 };
    m_rotation = { 0 };
    m_rotationSpeed = { 0 };
    m_scale = { 1 };
    m_speed = { 0 };
    m_color = RBColorBlack;
}

RBGameActor::RBGameActor(RBVec3D position, RBVec3D size) {
    m_position = { 0 };
    m_rotation = { 0 };
    m_rotationSpeed = { 0 };
    m_scale = { 1 };
    m_speed = { 0 };
    m_color = RBColorBlack;

    m_position = position;
    m_scale = size;
}

void RBGameActor::Update(float delay) {
    m_position.x += m_speed.x * delay;
    m_position.y += m_speed.y * delay;
    m_position.z += m_speed.z * delay;

    m_rotation.x += m_rotationSpeed.x * delay;
    m_rotation.y += m_rotationSpeed.y * delay;
    m_rotation.z += m_rotationSpeed.z * delay;
}

bool RBGameActor::TestCollisionAABB(RBGameActor* actor) {
    RBVec3D myPosition = GetPosition();
    RBVec3D otherPosition = actor->GetPosition();
    RBVec3D mySize = GetSize();
    RBVec3D otherSize = actor->GetSize();

    // Check X-axis
    if (abs(myPosition.x - otherPosition.x) < mySize.x + otherSize.x) {
        // Check Y-axis
        if (abs(myPosition.y - otherPosition.y) < mySize.y + otherSize.y) {
            // Check Z-axis
            if (abs(myPosition.z - otherPosition.z) < mySize.z + otherSize.z) {
                //RB_LOG(Debug, "Position: %f,%f,%f <-> %f,%f,%f", myPosition.x, myPosition.y, myPosition.z, otherPosition.x, otherPosition.y, otherPosition.z);
                //RB_LOG(Debug, "Size: %f,%f,%f <-> %f,%f,%f", mySize.x, mySize.y, mySize.z, otherSize.x, otherSize.y, otherSize.z);

                return true;
            }
        }
    }

    return false;
}

RBVec3D RBGameActor::GetSize() {
    return RBVec3DMake(1.0*GetScale().x/2.0, 1.0*GetScale().y/2.0, 1.0*GetScale().z/2.0);
}

void RBGameActor::Dump() {
    /**
    RB_LOG(Debug, "------------ Dump of primitive #%03d -------------", (int)GetID());
    RB_LOG(Debug, "GLUid ID: %d,%d,%d,%d", _cubeVaoID, _cylinderVaoID, _coneVaoID, _pyramidVaoID);
    RB_LOG(Debug, "     Tag: %d", GetTag());
    RB_LOG(Debug, "  Hidden: %d", IsHidden());
    RB_LOG(Debug, "   Color: %f,%f,%f", _color[0], _color[1], _color[2]);
    RB_LOG(Debug, "   Shape: %d", _shape);
    RB_LOG(Debug, "Position: %f,%f,%f", _position.x, _position.y, _position.z);
    RB_LOG(Debug, "Rotation: %f,%f,%f", _rotation.x, _rotation.y, _rotation.z);
    RB_LOG(Debug, "   Scale: %f,%f,%f", _scale.x, _scale.y, _scale.z);
    RB_LOG(Debug, "   Speed: %f,%f,%f", _speed.x, _speed.y, _speed.z);
    RB_LOG(Debug, "RotSpeed: %f,%f,%f", _rotationSpeed.x, _rotationSpeed.y, _rotationSpeed.z);
    RB_LOG(Debug, "--------------------------------------------------");
     **/
}
