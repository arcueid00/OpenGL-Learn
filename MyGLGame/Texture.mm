//
//  Texture.cpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/23.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#include "Texture.hpp"

#include "StringSupport.hpp"

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

static NSURL *FindImageFile(const std::string& filename)
{
    NSString* fileNameStr = [NSString stringWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
    NSString* baseName = [fileNameStr stringByDeletingPathExtension];
    NSString* ext = [fileNameStr pathExtension];
    return [[NSBundle mainBundle] URLForResource:baseName withExtension:ext];
}

Texture::Texture( const std::string& filename)
{
    NSURL *fileURL = FindImageFile( filename );
    if( !fileURL )
    {
        throw GameError( "Texture::Texture() Cannot find a texture file:\"%s\"", filename.c_str());
    }
    NSDictionary* option = @{ GLKTextureLoaderApplyPremultiplication:@NO,
                              GLKTextureLoaderOriginBottomLeft:@YES};
    NSError* error = nil;
    GLKTextureInfo* texInfo = [GLKTextureLoader textureWithContentsOfURL:fileURL
                                                                 options:option error:&error];
    if( !texInfo )
    {
        throw GameError("Texture::Texture() Failed to load a texture: \"%s\"", filename.c_str());
    }
    name = texInfo.name;
    width = texInfo.width;
    height = texInfo.height;
}

Texture::~Texture()
{
    glDeleteTextures(1, &name);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, name);
}

float Texture::GetWidth() const
{
    return width;
}

float Texture::GetHeight() const
{
    return height;
}
