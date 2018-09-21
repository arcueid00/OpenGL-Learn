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
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    value1=0.0f;
    value2=0.0f;

}

Game::~Game()
{
    
}


void Game::Render()
{
    if( Input::GetMouseButton(0))
    {
        GLKVector2 pos = Input::GetMousePosition();
        value1 = (pos.x + 1.0f)/2.0f;
        value2 = (pos.y + 1.0f)/2.0f;
    }
    
    glClearColor(value1, value2, 1.0f-value1*value2, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
}
