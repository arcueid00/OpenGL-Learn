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
    data.push_back( {{ 0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}});

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof( VertexData) * data.size(), &data[0], GL_STATIC_DRAW);
    
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexData), ((VertexData*)0)->pos );
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(VertexData), ((VertexData*)0)->color);
    
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

Game::~Game()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &vbo);
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
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
}
