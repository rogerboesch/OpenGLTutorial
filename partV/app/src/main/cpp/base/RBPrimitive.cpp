//
//  RBPrimitive.cpp
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

#include "RBPrimitive.hpp"

#define NUM_STEPS 30

static const GLfloat verticesCube[] = {
   -0.5f, 0.5f, 0.5f,     //  0: Front-top-left
   0.5f, 0.5f, 0.5f,      //  1: Front-top-right
   -0.5f, -0.5f, 0.5f,    //  2: Front-bottom-left
   0.5f, -0.5f, 0.5f,     //  3: Front-bottom-right
   0.5f, -0.5f, -0.5f,    //  4: Back-bottom-right
   0.5f, 0.5f, 0.5f,      //  5: Front-top-right
   0.5f, 0.5f, -0.5f,     //  6: Back-top-right
   -0.5f, 0.5f, 0.5f,     //  7: Front-top-left
   -0.5f, 0.5f, -0.5f,    //  8: Back-top-left
   -0.5f, -0.5f, 0.5f,    //  9: Front-bottom-left
   -0.5f, -0.5f, -0.5f,   // 10: Back-bottom-left
   0.5f, -0.5f, -0.5f,    // 11: Back-bottom-right
   -0.5f, 0.5f, -0.5f,    // 12: Back-top-left
   0.5f, 0.5f, -0.5f      // 13: Back-top-right
};

GLint RBPrimitive::s_cubeVaoID = -1;

RBPrimitive::RBPrimitive() : RBGameActor() {
	m_shape = Cube;

	// RB_LOG(Debug, "RBPrimitive %lu added", GetID());
}

GLint RBPrimitive::CreateVAO(RBShader* shader, GLfloat* vertices, int size) {
	GLuint vao = -1;

	glGenVertexArrays(1, &vao);

	shader->Activate();
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	GLint location = shader->GetAttribute("vertexPosition");

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glUseProgram(0);

	// RB_LOG(Debug, "Create vertex array buffer (VBO) for location '%d' in primitive '%lu'", vao, GetID());

	return vao;
}

void RBPrimitive::CreateAllVAOs(RBShader* shader) {
	s_cubeVaoID = CreateVAO(shader, (GLfloat*)&verticesCube[0], sizeof(verticesCube));
}

void RBPrimitive::RenderInternal(RBShader* shader, RBMat4x4 projectionMatrix) {
	RBMat4x4 t = GetTransform();
	RBMat4x4 mat = RBMatrixMultiplyMatrix(projectionMatrix, t);

	if (s_cubeVaoID == -1) {
		CreateAllVAOs(shader);
	}

	shader->Activate();

	shader->ApplyColor(GetColor());
	shader->ApplyProjectionMatrix(mat);
	shader->DrawVBO(s_cubeVaoID, 14);
}

void RBPrimitive::Render(RBShader* shader, RBMat4x4 projectionMatrix) {
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

