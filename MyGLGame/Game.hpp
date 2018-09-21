//
//  Game.hpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/07/21.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#include "Time.hpp"
#include "Input.hpp"

class Game
{
private:
    float value1;
    float value2;
    
public:
    Game();
    ~Game();
    
public:
    void    Render();
};

#endif /* Game_hpp */
