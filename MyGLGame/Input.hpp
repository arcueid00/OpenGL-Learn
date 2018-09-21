//
//  Input.hpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/22.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <cstdlib>
#include <GLKit/GLKMath.h>

struct KeyCode
{
    static const uint64_t   UpArrow;
    static const uint64_t   DownArrow;
    static const uint64_t   LeftArrow;
    static const uint64_t   RightArrow;
    
    static const uint64_t   Space;
    static const uint64_t   Escape;
    static const uint64_t   Return;
    static const uint64_t   Shift;
    
    static const uint64_t   A;
    static const uint64_t   B;
    static const uint64_t   C;
    static const uint64_t   D;
    static const uint64_t   E;
    static const uint64_t   F;
    static const uint64_t   G;
    static const uint64_t   H;
    static const uint64_t   I;
    static const uint64_t   J;
    static const uint64_t   K;
    static const uint64_t   L;
    static const uint64_t   M;
    static const uint64_t   N;
    static const uint64_t   O;
    static const uint64_t   P;
    static const uint64_t   Q;
    static const uint64_t   R;
    static const uint64_t   S;
    static const uint64_t   T;
    static const uint64_t   U;
    static const uint64_t   V;
    static const uint64_t   W;
    static const uint64_t   X;
    static const uint64_t   Y;
    static const uint64_t   Z;
    
    static const uint64_t   Alpha1;
    static const uint64_t   Alpha2;
    static const uint64_t   Alpha3;
    static const uint64_t   Alpha4;
    static const uint64_t   Alpha5;
    static const uint64_t   Alpha6;
    static const uint64_t   Alpha7;
    static const uint64_t   Alpha8;
    static const uint64_t   Alpha9;
    static const uint64_t   Alpha0;
};

class Input
{
    static uint64_t keyState;
    static uint64_t keyStateOld;
    static uint64_t keyDownStateTriggered;
    static uint64_t keyUpStateTriggered;
    
    static bool isMouseDown;
    static bool isMouseDownOld;
    static bool isMouseDownTriggered;
    static bool isMouseUpTriggered;
    
    static bool isMouseDownRight;
    static bool isMouseDownOldRight;
    static bool isMouseDownTriggeredRight;
    static bool isMouseUpTriggeredRight;
    
public:
    static bool GetKey(uint64_t keyCode);
    static bool GetKeyDown(uint64_t keyCode);
    static bool GetKeyUp(uint64_t keyCode);
    
    static bool GetMouseButton( int button );
    static bool GetMouseButtonDown( int button );
    static bool GetMouseButtonUp( int button );
    static GLKVector2 GetMousePosition();
    
public:
    static void ProcessKeyDown(uint64_t keyCode);
    static void ProcessKeyUp(uint64_t keyCode);
    
    static void ProcessMouseDown();
    static void ProcessMouseUp();
    static void ProcessMouseDownRight();
    static void ProcessMouseUpRight();

    static void Update();

};

#endif /* Input_hpp */
