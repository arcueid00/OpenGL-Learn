//
//  Shader.hpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/23.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <string>


class Shader
{
private:
    GLuint shader;
    
public:
    Shader(GLenum shaderType, const std::string& filanem);
    ~Shader();
    
public:
    GLuint GetHandle() const;
};

class ShaderProgram
{
private:
    GLuint program;
    std::shared_ptr<Shader> vshader;
    std::shared_ptr<Shader> fshader;

public:
    ShaderProgram(const std::string& vshName, const std::string& fshName);
    ~ShaderProgram();
    
public:
    void    Use();
};

#endif /* Shader_hpp */
