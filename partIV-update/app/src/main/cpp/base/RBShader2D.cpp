//
//  RBShader2D.cpp
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

#include <RBShader2D.hpp>
#include <cstdlib>

auto gVertexShader =
        "attribute vec4 vPosition;\n"
        "uniform float fWidth;\n"
        "uniform float fHeight;\n"

        "void main() {\n"
        "  mat4 projectionMatrix = mat4(2.0/fWidth, 0.0, 0.0, -1.0,\n"
        "                              0.0, 2.0/fHeight, 0.0, -1.0,\n"
        "                              0.0, 0.0, -1.0, 0.0,\n"
        "                              0.0, 0.0, 0.0, 1.0);\n"

        "  gl_Position = vPosition;\n"
        "  gl_Position *= projectionMatrix;\n"
        "}\n";

auto gFragmentShader =
        "precision mediump float;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "}\n";

RBShader2D::RBShader2D() : m_gl_position(-1), m_gl_width(-1), m_gl_height(-1) {
    if (Create(gVertexShader, gFragmentShader)) {
        m_gl_position = AssignAttribute("vPosition");
        m_gl_width = AssignUniform("fWidth");
        m_gl_height = AssignUniform("fHeight");
    }
}

void RBShader2D::MapSize(int width, int height) {
    MapUniform(m_gl_width, width);
    MapUniform(m_gl_height, height);
}