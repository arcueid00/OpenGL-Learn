//
//  MyGLView.h
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/07/04.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>

@interface MyGLView : NSOpenGLView

+ (MyGLView *)sharedInstance;
- (void)stopDisplayLink;

-(GLKVector2)mousePosition;

@end
