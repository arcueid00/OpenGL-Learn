//
//  Game.cpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/07/21.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#include "Game.hpp"
#include <cmath>
#include <vector>

struct VertexData
{
    GLfloat pos[3];
    GLfloat color[4];
};

Game::Game()
{
    program = std::make_shared<ShaderProgram>( "myshader.vsh", "myshader.fsh");
    
    std::vector<VertexData> data;
    data.push_back( {{ -0.5f, -0.5f,0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}});
    data.push_back( {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}});
    data.push_back( {{ 0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}});
    data.push_back( {{ -0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}});
    
    std::vector<GLushort> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);


    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof( VertexData) * data.size(), &data[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLushort) * indices.size(), &indices[0], GL_STATIC_DRAW);
    
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexData), ((VertexData*)0)->pos );
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(VertexData), ((VertexData*)0)->color);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

Game::~Game()
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1,&vao);
}


void Game::Render()
{
    program->Use();
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
    
    
}
