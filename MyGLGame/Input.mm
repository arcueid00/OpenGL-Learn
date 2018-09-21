//
//  Input.cpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/22.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#include "Input.hpp"
#import "MyGLView.h"


const uint64_t KeyCode::UpArrow     = (1ULL << 0);
const uint64_t KeyCode::DownArrow   = (1ULL << 1);
const uint64_t KeyCode::LeftArrow   = (1ULL << 2);
const uint64_t KeyCode::RightArrow  = (1ULL << 3);

const uint64_t KeyCode::Space       = (1ULL << 4);
const uint64_t KeyCode::Escape      = (1ULL << 5);
const uint64_t KeyCode::Return      = (1ULL << 6);
const uint64_t KeyCode::Shift       = (1ULL << 7);

const uint64_t KeyCode::A           = (1ULL << 8);
const uint64_t KeyCode::B           = (1ULL << 9);
const uint64_t KeyCode::C           = (1ULL << 10);
const uint64_t KeyCode::D           = (1ULL << 11);
const uint64_t KeyCode::E           = (1ULL << 12);
const uint64_t KeyCode::F           = (1ULL << 13);
const uint64_t KeyCode::G           = (1ULL << 14);
const uint64_t KeyCode::H           = (1ULL << 15);
const uint64_t KeyCode::I           = (1ULL << 16);
const uint64_t KeyCode::J           = (1ULL << 17);
const uint64_t KeyCode::K           = (1ULL << 18);
const uint64_t KeyCode::L           = (1ULL << 19);
const uint64_t KeyCode::M           = (1ULL << 20);
const uint64_t KeyCode::N           = (1ULL << 21);
const uint64_t KeyCode::O           = (1ULL << 22);
const uint64_t KeyCode::P           = (1ULL << 23);
const uint64_t KeyCode::Q           = (1ULL << 24);
const uint64_t KeyCode::R           = (1ULL << 25);
const uint64_t KeyCode::S           = (1ULL << 26);
const uint64_t KeyCode::T           = (1ULL << 27);
const uint64_t KeyCode::U           = (1ULL << 28);
const uint64_t KeyCode::V           = (1ULL << 29);
const uint64_t KeyCode::W           = (1ULL << 30);
const uint64_t KeyCode::X           = (1ULL << 31);
const uint64_t KeyCode::Y           = (1ULL << 32);
const uint64_t KeyCode::Z           = (1ULL << 33);

const uint64_t KeyCode::Alpha1      = (1ULL << 34);
const uint64_t KeyCode::Alpha2      = (1ULL << 35);
const uint64_t KeyCode::Alpha3      = (1ULL << 36);
const uint64_t KeyCode::Alpha4      = (1ULL << 37);
const uint64_t KeyCode::Alpha5      = (1ULL << 38);
const uint64_t KeyCode::Alpha6      = (1ULL << 39);
const uint64_t KeyCode::Alpha7      = (1ULL << 40);
const uint64_t KeyCode::Alpha8      = (1ULL << 41);
const uint64_t KeyCode::Alpha9      = (1ULL << 42);
const uint64_t KeyCode::Alpha0      = (1ULL << 43);


uint64_t Input::keyState                = 0ULL;
uint64_t Input::keyStateOld             = 0ULL;
uint64_t Input::keyDownStateTriggered   = 0ULL;
uint64_t Input::keyUpStateTriggered     = 0ULL;

bool Input::isMouseDown = false;
bool Input::isMouseDownOld = false;
bool Input::isMouseDownTriggered = false;
bool Input::isMouseUpTriggered = false;

bool Input::isMouseDownRight = false;
bool Input::isMouseDownOldRight = false;
bool Input::isMouseDownTriggeredRight = false;
bool Input::isMouseUpTriggeredRight = false;

bool Input::GetKey(uint64_t keyCode)
{
    return (keyState & keyCode)? true: false;
}

bool Input::GetKeyDown(uint64_t keyCode)
{
    return (keyDownStateTriggered & keyCode)? true: false;
}

bool Input::GetKeyUp(uint64_t keyCode)
{
    return (keyUpStateTriggered & keyCode)? true: false;
}

void Input::ProcessKeyDown(uint64_t keyCode)
{
    keyState |= keyCode;
}

void Input::ProcessKeyUp(uint64_t keyCode)
{
    keyState &= ~keyCode;
}

bool Input::GetMouseButton( int button )
{
    if( button == 0 )
    {
        return isMouseDown;
    }
    else
    {
        return isMouseDownRight;
    }
}

bool Input::GetMouseButtonDown( int button )
{
    if( button == 0)
    {
        return isMouseDownTriggered;
    }
    else
    {
        return isMouseDownTriggeredRight;
    }
}

bool Input::GetMouseButtonUp( int button )
{
    if( button == 0)
    {
        return isMouseUpTriggered;
    }
    else
    {
        return isMouseUpTriggeredRight;
    }
}

GLKVector2 Input::GetMousePosition()
{
    return [[MyGLView sharedInstance] mousePosition];
}


void Input::ProcessMouseDown()
{
    isMouseDown = true;
}

void Input::ProcessMouseUp()
{
    isMouseDown = false;
}

void Input::ProcessMouseDownRight()
{
    isMouseDownRight = true;
}

void Input::ProcessMouseUpRight()
{
    isMouseDownRight = false;
}

void Input::Update()
{
    keyDownStateTriggered = keyState & ~keyStateOld;
    keyUpStateTriggered = ~keyState & keyStateOld;
    keyStateOld = keyState;
    
    isMouseDownTriggered = isMouseDown & ~isMouseDownOld;
    isMouseUpTriggered = ~isMouseDown & isMouseDownOld;
    isMouseDownOld = isMouseDown;
    
    isMouseDownTriggeredRight = isMouseDownRight & ~isMouseDownOldRight;
    isMouseUpTriggeredRight = ~isMouseDownRight & isMouseDownOldRight;
    isMouseDownOldRight = isMouseDownRight;
    
    
    
    
}

