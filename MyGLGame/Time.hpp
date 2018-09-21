//
//  Time.hpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/22.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp

struct Time
{
    static unsigned frameCount; //!< フレーム数
    static float    time;       //!< ゲーム開始時からの経過時間（秒）
    static float    deltaTime;  //!< 直前のフレームからの経過時間（秒）
    static float    fps;        //!< FPS
    
    static void Start();
    static void Update();
};


#endif /* Time_hpp */
