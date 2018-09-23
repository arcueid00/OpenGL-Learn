//
//  MyGLView.m
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/07/04.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#import "MyGLView.h"

#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>

#include "Game.hpp"
#include "Time.hpp"
#include "Input.hpp"

static MyGLView *instance = nil;

@implementation MyGLView
{
    NSOpenGLContext*    glContext;
    CVDisplayLinkRef    displayLink;
    float               value;
    bool                hasDisplayLinkStopped;
    Game                *game;
    NSWindow            *window;
    NSSize              size;
    NSRect              viewportRect;
}
+ (MyGLView*)sharedInstance
{
    return instance;
}

static CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink,
                                    const CVTimeStamp* now,
                                    const CVTimeStamp* outputTime,
                                    CVOptionFlags flagsIn,
                                    CVOptionFlags *flagsOut,
                                    void* displayLinkContext)
{
    @autoreleasepool{
        MyGLView* glView = (__bridge MyGLView*)displayLinkContext;
        [glView render];
        return kCVReturnSuccess;
    }
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (instancetype)initWithFrame:(NSRect)frame
{
    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFAAllowOfflineRenderers,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFADepthSize, 32,
        NSOpenGLPFAMultisample,
        NSOpenGLPFASampleBuffers, 1,
        NSOpenGLPFASamples, 4,
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
    
    self = [super initWithFrame:frame pixelFormat:pixelFormat];
    if (self) {
        instance = self;
        [self setWantsBestResolutionOpenGLSurface:YES];
    }
    return self;

}

- (void)prepareOpenGL
{
    [super prepareOpenGL];
    
    const GLubyte *glVersion = glGetString(GL_VERSION);
    const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("OpenGL Version : %s\n", glVersion);
    printf("GLSL Version : %s\n", glslVersion);
    
    GLint maxTextureUnits, maxTextureSize;
    glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
    glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    printf( "Max Texture Units : %d\n", maxTextureUnits);
    printf( "Max Texture Size (width/Height) : %d\n", maxTextureSize);
    
    GLint maxIndexListVertices, maxIndexListCount;
    glGetIntegerv( GL_MAX_ELEMENTS_VERTICES, &maxIndexListVertices);
    glGetIntegerv( GL_MAX_ELEMENTS_INDICES, &maxIndexListCount);
    printf( "Max IndexList Vertices : %d\n", maxIndexListVertices);
    printf( "Max IndexList Count %d\n", maxIndexListCount);
    
    window = self.window;
    size = self.bounds.size;
    
    [self.window makeFirstResponder:self];
    
    Time::Start();
    
    glContext = [self openGLContext];
    
    game = new Game();
    [glContext flushBuffer];
    
    // 垂直同期を使用するためには以下2行のコメントアウトを外す
    //GLint swapInt = 1;
    //[glContext setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink, &DisplayLinkCallback, (__bridge void*)(self));
    
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    CVDisplayLinkStart(displayLink);
}

- (void)stopDisplayLink
{
    CVDisplayLinkStop(displayLink);
    CVDisplayLinkRelease(displayLink);
}

-(GLKVector2)mousePosition
{
    NSPoint location = [NSEvent mouseLocation];
    NSRect rect = NSMakeRect(location.x, location.y, 0.0f, 0.0f);
    rect = [window convertRectFromScreen:rect];
    location = rect.origin;
    location.x = location.x * 2 / size.width - 1.0f;
    location.y = location.y * 2 / size.height - 1.0f;
    return GLKVector2Make(location.x, location.y);
}

-(void)render
{
    Input::Update();
    
    [glContext lock];
    [glContext makeCurrentContext];
    
    glViewport(viewportRect.origin.x, viewportRect.origin.y, viewportRect.size.width, viewportRect.size.height);
    game->Render();
    
    [glContext flushBuffer];
    [glContext unlock];
    
    Time::Update();
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        [self.window setTitle:[NSString stringWithFormat:@"Game(%.2f fps)", Time::fps]];
         }];
}

- (void)resetViewportSize
{
    NSSize frameSize = [self frame].size;
    frameSize = [self convertSizeToBacking:frameSize];
    const float kBaseAspect = 4.0f/3.0f;
    if(frameSize.width / frameSize.height > kBaseAspect)
    {
        int width = int(frameSize.height*kBaseAspect);
        viewportRect.origin.x = (frameSize.width-width)/2;
        viewportRect.origin.y = 0;
        viewportRect.size.width = width;
        viewportRect.size.height = frameSize.height;
    }
    else
    {
        int height = int(frameSize.width/kBaseAspect);
        viewportRect.origin.x = 0;
        viewportRect.origin.y = (frameSize.height - height)/2;
        viewportRect.size.width = frameSize.width;
        viewportRect.size.height = height;
    }
    size = self.bounds.size;
}

-(void)pauseDisplayLink
{
    CVDisplayLinkStop(displayLink);
}

-(void)restartDisplayLink
{
    CVDisplayLinkStart(displayLink);
}

@end
