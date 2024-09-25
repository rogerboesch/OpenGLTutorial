//
//  RBCube.cpp
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

#include "RBCube.hpp"

float vertices[] = {
        // Front face
        0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
        -0.5, -0.5,  0.5,
        0.5, -0.5,  0.5,

        // Back face
        0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
};

float vertex_colors[] = {
        1.0, 0.4, 0.6,
        1.0, 0.9, 0.2,
        0.7, 0.3, 0.8,
        0.5, 0.3, 1.0,

        0.2, 0.6, 1.0,
        0.6, 1.0, 0.4,
        0.6, 0.8, 0.8,
        0.4, 0.8, 0.8,
};

unsigned short triangle_indices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Right
        0, 3, 7,
        7, 4, 0,

        // Bottom
        2, 6, 7,
        7, 3, 2,

        // Left
        1, 5, 6,
        6, 2, 1,

        // Back
        4, 7, 6,
        6, 5, 4,

        // Top
        5, 1, 0,
        0, 4, 5,
};

const unsigned int vertices_index = 0;
const unsigned int colors_index = 1;

GLuint RBCube::s_cubeVaoID = -1;

RBCube::RBCube() : RBGameActor() {
}

void RBCube::CreateVAO() {
    if (s_cubeVaoID != -1) return;

    glGenVertexArrays(1, &s_cubeVaoID);
    glBindVertexArray(s_cubeVaoID);

    unsigned int triangles_ebo;
    glGenBuffers(1, &triangles_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof triangle_indices, triangle_indices, GL_STATIC_DRAW);

    unsigned int vertices_vbo;
    glGenBuffers(1, &vertices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vertices_index, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vertices_index);

    unsigned int colors_vbo;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertex_colors, vertex_colors, GL_STATIC_DRAW);

    glVertexAttribPointer(colors_index, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(colors_index);

    // Unbind to prevent accidental modification
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // RB_LOG(Debug, "RBCube %lu added", GetID());
}

void RBCube::RenderInternal(RBShader* shader, RBMat4x4 projectionMatrix) {
    if (s_cubeVaoID == -1) {
        CreateVAO();
    }

	RBMat4x4 t = GetTransform();
	RBMat4x4 mat = RBMatrixMultiplyMatrix(projectionMatrix, t);

	shader->Activate(true);

	shader->ApplyColor(GetColor());
	shader->ApplyProjectionMatrix(mat);
	shader->DrawVAO(s_cubeVaoID, 14);
}

void RBCube::Render(RBShader* shader, RBMat4x4 projectionMatrix) {
	if (IsHidden()) return;

	RBMat4x4 matT = RBMatrixMakeTranslation(GetPosition().x, GetPosition().x, GetPosition().z);
	RBMat4x4 matS = RBMatrixMakeScale(GetScale().x, GetScale().y, GetScale().z);
	RBMat4x4 matRX = RBMatrixMakeRotationX(DEG_TO_RAD(GetRotation().x));
	RBMat4x4 matRY = RBMatrixMakeRotationY(DEG_TO_RAD(GetRotation().x));
	RBMat4x4 matRZ = RBMatrixMakeRotationZ(DEG_TO_RAD(GetRotation().z));

	RBMat4x4 mat = RBMatrixMultiplyMatrix(matT, matS);
	mat = RBMatrixMultiplyMatrix(mat, matRX);
	mat = RBMatrixMultiplyMatrix(mat, matRY);
	mat = RBMatrixMultiplyMatrix(mat, matRZ);

	SetTransform(mat);

	RenderInternal(shader, projectionMatrix);
}

