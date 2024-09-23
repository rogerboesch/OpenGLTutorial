//
//  RBShader3D.cpp
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

#include <RBShader3D.hpp>
#include <cstdlib>

auto gVertexShader3D =
        "attribute vec3 coordinate;\n"
        "uniform mat4 projection;\n"
        "uniform vec4 color;\n"

        "void main(void) {\n"
        "  gl_Position =  projection * vec4(coordinate, 1);\n"
        "}\n";

auto gFragmentShader3D =
        "precision mediump float;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "}\n";

RBShader3D::RBShader3D()  {
    Create(gVertexShader3D, gFragmentShader3D);
}
