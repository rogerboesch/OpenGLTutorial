//  Cube3D.hpp
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

class Cube3D : public RBGame {
public:
    void CreateContent() override;

protected:
    void Update(float delay) override;
    void Render() override;
    void SizeChanged() override ;

private:
    float m_offsetZ1 = 0.0f;
    float m_offsetZ2 = 0.0f;
    float m_totalTime = 0.0f;
};
