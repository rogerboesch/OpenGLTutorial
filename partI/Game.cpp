//
//  Game.cpp
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

#include "Game.hpp"

Game* gGame = new Game();

// Array with 3 vectors to represent the 3 vertices of the triangle
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

// -----------------------------------------------------------------------------
#pragma mark - Construction / Destruction

Game::Game() {}

// -----------------------------------------------------------------------------
#pragma mark - Render loop

void Game::onInit() {}
void Game::onUpdate() {}

void Game::onRender() {
    // Create and assign a vertex buffer
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

// -----------------------------------------------------------------------------

