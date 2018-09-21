//
//  StringSupport.cpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/22.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#include "StringSupport.hpp"

#include <fstream>
#include <stdexcept>
#import <Foundation/Foundation.h>


std::string FormatString(const char* format, ...)
{
    static char buffer[1024];
    va_list marker;
    va_start(marker,format);
    vsnprintf(buffer, 1024, format, marker);
    va_end(marker);
    return buffer;
}

std::string GetFilepath(const std::string& filename)
{
    NSString *fileNameObj = [[NSString alloc] initWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
    
    NSString *body = [fileNameObj stringByDeletingPathExtension];
    NSString *ext = [fileNameObj pathExtension];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:body ofType:ext];
    if (!path) {
        throw GameError("Cannot locate a file path: %s", filename.c_str());
    }
    
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

std::string ReadTextFile(const std::string& filename)
{
    std::string filepath = GetFilepath(filename);
    
    std::ifstream ifs(filepath);
    if (!ifs) {
        throw GameError("Failed to open a file: %s", filepath.c_str());
    }
    
    ifs.seekg(0, std::ios::end);
    int length = (int)ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    
    char *buffer = new char[length + 1];
    ifs.read(buffer, length);
    buffer[length] = '\0';
    std::string ret = buffer;
    delete[] buffer;
    
    return ret;
}
