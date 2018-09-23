//
//  Game.cpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/07/21.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#include "Game.hpp"
#include <cmath>


Game::Game()
{
    program = std::make_shared<ShaderProgram>( "myshader.vsh", "myshader.fsh");
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLfloat data[] =
    {
        -0.5f, -0.5f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        
        0.5f, -0.5f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat) * 7 * 3, data, GL_STATIC_DRAW);
    
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(GLfloat)*7, (GLfloat*)0 );
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*7, ((GLfloat*)0)+3);
    
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    value1=0.0f;
    value2=0.0f;

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
#if 0
    if( Input::GetMouseButton(0))
    {
        GLKVector2 pos = Input::GetMousePosition();
        value1 = (pos.x + 1.0f)/2.0f;
        value2 = (pos.y + 1.0f)/2.0f;
    }
    
    glClearColor(value1, value2, 1.0f-value1*value2, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
#else
    program->Use();
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
#endif
    
}
