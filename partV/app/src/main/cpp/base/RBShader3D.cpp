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
    "attribute vec4 vertexPosition;\n"
    "attribute vec3 vertexColor;\n"
    "uniform mat4 projectionMatrix;\n"
    "varying highp vec3 color;\n"

    "void main() {\n"
    " gl_Position = projectionMatrix * vertexPosition;\n"
    " color = vertexColor;\n"
    "}\n";

auto gFragmentShader3D =
"varying lowp vec3 color;\n"

"void main() {\n"
" gl_FragColor = vec4(color, 1);\n"
"}\n";

RBShader3D::RBShader3D()  {
    Create(gVertexShader3D, gFragmentShader3D);
}
