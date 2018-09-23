//
//  Shader.cpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/23.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#include "Shader.hpp"
#include "StringSupport.hpp"

Shader::Shader( GLenum shaderType, const std::string& filename)
{
    shader = glCreateShader( shaderType );
    if( shader == 0 )
    {
        throw GameError( "Shader::Shader() Failed to create a shader: %s", filename.c_str() );
    }
    
    std::string sourceStr = ReadTextFile( filename );
    
    const GLchar *source = sourceStr.c_str();
    glShaderSource( shader, 1, &source, NULL );
    
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        throw GameError( "Shader::Shader() FGailed to glShaderSource(): error = %d", error );
    }
    
    glCompileShader(shader);
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result );
    if( result == GL_FALSE )
    {
        GLint logLenth;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLenth);
        if( logLenth> 0 )
        {
            GLchar *logBuffer = new GLchar[logLenth];
            glGetShaderInfoLog( shader, logLenth, &logLenth, logBuffer);
            printf( "-----\n");
            printf("[Shader Comple Log] %s", logBuffer);
            printf( "-----\n");
            delete[] logBuffer;
        }
        throw GameError("Shader::Shader() Failed to comple a shader : %s", filename.c_str() );
    }
}

Shader::~Shader()
{
    glDeleteShader(shader);
}

GLuint Shader::GetHandle() const
{
    return shader;
}

ShaderProgram::ShaderProgram(const std::string& vshName, const std::string& fshName)
{
    vshader = std::make_shared<Shader>( GL_VERTEX_SHADER, vshName);
    fshader = std::make_shared<Shader>( GL_FRAGMENT_SHADER, fshName);
    
    program = glCreateProgram();
    if( program == 0 )
    {
        throw GameError( "ShaderProgram::ShaderProgram() Failed to create a shader program.");
    }
    
    glAttachShader( program, vshader->GetHandle());
    glAttachShader( program, fshader->GetHandle());
    glLinkProgram(program);
    
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if( status == GL_FALSE)
    {
        GLint logLength;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength);
        if( logLength > 0 )
        {
            GLchar *logBuffer = new GLchar[logLength];
            glGetProgramInfoLog( program, logLength, &logLength, logBuffer);
            printf( "-----\n");
            printf("[Shader Comple Log] %s", logBuffer);
            printf( "-----\n");
            delete[] logBuffer;
        }
        throw GameError( "ShaderProgram::ShaderProgram() Failed to link a program : %s, %s", vshName.c_str(), fshName.c_str());
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program);
}

void ShaderProgram::Use()
{
    glUseProgram(program);
    GLenum error = glGetError();
    if( error != GL_NO_ERROR)
    {
        throw GameError( "ShaderProgram::Use() Failed to glUseProgram(): error = %d", error);
    }
}
