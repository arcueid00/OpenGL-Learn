//
//  AppDelegate.m
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/07/04.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#import "AppDelegate.h"
#import "MyGLView.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    [[MyGLView sharedInstance] stopDisplayLink];
    return NSTerminateNow;
}

@end
