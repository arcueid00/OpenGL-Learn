//
//  Texture.hpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/23.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <OpenGL/openGL.h>
#include <OpenGL/gl3.h>
#include <string>

#endif /* Texture_hpp */

class Texture
{
    GLuint  name;
    float   width;
    float   height;
    
public:
    Texture( const std::string& filename);
    ~Texture();
    
public:
    void Bind();
    float GetWidth() const;
    float GetHeight() const;
    
};
